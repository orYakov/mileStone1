//
// Created by oryakov on 12/22/18.
//

#include "LoopCommand.h"

int LoopCommand::doCommand(vector<string> commandOperation, int index) {
    index = 0;
    MapHolder* mapHolder = MapHolder::getInstance();
    string strExp1 = commandOperation[1];
    string strExp2 = commandOperation[3];
    double firstExp = shuntingYard.createExpression(strExp1)->calculate();
    double secondExp = shuntingYard.createExpression(strExp2)->calculate();
    condition = commandOperation[2];
    // delete until first command
    commandOperation.erase(commandOperation.begin(), commandOperation.begin() + 6);
    Parser parser(commandOperation);


    if (condition == "==") {
        while (firstExp == secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    } else if (condition == "!=") {
        while (firstExp != secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    } else if (condition == "<=") {
        while (firstExp <= secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    } else if (condition == ">=") {
        while (firstExp >= secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    } else if (condition == "<") {
        while (firstExp < secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    } else if (condition == ">") {
        while (firstExp > secondExp) {
            parser.parse();
            firstExp = shuntingYard.createExpression(strExp1)->calculate();
            secondExp = shuntingYard.createExpression(strExp2)->calculate();
        }
    }
    return 0;
}
