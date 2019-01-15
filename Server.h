//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_SERVER_H
#define PROJECTPART2_SERVER_H

#include "ClientHandler.h"
#include <netinet/in.h>
#include <string.h>

/**
 * Interface of Server.
 * Each server could connect on a different port and have
 * different client handling protocols.
 */

namespace server_side {
    class Server {
    protected:
        int sockfd;
    public:
        virtual void open(int port, ClientHandler *clientHandler) = 0;
        virtual void stop() = 0;
        virtual ~Server() = default;
    };
}

#endif //PROJECTPART2_SERVER_H
