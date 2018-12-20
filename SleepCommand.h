//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_SLEEPCOMMAND_H
#define MILESTONE1_SLEEPCOMMAND_H
#include "Command.h"

class SleepCommand : Command {
public:
    virtual int doCommand(vector<string> commandOperation);
};


#endif //MILESTONE1_SLEEPCOMMAND_H
