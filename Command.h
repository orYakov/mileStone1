//
// Created by oryakov on 12/16/18.
//

#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

#include <iostream>

using namespace std;

class Command {
public:
    virtual int doCommand(string commandOperation);
};


#endif //MILESTONE1_COMMAND_H
