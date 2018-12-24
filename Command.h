//
// Created by oryakov on 12/16/18.
//

#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

#include <iostream>
#include <vector>
#include "ShuntingYard.h"

using namespace std;

class Command {
public:
    virtual int doCommand(vector<string> commandOperation, int index) = 0;
};


#endif //MILESTONE1_COMMAND_H
