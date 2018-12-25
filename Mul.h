//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_MUL_H
#define MILESTONE1_MUL_H

#include "BinaryExpression.h"

class Mul: public BinaryExpression {
public:
    Mul(Expression* first, Expression* second);
    virtual double calculate();
};


#endif //MILESTONE1_MUL_H
///