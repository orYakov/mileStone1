//
// Created by oryakov on 12/20/18.
//

#include "DefineVarCommand.h"
#include "MapHolder.h"
#include "Parser.h"
#include <mutex>

int DefineVarCommand::doCommand(vector<string> commandOperation, int index) {
    MapHolder* mapHolder = MapHolder::getInstance();
    string var;
    string bind = "bind";
    bool isBind = false;
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    mutex mutex1;



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
        // create a new symbol
        mutex1.lock();
        mapHolder->setVarPath(var, commandOperation[index + 3]);
        double pathValue;
        if (mapHolder->getPathAndValueMap().count(commandOperation[index + 3])) {
            pathValue = mapHolder->getValueByPath(commandOperation[index + 3]);
        } else {
            pathValue = 0;
        }
        mapHolder->setVarValue(var, pathValue);
        mutex1.unlock();
        //mapHolder->setPathValue(commandOperation[index + 3], 0); // TODO TODO

    } else {
        // if "bind" doesn't appear
        string varToFind = commandOperation[index + 2]; // [0] is var, [1] is "=", [2] is another var

        // create a new symbol: var and the value of an already existing var
        mutex1.lock();
        map<string, double> symbolTableCopy = mapHolder->getSymbolTable();
        mutex1.unlock();
        if (symbolTableCopy.count(varToFind)) {
            mutex1.lock();
            double newValue = mapHolder->getSymbolTable().at(varToFind);
            mapHolder->setVarValue(var, newValue);
            mutex1.unlock();
        } else {
            // calculate the expression after the '=', and create a new symbol"
            // var and the calculated value of the expression
            string toEvaluate = commandOperation[index + 2];
            ShuntingYard shuntingYard;
            Expression* expression = shuntingYard.createExpression(toEvaluate);
            double newValue = expression->calculate();
            delete expression;
//            symbolTable[var] = newValue;
            mutex1.lock();
            mapHolder->setVarValue(var, newValue);
            mutex1.unlock();
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
///