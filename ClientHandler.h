//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_CLIENTHANDLER_H
#define PROJECTPART2_CLIENTHANDLER_H

#include <string>

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int *sockfd) = 0;
    virtual ~ClientHandler() = default;
};

#endif //PROJECTPART2_CLIENTHANDLER_H
