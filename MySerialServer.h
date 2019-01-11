//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_MYSERIALSERVER_H
#define PROJECTPART2_MYSERIALSERVER_H

#include "Server.h"
#include <string>
#include <iostream>
#include "unistd.h"

class MySerialServer : public server_side::Server {
    ClientHandler *clientHandler;
    int port;
public:
    MySerialServer() = default;
    ~MySerialServer() = default;
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    void start();

    void* runSerialServerFunc(void *a);
    static void* runSerialServer(void *a);

};


#endif //PROJECTPART2_MYSERIALSERVER_H
