#include "lexer.h"
#include<cctype>

Lexer::Lexer(const std::string& input) : input(input), position(0) {
    // nothing to do here
}

// implementing the methods:

// tokenize method for header file will be called from here...
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (position < input.length()){
        char c = input[position];
        if (std::isspace(c)) {
            position++;
            continue;
        }

        if (std::isalpha(c) || c == '_'){
            tokens.push_back(readIdentifierOrKeyword());
        } else if(std:: isdigit(c)){
            tokens.push_back(readNumber());
        } else if(isSymbol(c)){
            tokens.push_back(readSymbol());
        } else {
            tokens.push_back({TokenType::UNKNOWN, std::string(1, c)});
            position++;
        }
    }
    return tokens;
}

Token Lexer::readIdentifierOrKeyword(){
    size_t start = position;
    while (position < input.length() && (std::isalnum(input[position]) || input[position] == '_')) {
        position++;
    }
    std::string value = input.substr(start, position - start);
    if(keywords.count(value)){
        return {TokenType::KEYWORD, value};
    }
    return {TokenType::IDENTIFIER, value};
}

Token Lexer::readNumber(){
    size_t start = position;
    while(position < input.length() && std::isdigit(input[position])){
        position++;
    }
    return {TokenType::NUMBER, input.substr(start, position - start)};
}

Token Lexer::readSymbol(){
    char c = input[position];
    position++;
    return {TokenType::SYMBOL, std::string(1, c)};
}

bool Lexer::isSymbol(char curr) const{
    return symbols.count(curr);
}

// end of Lexer.cpp for creating lexems from the souce code: 
// Next step is creating an AST...