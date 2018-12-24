//
// Created by oryakov on 12/20/18.
//

#include "DefineVarCommand.h"
#include "MapHolder.h"
#include "Parser.h"

int DefineVarCommand::doCommand(vector<string> commandOperation, int index) {
    MapHolder* mapHolder = MapHolder::getInstance();
    string var;
    string bind = "bind";
    bool isBind = false;
    int resIndex = Parser::getReturnIndex(commandOperation, index);




    if (commandOperation[index] == "var") {
        commandOperation.erase(commandOperation.begin());
    }
    // get the var name
    var = commandOperation[index];
    if (var.empty()) {
        throw "var not found";
    }
    // check if the word "bind" appears
    //if (commandOperation.size() == 4) { // number of arguments including "bind"
        if (bind == commandOperation[index + 2]) {
            isBind = true;
        }
    //}
    if (isBind) {
        // create a new symbol: var and the value 0
        mapHolder->setVarValue(var, 0);
//        symbolTable[var] = 0;
        mapHolder->setVarPath(var, commandOperation[index + 3]);
//        varAndPathMap[var] = commandOperation[3];
        mapHolder->setPathValue(commandOperation[index + 3], 0); // TODO TODO
//        pathAndValueMap[commandOperation[3]] = 0; // TODO TODO
    } else {
        // if "bind" doesn't appear
        string varToFind = commandOperation[index + 2]; // [0] is var, [1] is "=", [2] is another var

        // create a new symbol: var and the value of an already existing var
        if (mapHolder->getSymbolTable().count(varToFind)) {
            double newValue = mapHolder->getSymbolTable().at(varToFind);
//            double newValue = symbolTable.at(varToFind);
            mapHolder->setVarValue(var, newValue);
//            symbolTable[var] = newValue;
//            symbolTable.insert(pair<string, double>(var, newValue));
        } else {
            // calculate the expression after the '=', and create a new symbol"
            // var and the calculated value of the expression
            string toEvaluate = commandOperation[index + 2];
            ShuntingYard shuntingYard;
            Expression* expression = shuntingYard.createExpression(toEvaluate);
            double newValue = expression->calculate();
            delete expression;
//            symbolTable[var] = newValue;
            mapHolder->setVarValue(var, newValue);
//            symbolTable.insert(pair<string, double>(var, newValue));
        }
    }

    return resIndex;
}


//string DefineVarCommand::findVarInLine(string &line) {
//    string var;
//    bool foundVar = false;
//    for (int i = 0; i < vars.size(); ++i) {
//        var = vars[i];
//        // Find first occurrence of the var
//        size_t found = line.find(var);
//        if (found != string::npos) {
//            foundVar = true;
//            break;
//        }
//    }
//    if (!foundVar) {
//        var.clear();
//    }
//    return var;
//}
