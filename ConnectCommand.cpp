////
//// Created by noa on 12/25/18.
////
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include "ConnectCommand.h"
#include "Parser.h"
#include "MapHolder.h"

int ConnectCommand::doCommand(vector<string> commandOperation, int index) {
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    ShuntingYard shuntingYard;
    string ip = commandOperation[index + 1]; //stays as string
    string strPort = commandOperation[index + 2];
    int port = (int) (shuntingYard.createExpression(strPort)->calculate());
    connectToServer(ip, port);


    return resIndex;
}

void ConnectCommand::connectToServer(string ip, int port) {
    //mutex mutex1;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    const char *ipCstyle = ip.c_str();
    server = gethostbyname(ipCstyle);

    if (server == nullptr) {
        perror("ERROR, no such host");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    cout << "trying to connect. press something" << endl;
    scanf("%*c");
    //mutex1.unlock();
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <
        0) {
        perror("ERROR connecting");
        throw "ERROR connecting";
    }
    cout << "connect successful" << endl;

    MapHolder *mapHolder = MapHolder::getInstance();
    mapHolder->setSockfd(sockfd);
}

void ConnectCommand::sendData(string path, double value, int sockfd) {
    if (sockfd == -1) {
        return;
    }
    /* Now ask for a message from the user, this message
       * will be read by server
    */
    ssize_t n;
    char buffer[256];
    string message;
    string strValue = to_string(value);
    message = "set " + path + " " + strValue + " \r\n";
    const char *messageCstyle = message.c_str();
    bzero(buffer, 256);
    strcpy(buffer, messageCstyle);

    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

}
