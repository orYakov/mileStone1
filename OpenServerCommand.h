//
// Created by oryakov on 12/23/18.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"
#include "MapHolder.h"

class OpenServerCommand : public Command {
    //vector<string> pathes;
public:
    virtual int doCommand(vector<string> commandOperation, int index);
    static void createServer(int port, int waitTime, MapHolder* pMapHolder);
    static void initPathes(vector<string> &pathes);
    static vector<string> littleLexer(string line, char c);
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
///