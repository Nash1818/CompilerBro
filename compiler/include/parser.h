// start of the parser for AST file:

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include<vector>
#include<memory>

class Parser{
    public:
        explicit Parser(const std::vector<Token>& tokens);
        // start for the parsing....
        std::shared_ptr<ASTNode> parse();
        
    private:
        const std::vector<Token>& tokens;
        size_t position;

        std::shared_ptr<ASTNode> parseStatement();
        std::shared_ptr<ASTNode> parseExpression();
        std::shared_ptr<ASTNode> parseBinaryOperation();
        std::shared_ptr<ASTNode> parseIdentifier();
        std::shared_ptr<ASTNode> parseNumber();
        std::shared_ptr<ASTNode> parseArrayDeclaration();
        std::shared_ptr<ASTNode> parseArrayAccess();
        std::shared_ptr<ASTNode> parseStructDeclaration();
        std::shared_ptr<ASTNode> parseStructFieldAccess();

        Token peek();
        Token advance();
        bool match(TokenType type);
        bool isAtEnd();
};

#endif
// end of parser header file...