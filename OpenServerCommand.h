//
// Created by oryakov on 12/23/18.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"

class OpenServerCommand : public Command {
    vector<string> pathes;
public:
    virtual int doCommand(vector<string> commandOperation, int index);
    void createServer(int port, int waitTime);
    void initPathes();
    vector<string> littleLexer(string line, char c);
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
///