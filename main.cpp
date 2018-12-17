#include <iostream>
#include "Num.h"
#include "BinaryExpression.h"
#include "Plus.h"
#include "Div.h"
#include "Mul.h"
#include "Minus.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Expression* e = new Plus(new Div(new Num(10),new Num(2)) , new Mul(new Num(2), new Minus(new Num(3), new Num(4))));
    //Expression* expression = new Plus(new Num(3), new Num(5));
    cout << e->calculate();
    return 0;
}