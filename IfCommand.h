//
// Created by oryakov on 12/22/18.
//

#ifndef MILESTONE1_IFCOMMAND_H
#define MILESTONE1_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    virtual int doCommand(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_IFCOMMAND_H
///