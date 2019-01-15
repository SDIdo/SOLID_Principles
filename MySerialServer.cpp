//
// Created by idox on 1/3/19.
//

#include "MySerialServer.h"
#include <thread>

void MySerialServer::open(int port, ClientHandler *clientHandler) {
    this->clientHandler = clientHandler;
    this->port = port;
    pthread_t threadID;
    pthread_create(&threadID, nullptr, runSerialServer, this);
    pthread_join(threadID, nullptr);
}

/**
 * This method runs the server: reads information from client from
 * the socket, and updates samples map and symbol map accordingly.
 * @param a void pointer.
 * @return void pointer.
 */
void *MySerialServer::runSerialServerFunc(void *arguments) {
    int clilen;
    int enable = 1;
    struct sockaddr_in serv_addr, cli_addr;

    // open sockets to communicate with clients.
    while(true) {
        /* First call to socket() function */
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0){
            perror("Cannot reuse address");
            exit(1);
        }

        if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) != 0){
            perror("Cannot reuse port");
            exit(1);
        }

        if (this->sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        /* Initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        serv_addr.sin_port = htons(this->port);

        /* Now bind the host address using bind() call.*/
        if (bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }
        /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */

        cout << "Listening\n";
        listen(this->sockfd, 5);
        clilen = sizeof(cli_addr);
        /* Accept actual connection from the client */
        this->sockfd = accept(this->sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        if (this->sockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        cout << "HERE WITH NEW CLIENT!\n";
        cout << "Success\n";
        this->clientHandler->handleClient(&this->sockfd);
        cout << "YEAH\n";
        close(sockfd); // close the socket.
    }
}

/**
 * This method is used by the pthread to run the opened server.
 * @param a void pointer.
 * @return void pointer.
 */
void *MySerialServer::runSerialServer(void *a) {
    return ((MySerialServer *) a)->runSerialServerFunc(a);
}


void MySerialServer::stop() {

}

void MySerialServer::start() {

}