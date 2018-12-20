//
// Created by oryakov on 12/20/18.
//

#include "DefineVarCommand.h"


int DefineVarCommand::doCommand(string commandOperation) {
    string var;
    string bind = "bind";
    bool isBind = false;

    // get the var name
    var = findVarInLine(commandOperation);
    if (var.empty()) {
        throw "var not found";
    }
    // check if the word "bind" appears
    size_t found = commandOperation.find(bind);
    if (found != string::npos) {
        isBind = true;
    }
    if (isBind) {
        // create a new symbol: var and the value 0
        symbolTable.insert(pair<string, double>(var, 0));
    } else {
        // if "bind" doesn't appear
        string varLine = commandOperation;
        varLine.erase(0, var.size());
        string varToFind = findVarInLine(varLine);
        if (!varToFind.empty()) {
            // create a new symbol: var and the value of an already existing var
            if (symbolTable.count(varToFind)) {
                double newValue = symbolTable.at(varToFind);
                symbolTable.insert(pair<string, double>(var, newValue));
            } else {
                throw "wrong var";
            }
        } else {
            // calculate the expression after the '=', and create a new symbol"
            // var and the calculated value of the expression
        }
    }


}

string DefineVarCommand::findVarInLine(string &line) {
    string var;
    bool foundVar = false;
    for (int i = 0; i < vars.size(); ++i) {
        var = vars[i];
        // Find first occurrence of the var
        size_t found = line.find(var);
        if (found != string::npos) {
            foundVar = true;
            break;
        }
    }
    if (!foundVar) {
        var.clear();
    }
    return var;
}
