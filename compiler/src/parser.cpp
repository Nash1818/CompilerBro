// cpp script for parsing : uses parser.h as header file for AST traversal..
// To be modified as well!

#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {
    // Initialize the parser with the given tokens and position
}

// entry point:
std::shared_ptr<ASTNode> Parser::parse() {
    return parseStatement();
}

// Parsing statements (vars, struct, assignment):
std::shared_ptr<ASTNode> Parser::parseStatement() {
    if(match(TokenType::KEYWORD)) {
        if (peek().value == "struct") {
            return parseStructDeclaration();
        }
        if (peek().value == "int") {
            return parseArrayDeclaration();
        }
    }
    return parseStatement();
}

// Parsing expressions:
std::shared_ptr<ASTNode> Parser::parseExpression() {
    if (match(TokenType::NUMBER)){
        return parseNumber();
    }
    if (match(TokenType::IDENTIFIER)) {
        if (peek().value == "[") {
            return parseArrayAccess();
        }
        if (peek().value == "."){
            return parseStructFieldAccess();
        }
        return parseIdentifier();
    }
    return parseBinaryOperation();
}

// Parse Binary operations (a + b)
std::shared_ptr<ASTNode>Parser::parseBinaryOperation(){
    auto left = parseExpression();
    if(match(TokenType::SYMBOL) && (peek().value == "+" || peek().value == "-")){
        std::string op = advance().value;
        auto right = parseExpression();
        return std::make_shared<BinaryOperationNode>(op, left, right);
    }
    return left;
}

// Identifiers:
std::shared_ptr<ASTNode> Parser::parseIdentifier() {
    Token token = advance();
    return std::make_shared<IdentifierNode>(token.value);
}

// Number:
std::shared_ptr<ASTNode> Parser::parseNumber() {
    Token token = advance();
    return std::make_shared<NumberNode>(std::stoi(token.value));
}

// array declaration:
std::shared_ptr<ASTNode> Parser::parseArrayDeclaration() {
    advance(); // int
    std::string name = advance().value; // array name
    advance(); // consume '['
    int size = std::stoi(advance().value); // size
    advance(); // consume ']'
    advance(); // consume ;
    return std::make_shared<ArrayDeclarationNode>(name, size);
}

// parse array access:
std::shared_ptr<ASTNode> Parser::parseArrayAccess() {
    std::string arrayName = advance().value;
    advance(); // consume '['
    auto index = parseExpression();
    advance(); // consume ']'
    return std::make_shared<ArrayAccessNode>(arrayName, index);
}

// struct declaration:
std::shared_ptr<ASTNode> Parser::parseStructDeclaration() {
    advance(); // struct
    std::string name = advance().value; // struct name
    advance(); // consume '{'

    std::unordered_map<std::string, std::string> fields;
    while(!match(TokenType::SYMBOL) || peek().value != "}") {
        std::string type = advance().value; // field name
        std::string fieldName = advance().value;
        advance();
        fields[fieldName] = type;
    }
    advance(); // consume '}'
    advance(); // consume ;
    return std::make_shared<StructNode>(name, fields);
}

// struct field access:
std::shared_ptr<ASTNode> Parser::parseStructFieldAccess() {
    std::string structName = advance().value;
    advance(); // consume '.'
    std::string fieldName = advance().value;
    return std::make_shared<StructFieldAccessNode>(structName, fieldName);
}

// Helper functions used above -> (peek, match, advance, isAtEnd)

// peek
Token Parser :: peek() {
    return isAtEnd() ? Token{TokenType::UNKNOWN, ""} : tokens[position];
}

// advance:
Token Parser :: advance() {
    return isAtEnd() ? Token{TokenType::UNKNOWN, ""} : tokens[position++];
}

// match:
bool Parser :: match(TokenType type) {
    if (!isAtEnd() && tokens[position].type == type) {
        position++;
        return true;
    }
    return false;
}

// isAtEnd:
bool Parser :: isAtEnd() {
    return position >= tokens.size();
}