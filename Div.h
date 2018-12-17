//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_DIV_H
#define MILESTONE1_DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {
public:
    Div(Expression* first, Expression* second);
    virtual double calculate();
};


#endif //MILESTONE1_DIV_H
