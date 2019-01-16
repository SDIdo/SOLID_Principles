//
// Created by roy on 1/13/19.
//

#ifndef PROJECTPART2_MYPARALLELSERVER_H
#define PROJECTPART2_MYPARALLELSERVER_H


#include "../Server.h"
#include <string>
#include <thread>
#include <iostream>
#include <vector>
#include "unistd.h"
#include "../Server.h"

/**
 * MyParallelServer extends Server, therefore could create a server.
 * Used for parallel client handling on many threads.
 */
class MyParallelServer : public server_side::Server {
    ClientHandler *clientHandler;
    int port;
    vector<pthread_t> pthreadWorkers;
public:
    MyParallelServer() = default;
    virtual ~MyParallelServer();
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    void runParallelServer();
    static void* clientHandling(void * a);
};


#endif //PROJECTPART2_MYPARALLELSERVER_H
