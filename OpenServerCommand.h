//
// Created by oryakov on 12/23/18.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"

class OpenServerCommand : public Command {
public:
    virtual int doCommand(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
