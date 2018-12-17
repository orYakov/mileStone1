//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_PLUS_H
#define MILESTONE1_PLUS_H


#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    Plus(Expression* first, Expression* second);
    virtual double calculate();
};


#endif //MILESTONE1_PLUS_H
