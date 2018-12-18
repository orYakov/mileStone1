//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_SHUNTINGYARD_H
#define MILESTONE1_SHUNTINGYARD_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include "Num.h"
#include "Plus.h"
#include "Minus.h"
#include "Div.h"
#include "Mul.h"

using namespace std;
/// balh blah blah
class ShuntingYard {
    vector<char> operators = {'+', '-', '*', '/'};
    deque<string> resQueue;
    stack<char> opStack;
    map<char, int> priority;
public:
    bool isOperator(char token);
    bool isOpenBracket(char token);
    bool isCloseBracket(char token);
    void initPriority();
    deque<string> makePostFixQueue (string &tokens);
    bool isNumber(string token);
    Expression* evaluateExpression(string tokens);
    Expression* createSimpleExp(char op, Expression* &leftExp, Expression* &rightExp);

};


#endif //MILESTONE1_SHUNTINGYARD_H
