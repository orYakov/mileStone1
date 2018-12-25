//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_BINARYEXPRESSION_H
#define MILESTONE1_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* first, Expression* second);
    virtual double calculate() = 0;
};
#endif //MILESTONE1_BINARYEXPRESSION_H
///