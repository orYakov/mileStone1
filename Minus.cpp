//
// Created by oryakov on 12/17/18.
//

#include "Minus.h"

Minus::Minus(Expression *first, Expression *second) : BinaryExpression(first,
                                                                       second) {

}

double Minus::calculate() {
    //cout << (left->calculate() - right->calculate()) << endl;
    return left->calculate() - right->calculate();
}
