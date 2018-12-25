//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_MINUS_H
#define MILESTONE1_MINUS_H

#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression* first, Expression* second);
    virtual double calculate();
};

#endif //MILESTONE1_MINUS_H
///