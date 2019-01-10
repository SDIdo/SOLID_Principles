//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_MYTESTCLIENTHANDLER_H
#define PROJECTPART2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <string>
#include <unistd.h>
#include <strings.h>
#include <iostream>

using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;
public:
    MyTestClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager);
    ~MyTestClientHandler() = default;
    virtual void handleClient(int sockfd);
};


#endif //PROJECTPART2_MYTESTCLIENTHANDLER_H
