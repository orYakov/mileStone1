//
// Created by oryakov on 12/24/18.
//

#include "DefinitionCommand.h"
#include "MapHolder.h"
#include "Parser.h"
#include <mutex>
#include "ConnectCommand.h"

int DefinitionCommand::doCommand(vector<string> commandOperation, int index) {
    MapHolder* mapHolder = MapHolder::getInstance();
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    string var = commandOperation[index];
    string varPath = mapHolder->getPathByVar(var);
    ShuntingYard shuntingYard;
    // get the value of the expression that after the "="
    double newValue = shuntingYard.createExpression(commandOperation[index + 2])->calculate();
    int sockfd;
    mutex mutex1;
    mutex1.lock();
    mapHolder->setVarValue(var, newValue);
    mapHolder->setPathValue(varPath, newValue);
    sockfd = mapHolder->getSockfd();
    ConnectCommand::sendData(varPath, newValue, sockfd);
    mutex1.unlock();

    return resIndex;
}
///