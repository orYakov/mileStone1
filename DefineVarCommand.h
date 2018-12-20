//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_DEFINEVARCOMMAND_H
#define MILESTONE1_DEFINEVARCOMMAND_H

#include "Command.h"
#include <map>
class DefineVarCommand : public Command {
    map<string, double> symbolTable;
public:
    DefineVarCommand();
    void initSymbolTable();
};


#endif //MILESTONE1_DEFINEVARCOMMAND_H
