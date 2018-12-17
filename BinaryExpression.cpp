//
// Created by oryakov on 12/17/18.
//

#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression *first, Expression *second) {
    this->left = first;
    this->right = second;

}
