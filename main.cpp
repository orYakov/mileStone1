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
#include <thread>
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

#include <list>

using namespace std;

int main(int argc, char *argv[]) {

    string fileName = argv[1];
    Lexer lexer;
    vector<string> lexedData = lexer.lex(fileName);
    Parser parser(lexedData);
    parser.parse();

    return 0;
}
