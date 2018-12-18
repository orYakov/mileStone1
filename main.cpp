#include <iostream>
#include "Num.h"
#include "BinaryExpression.h"
#include "Plus.h"
#include "Div.h"
#include "Mul.h"
#include "Minus.h"
#include "ShuntingYard.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //Expression* e = new Plus(new Div(new Num(10),new Num(2)) , new Mul(new Num(2), new Minus(new Num(3), new Num(4))));
    //Expression* expression = new Plus(new Num(3), new Num(5));
    //cout << e->calculate();
    string tokens = "2 / (( 1 - 5 ) * 50)";
    ShuntingYard shuntingYard;
    Expression* expression = shuntingYard.evaluateExpression(tokens);
    cout << expression->calculate();
    return 0;
    // / 5 * ( 2 + 7)
}