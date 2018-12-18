//
// Created by oryakov on 12/17/18.
//

#include "Div.h"

Div::Div(Expression *first, Expression *second) : BinaryExpression(first,
                                                                   second) {

}

double Div::calculate() {
    cout << (left->calculate() / right->calculate()) << endl;
    return left->calculate() / right->calculate();
}
