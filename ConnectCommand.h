//
// Created by noa on 12/25/18.
//
#include "Command.h"

#ifndef MILESTONE1_CONNECTCOMMAND_H
#define MILESTONE1_CONNECTCOMMAND_H


class ConnectCommand: public Command {
public:

    virtual int doCommand(vector<string> commandOperation, int index);

    void connectToServer(string ip, int port);

    static void sendData(string path, double value, int sockfd);

};


#endif //MILESTONE1_CONNECTCOMMAND_H
