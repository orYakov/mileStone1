//
// Created by oryakov on 12/22/18.
//

#ifndef MILESTONE1_LOOPCOMMAND_H
#define MILESTONE1_LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser {
public:
    virtual int doCommand(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_LOOPCOMMAND_H
///