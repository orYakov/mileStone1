//
// Created by oryakov on 12/17/18.
//

#include "Mul.h"

Mul::Mul(Expression *first, Expression *second) : BinaryExpression(first,
                                                                   second) {

}

double Mul::calculate() {
    return left->calculate() * right->calculate();
}


