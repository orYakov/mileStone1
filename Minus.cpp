//
// Created by oryakov on 12/17/18.
//

#include "Minus.h"

Minus::Minus(Expression *first, Expression *second) : BinaryExpression(first,
                                                                       second) {

}

double Minus::calculate() {
    return left->calculate() - right->calculate();
}
