// defines the token structure for the lexer:

#ifndef TOKEN_H
#define TOKEN_H

#include<string>
#include<iostream>

// class enum:
enum class TokenType {
    // keywords
    IDENTIFIER,
    NUMBER,
    KEYWORD,
    SYMBOL,
    WHITESPACE,
    UNKNOWN
};

// struct:
struct Token {
    TokenType type;
    std::string value;

    void print() const;
};

#endif 
// end of Token header file