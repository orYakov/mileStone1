//
// Created by oryakov on 12/17/18.
//

#ifndef MILESTONE1_NUMBER_H
#define MILESTONE1_NUMBER_H

#include "Expression.h"

class Num : public Expression {
    double value;
public:
    Num(double value);
    virtual double calculate();
};


#endif //MILESTONE1_NUMBER_H
///