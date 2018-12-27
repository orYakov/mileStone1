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
    MapHolder* mapHolder = MapHolder::getInstance();
    ShuntingYard shuntingYard;
    string strPort = commandOperation[index + 1];
    string strWaitTime = commandOperation[index + 2];
    int port = (int) (shuntingYard.createExpression(strPort)->calculate());
    int waitTime = (int) (shuntingYard.createExpression(strWaitTime)->calculate());
    //cout << "starting to create server" <<endl;
    bool toDetach = false;
    std::thread serverThread(createServer, port, waitTime, &toDetach, &mapHolder);
//    while (true) {
//        if (toDetach) {
//            break;
//        }
//    }
//    if (toDetach) {
//        serverThread.detach();
//    }
    serverThread.detach();
    //createServer(port, waitTime);

    return resIndex;
}

void OpenServerCommand::initPathes(vector<string> &pathes) {
    pathes.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    pathes.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    pathes.push_back("/instrumentation/altimeter/pressure-alt-ft");
    pathes.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    pathes.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    pathes.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    pathes.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    pathes.push_back("/instrumentation/encoder/indicated-altitude-ft");
    pathes.push_back("/instrumentation/encoder/pressure-alt-ft");
    pathes.push_back("/instrumentation/gps/indicated-altitude-ft");
    pathes.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    pathes.push_back("/instrumentation/gps/indicated-vertical-speed");
    pathes.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    pathes.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    pathes.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    pathes.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    pathes.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    pathes.push_back("/controls/flight/aileron");
    pathes.push_back("/controls/flight/elevator");
    pathes.push_back("/controls/flight/rudder");
    pathes.push_back("/controls/flight/flaps");
    pathes.push_back("/controls/engines/engine/throttle");
    pathes.push_back("/engines/engine/rpm");
}


void OpenServerCommand::createServer(int port, int waitTime, bool *toDetach, MapHolder** pMapHolder) {
    mutex mutex1;
    vector<string> pathes;
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    initPathes(pathes);

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        throw "cannot open socket";
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
    cout<<"Try to connect"<<endl;
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);
    cout<<"connection succesful"<< endl;
    *toDetach = true; //TODO delete this
    if (newsockfd < 0) {
        perror("ERROR on accept");
        throw "error in accepting socket";
    }

    /* If connection is established then start communicating */
    while (true) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            throw "cannot read socket";
        }
        *toDetach = true;

        //MapHolder* mapHolder = MapHolder::getInstance();
        string curBuffer = buffer;
        /*
        vector<string> lexedBuffer = littleLexer(curBuffer, ',');
        for (int i = 0; i < lexedBuffer.size(); ++i) {
            string path = pathes[i];
            double pathValue = std::stod(lexedBuffer[i]);
            mutex1.lock();
            //mapHolder->setPathValue(path, pathValue);
            (*pMapHolder)->setPathValue(path, pathValue);
            mutex1.unlock();
        }
         */

        printf("Here is the message: %s\n", buffer);

        /* Write a response to the client */
        n = write(newsockfd, "I got your message", 18);

        if (n < 0) {
            perror("ERROR writing to socket");
            throw "error writing to socket";
        }
        //sleep(1 / waitTime);

        if ((*pMapHolder)->isStopThreadLoop()) {
            break;
        }

    }
}

vector<string> OpenServerCommand::littleLexer(string line, char c) {
    vector<string> res;
    char delimiter = c;
    string token;
    int pos = 0;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + 1);
        res.push_back(token);
    }
}


///