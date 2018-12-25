//
// Created by oryakov on 12/24/18.
//

#include "DefinitionCommand.h"
#include "MapHolder.h"
#include "Parser.h"

int DefinitionCommand::doCommand(vector<string> commandOperation, int index) {
    MapHolder* mapHolder = MapHolder::getInstance();
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    string var = commandOperation[index];
    string varPath = mapHolder->getPathByVar(var);
    ShuntingYard shuntingYard;
    // get the value of the expression that after the "="
    double newValue = shuntingYard.createExpression(commandOperation[index + 2])->calculate();
    mapHolder->setVarValue(var, newValue);
    mapHolder->setPathValue(varPath, newValue);


    return resIndex;
}
///