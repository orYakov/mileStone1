//
// Created by noa on 12/17/18.
//

#ifndef MILESTONE1_LEXER_H
#define MILESTONE1_LEXER_H



#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Lexer {

public:

    vector<string> lex(string name);
    void contract(vector<string> &line);
    bool isOperator(string str);
    bool isWhiteSpace(string str);

};



#endif //MILESTONE1_LEXER_H
