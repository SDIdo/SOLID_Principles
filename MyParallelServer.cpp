//
// Created by idox on 1/3/19.
//

#include "MyParallelServer.h"

struct A {
    ClientHandler *ch;
    int sock;
    pthread_t pthreadID;
};

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    this->clientHandler = clientHandler;
    this->port = port;
    this->runParallelServer();
}

/**
 * This method runs the server: reads information from client from
 * the socket, and updates samples map and symbol map accordingly.
 * @param a void pointer.
 * @return void pointer.
 */
void MyParallelServer::runParallelServer() {
    int clilen;
    int enable = 1;
    struct sockaddr_in serv_addr, cli_addr;

    // open sockets to communicate with clients.

    /* First call to socket() function */
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0) {
        perror("Cannot reuse address");
        exit(1);
    }

    if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) != 0) {
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
    listen(this->sockfd, SOMAXCONN);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    while (true) {
        int newSocket = accept(this->sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        if (newSocket < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        cout << "HERE WITH NEW CLIENT!\n";
        cout << "Success\n";

        pthread_t threadID;
        A *a = new A();
        a->sock = newSocket;
        a->ch = this->clientHandler;
        a->pthreadID = threadID;
        pthread_create(&threadID, nullptr, &clientHandling, (void *) a);
        cout << "Moving to next client listen\n";

    }
    close(this->sockfd); // close the socket.
}

void MyParallelServer::stop() {

}

void MyParallelServer::start() {

}

void *MyParallelServer::clientHandling(void *a) {
    A *b = (A *) a;
    b->ch->handleClient(b->sock);
    close(b->sock);
    pthread_exit(&b->pthreadID);
}
