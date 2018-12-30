//
// Created by oryakov on 12/23/18.
//

#include "OpenServerCommand.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include "MapHolder.h"
#include "Parser.h"
#include <mutex>

int OpenServerCommand::doCommand(vector<string> commandOperation, int index) {
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    MapHolder *mapHolder = MapHolder::getInstance();
    ShuntingYard shuntingYard;
    string strPort = commandOperation[index + 1];
    string strWaitTime = commandOperation[index + 2];
    int port = (int) (shuntingYard.createExpression(strPort)->calculate());
    int waitTime = (int) (shuntingYard.createExpression(
            strWaitTime)->calculate());
    //cout << "starting to create server" <<endl;
    std::thread serverThread(createServer, port, waitTime, mapHolder);
    serverThread.detach();



    //mapHolder->setServerThread(&serverThread);
    //serverThread.detach();
    //createServer(port, waitTime);

    return resIndex;
}

void OpenServerCommand::initPathes(vector<string> &pathes) {
    pathes.emplace_back(
            "/instrumentation/airspeed-indicator/indicated-speed-kt");
    pathes.emplace_back("/instrumentation/altimeter/indicated-altitude-ft");
    pathes.emplace_back("/instrumentation/altimeter/pressure-alt-ft");
    pathes.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    pathes.emplace_back(
            "/instrumentation/attitude-indicator/indicated-roll-deg");
    pathes.emplace_back(
            "/instrumentation/attitude-indicator/internal-pitch-deg");
    pathes.emplace_back(
            "/instrumentation/attitude-indicator/internal-roll-deg");
    pathes.emplace_back("/instrumentation/encoder/indicated-altitude-ft");
    pathes.emplace_back("/instrumentation/encoder/pressure-alt-ft");
    pathes.emplace_back("/instrumentation/gps/indicated-altitude-ft");
    pathes.emplace_back("/instrumentation/gps/indicated-ground-speed-kt");
    pathes.emplace_back("/instrumentation/gps/indicated-vertical-speed");
    pathes.emplace_back(
            "/instrumentation/heading-indicator/indicated-heading-deg");
    pathes.emplace_back(
            "/instrumentation/magnetic-compass/indicated-heading-deg");
    pathes.emplace_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    pathes.emplace_back("/instrumentation/turn-indicator/indicated-turn-rate");
    pathes.emplace_back(
            "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    pathes.emplace_back("/controls/flight/aileron");
    pathes.emplace_back("/controls/flight/elevator");
    pathes.emplace_back("/controls/flight/rudder");
    pathes.emplace_back("/controls/flight/flaps");
    pathes.emplace_back("/controls/engines/engine/throttle");
    pathes.emplace_back("/engines/engine/rpm");
}


void
OpenServerCommand::createServer(int port, int waitTime, MapHolder *pMapHolder) {
    vector<string> pathes;
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;

    initPathes(pathes);

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        throw "cannot bind socket";
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    cout << "Try to connect" << endl;
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);
    cout << "connection succesful" << endl;

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    while (true) {

        string curBuffer;
        while (curBuffer.find('\n') == string::npos) {
            char c;
            n = read(newsockfd, &c, 1);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            curBuffer += c;
        }


        curBuffer.pop_back(); //todo show michael
        curBuffer += ",";

        vector<string> lexedBuffer = littleLexer(curBuffer, ',');

        for (int i = 0; i < lexedBuffer.size(); ++i) {
            string path = pathes[i];

            try {
                double pathValue = std::stod(lexedBuffer[i]);
                pMapHolder->setPathValue(path, pathValue);
                for (auto &it : pMapHolder->getVarAndPathMap()) {
                    if (it.second == path) {
                        string varToUpdate = it.first;
                        pMapHolder->setVarValue(varToUpdate, pathValue);
                    }
                }
            } catch (std::exception &e) {
                cout << e.what() << endl;
            }
        }

    }
}

vector<string> OpenServerCommand::littleLexer(string line, char c) {
    vector<string> res;
    char delimiter = c;
    string token;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + 1);
        res.push_back(token);
    }
    return res;
}


///