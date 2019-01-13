//
// Created by roy on 1/13/19.
//

#ifndef PROJECTPART2_MYPARALLELSERVER_H
#define PROJECTPART2_MYPARALLELSERVER_H


#include "../Server.h"
#include <string>
#include <thread>
#include <iostream>
#include "unistd.h"
#include "../Server.h"

class MyParallelServer : public server_side::Server {
    ClientHandler *clientHandler;
    int port;
public:
    MyParallelServer() = default;
    ~MyParallelServer() = default;
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    void start();

    void runParallelServer();
    static void* clientHandling(void * a);
};


#endif //PROJECTPART2_MYPARALLELSERVER_H
