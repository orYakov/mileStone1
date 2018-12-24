//
// Created by oryakov on 12/22/18.
//

#include "IfCommand.h"

int IfCommand::doCommand(vector<string> commandOperation, int index) {
    index = 0;
    double firstExp = shuntingYard.createExpression(commandOperation[1])->calculate();
    double secondExp = shuntingYard.createExpression(commandOperation[3])->calculate();
    condition = commandOperation[2];
    Parser parser(commandOperation);

    if (condition == "==") {
        if (firstExp == secondExp) {
            parser.parse();
        }
    } else if (condition == "!=") {
        if (firstExp != secondExp) {
            parser.parse();
        }
    } else if (condition == "<=") {
        if (firstExp <= secondExp) {
            parser.parse();
        }
    } else if (condition == ">=") {
        if (firstExp >= secondExp) {
            parser.parse();
        }
    } else if (condition == "<") {
        if (firstExp < secondExp) {
            parser.parse();
        }
    } else if (condition == ">") {
        if (firstExp > secondExp) {
            parser.parse();
        }
    }
    return 0;
}
