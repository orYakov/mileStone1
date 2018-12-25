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


class ShuntingYard {
    map<char, int> prcedence;
    vector<char> operators = {'+', '-', '*', '/'};
public:
/////////////
    ShuntingYard();
    void initializeMap();

    int precedence(char operation);

    Expression *createExpression(string tokens);
    Expression* applyOp(Expression* val1,Expression*  val2,char operation);
    bool isOperator(char token);
};


#endif //MILESTONE1_SHUNTINGYARD_H
