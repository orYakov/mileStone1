//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_PRINTCOMMAND_H
#define MILESTONE1_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command {
public:
    virtual int doCommand(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_PRINTCOMMAND_H
