//
// Created by noa on 12/25/18.
//



#include "ConnectCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include "MapHolder.h"
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>


struct thread_data {
    int port;
    string ip;
};

void *runClient(void *c) {
    struct thread_data *my_thread_data;
    my_thread_data = (struct thread_data *) c;
    int port = my_thread_data->port;
    string ip = my_thread_data->ip;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    string buffer;

    portno = port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    const char *x = ip.c_str();
    server = gethostbyname(x);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    /* Now ask for a message from the user, this message
       * will be read by server
    */
//if there is new data
    while (true) {
        if (.getIsNewData()) {
            // pthread_mutex_lock(&mutex);
            buffer = "set" + data.getBind()->getName() + to_string(data.getBind()->getValue());
            /* Send message to the server */
            const char *chr = buffer.c_str();
            n = write(sockfd, chr, strlen(chr));
            data.setIsNewData(false);
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            // pthread_mutex_unlock(&mutex);
        }
    }

    /* Now read server response */
//    bzero(buffer, 256);
//    n = read(sockfd, buffer, 255);
//
//    if (n < 0) {
//        perror("ERROR reading from socket");
//        exit(1);
//    }

    cout << buffer;
    return 0;
}

double ConnectCommand::doCommand() {
    pthread_t thread;
    int rc;
    thread_data *my_thread_data = new thread_data();
    my_thread_data->port = this->port;
    my_thread_data->ip = this->ip;
    rc = pthread_create(&thread, nullptr, runClient, my_thread_data);
    if (rc) {
        cout << "Error! unable to create thread";
        exit(1);
    }
}

ConnectCommand::ConnectCommand(string ip, int port) {
    this->ip = ip;
    this->port = port;
}

void ConnectCommand::sendData(string path, double value) {

}
//