//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_DEFINEVARCOMMAND_H
#define MILESTONE1_DEFINEVARCOMMAND_H

#include "Command.h"
#include <map>
#include <vector>

class DefineVarCommand : public Command {
    map<string, double> symbolTable;
    string breaks, throttle, heading, airspeed, roll, pitch, rudder, aileron, elevator, alt, h0;
    vector<string> vars = {breaks, throttle, heading, airspeed, roll, pitch, rudder, aileron, elevator, alt, h0};
public:
    virtual int doCommand(string commandOperation);
    string findVarInLine(string &line);
};


#endif //MILESTONE1_DEFINEVARCOMMAND_H
