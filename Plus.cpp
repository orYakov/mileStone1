//
// Created by oryakov on 12/17/18.
//

#include "Plus.h"

Plus::Plus(Expression *first, Expression *second) : BinaryExpression(first,
                                                                     second) {

}

double Plus::calculate() {
    //cout << (left->calculate() + right->calculate()) << endl;
    return left->calculate() + right->calculate();
}
