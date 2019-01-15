//
// Created by idox on 1/3/19.
//

#include "MyParallelServer.h"

struct A {
    ClientHandler *ch;
    int *sock;
};

MyParallelServer::~MyParallelServer() = default;

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
    timeval servertimeout;
    servertimeout.tv_sec = 1;
    servertimeout.tv_usec = 0;
    timeval clienttimeout;
    clienttimeout.tv_sec = 0;
    clienttimeout.tv_usec = 0;
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
    listen(this->sockfd, SOMAXCONN);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    while (true) {
        int newSocket = accept(this->sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        if (newSocket < 0) {
            // if there was no connection for the time period that was set.
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
                this->stop();
                return;
            } else {
                perror("other error");
                exit(3);
            }
        }

        pthread_t threadID;
        A *a = new A();
        a->sock = &newSocket;
        a->ch = this->clientHandler;
        pthread_create(&threadID, nullptr, &clientHandling, (void *) a);
        this->pthreadWorkers.push_back(threadID);
        // set timer for socket for the next clients.
        setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &servertimeout, sizeof(servertimeout));
        setsockopt(newSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &clienttimeout, sizeof(clienttimeout));
    }
}

void MyParallelServer::stop() {
    cout << "Welcome to bye\n";
    for (pthread_t pthreadId : this->pthreadWorkers) {
        pthread_join(pthreadId, nullptr);
    }
    cout << "All pthread have been joined.\n";
}

void MyParallelServer::start() {

}

void *MyParallelServer::clientHandling(void *a) {
    cout << "handle started\n";
    A *b = (A *) a;
    b->ch->handleClient(b->sock);
    cout << "handle ended\n";
    close(*b->sock);
    delete(b);
//    pthread_exit(&b->pthreadID);
}
