//
// Created by oryakov on 12/20/18.
//

#include "PrintCommand.h"
#include "MapHolder.h"
#include "Parser.h"

int PrintCommand::doCommand(vector<string> commandOperation, int index) {
    string toPrint = commandOperation[index + 1]; // skip the word "print"
    MapHolder* mapHolder = MapHolder::getInstance();
    vector<string> vars = mapHolder->getVars();
    map<string, double> symbols = mapHolder->getSymbolTable();
    //double replaceValue;
    bool createExp = false;
    int resIndex = Parser::getReturnIndex(commandOperation, index);

    for (int i = 0; i < vars.size(); ++i) {
        size_t found = toPrint.find(vars[i]);
        if (found != string::npos) {
            if (symbols.count(vars[i])) {
//                replaceValue = symbols.at(vars[i]);
//                string strRepVal = to_string(replaceValue);
//                // Replace (vars[i].size) characters from "found-th" index with strRepVal
//                toPrint.replace(found, vars[i].size(), strRepVal);
                createExp = true;
            }
        }
    }
    if (createExp) {
//        int j = index + 1;
//        while (commandOperation[j] != "@") {
//            toPrint += (" " + commandOperation[j]);
//            ++j;
//        }
        ShuntingYard shuntingYard;
        Expression* expression = shuntingYard.createExpression(toPrint);
        double value = expression->calculate();
        cout << value << endl;
    } else {
        int j = index + 2;
        while (commandOperation[j] != "@") {
            toPrint += (" " + commandOperation[j]);
            ++j;
        }
        cout << toPrint << endl;
    }
    return resIndex;
}
