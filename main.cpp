#include <iostream>
#include "Num.h"
#include "BinaryExpression.h"
#include "Plus.h"
#include "Div.h"
#include "Mul.h"
#include "Minus.h"
#include "ShuntingYard.h"
#include "MapHolder.h"
#include "PrintCommand.h"
#include "Lexer.h"
#include "Parser.h"

//#include <iostream>
#include <list>
//#include "Expression.h"
//#include "ShuntingYard.h"

using namespace std;

int main() {

    Lexer lexer;
    vector<string> lexedData = lexer.lex("bdika.txt");
    Parser parser(lexedData);
    parser.parse();


//    MapHolder* mapHolder = MapHolder::getInstance();
//    mapHolder->setVarValue("alt", 30);
//    mapHolder->setVarValue("throttle", 40.2);
//    PrintCommand* printCommand = new PrintCommand;
//    vector<string> strings;
//    strings.push_back("alt + throttle");
//    printCommand->doCommand(strings);


//    ShuntingYard x = ShuntingYard();
//    list < Expression * > list1;
//    Expression* a = x.createExpression("10 + 2 * 6");
//    list1.push_back(a);
//    Expression* b = x.createExpression("100 * 2 + 12");
//    list1.push_back(b);
//    Expression* c = x.createExpression("100 * ( 2 + 12 )");
//    list1.push_back(c);
//    Expression* d = x.createExpression("100 * ( 2 + 12 ) / 14");
//    list1.push_back(d);
//    Expression* d1 = x.createExpression(" + -  40");
//    list1.push_back(d1);
//    Expression* e = x.createExpression("5 - + - 3");
//    list1.push_back(e);
//    Expression* e0 = x.createExpression("5 + - + 3");
//    list1.push_back(e0);
//    Expression* e1 = x.createExpression("5 - - 3");
//    list1.push_back(e1);
//    Expression* e2 = x.createExpression("3 - + 10");
//    list1.push_back(e2);
//    Expression* e22 = x.createExpression("3 + - 10");
//    list1.push_back(e22);
//    Expression* e3 = x.createExpression("3 * - 10");
//    list1.push_back(e3);
//    Expression* e31 = x.createExpression("3 * + 10");
//    list1.push_back(e31);
//    Expression* e32 = x.createExpression("81 / - 9");
//    list1.push_back(e32);
//    Expression* e33 = x.createExpression("81 / + 9");
//    list1.push_back(e33);
//    Expression* f = x.createExpression(" - ( - 2 + 4)");
//    list1.push_back(f);
//    Expression* g = x.createExpression(" - ( - 6 / - 2)");
//    list1.push_back(g);
//    Expression* h = x.createExpression(" - ( - 6 * - 2)");
//    list1.push_back(h);
//    Expression* i = x.createExpression(" 0.2 * 0.5 ");
//    list1.push_back(i);
//    Expression* i1 = x.createExpression(" (0.8 -(0.2 * 0.5) + 0.8 ) / 0.5 ");
//    list1.push_back(i1);
//    Expression* i2 = x.createExpression(" 1/3 ");
//    list1.push_back(i2);
//    Expression* i3 = x.createExpression(" 1 / 3 / 1 / 4 / 1 / 5");
//    list1.push_back(i3);
//    Expression* i4 = x.createExpression(" (1 / 3)* (1 / 4) * (1 / 5) ");
//    list1.push_back(i4);
//    Expression* i5 = x.createExpression(" (6 / 3)* (-4) - (-5)");
//    list1.push_back(i5);
//
//
//
//    for (Expression* e : list1){
//        cout<< e->calculate()<<endl;
//    }

/*output:
 * 22
 * 212
 * 1400
 * 100
 * -40
 * 8
 * 2
 * 8
 * -7
 * -7
 * -30
 * 30
 * -9
 * 9
 * -2
 * -3
 * -12
 * 0.1
 * 3
 * 0.333333
 * 0.166667
 * 0.166667
 * */

    return 0;
}



//
//
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    //Expression* e = new Plus(new Div(new Num(10),new Num(2)) , new Mul(new Num(2), new Minus(new Num(3), new Num(4))));
//    //Expression* expression = new Plus(new Num(3), new Num(5));
//    //cout << e->calculate();
//    string tokens = "-0.2 *-0.3 * -0.2";
//    ShuntingYard shuntingYard;
//    Expression* expression = shuntingYard.evaluateExpression(tokens);
//    cout << expression->calculate();
//    return 0;
//    // / 5 * ( 2 + 7)
//    //2 / (( 1 - 5 ) * 50)
//    //"2 / (( 1 - 5 ) * 50) / 5 * ( 2 + 7)"
//    //"2 / (( 1 - 5 ) * 50) / 5 * ( 2 + 7) * 2/300"
//}