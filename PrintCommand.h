//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_PRINTCOMMAND_H
#define MILESTONE1_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : Command {
    virtual int doCommand(vector<string> commandOperation);
};


#endif //MILESTONE1_PRINTCOMMAND_H
