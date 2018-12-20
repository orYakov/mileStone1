//
// Created by oryakov on 12/20/18.
//

#include "PrintCommand.h"
#include "MapHolder.h"

int PrintCommand::doCommand(vector<string> commandOperation) {
    string toPrint = commandOperation[0];
    MapHolder* mapHolder = MapHolder::getInstance();
    vector<string> vars = mapHolder->getVars();
    map<string, double> symbols = mapHolder->getSymbolTable();
    double replaceValue;
    bool createExp = false;
    for (int i = 0; i < vars.size(); ++i) {
        size_t found = toPrint.find(vars[i]);
        if (found != string::npos) {
            if (symbols.count(vars[i])) {
                replaceValue = symbols.at(vars[i]);
                string strRepVal = to_string(replaceValue);
                // Replace (vars[i].size) characters from "found-th" index with strRepVal
                toPrint.replace(found, vars[i].size(), strRepVal);
                createExp = true;
            }
        }
    }
    if (createExp) {
        ShuntingYard shuntingYard;
        Expression* expression = shuntingYard.createExpression(toPrint);
        double value = expression->calculate();
        cout << value << endl;
    } else {
        cout << toPrint << endl;
    }
}
