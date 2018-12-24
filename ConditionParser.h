//
// Created by oryakov on 12/22/18.
//

#ifndef MILESTONE1_CONDITIONPARSER_H
#define MILESTONE1_CONDITIONPARSER_H

#include "Command.h"
#include "Parser.h"
#include "MapHolder.h"
#include "ShuntingYard.h"

class ConditionParser : public Command {
protected:
    ShuntingYard shuntingYard;
    string condition;
};


#endif //MILESTONE1_CONDITIONPARSER_H
