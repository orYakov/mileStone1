//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_SHUNTINGYARD_H
#define MILESTONE1_SHUNTINGYARD_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
/// balh blah blah
class ShuntingYard {
    vector<string> operators = {"+", "-", "*", "/"};
    queue<string> queue1;
    stack<string> stack2;
public:

    bool isnumber(string token);
    bool isOperator(string token);
    bool isOpenBracket(string token);
    bool isCloseBracket(string token);

};


#endif //MILESTONE1_SHUNTINGYARD_H
