// header file for tokenizing the source code:

#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include<string>
#include<vector>
#include<unordered_set>

class Lexer{
    // defining public and private:
    public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

    private:
    std::string input;
    size_t position;

    const std::unordered_set<std::string> keywords = {"if", "else", "while", "return", "parallel_for", "struct"};
    const std::unordered_set<char> symbols = {'+', '-', '*', '/', '=', ';', '(', ')', '{', '}', '[', ']'};

    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readSymbol();
    bool isSymbol(char c) const;
};

#endif

// end of Lexer header