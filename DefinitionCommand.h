//
// Created by oryakov on 12/24/18.
//

#ifndef MILESTONE1_DEFINITIONCOMMAND_H
#define MILESTONE1_DEFINITIONCOMMAND_H


#include "Command.h"

class DefinitionCommand : public Command {
public:
    virtual int doCommand(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_DEFINITIONCOMMAND_H
///