//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_MAIN_H
#define PROJECTPART2_MAIN_H


#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "Solver.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"

namespace boot {

    class Main {
    public:
        int main(int port) {
            // create serial server, string reverser, file cache manager.
            server_side::Server *server = new MySerialServer;
            Solver<string, string> *strRev = new StringReverser();
            CacheManager<string, string> *cacheManager = new FileCacheManager("try.txt");
            // create the handling of clients.
            ClientHandler *clientHandler = new MyTestClientHandler(strRev, cacheManager);
            // open server with port and client handler.
            server->open(port, clientHandler);

            server->stop();

        }
    };
}
//            while (true) {
//            string userInput;
//            getline(cin, userInput);
////                if server->stop() {
//                    break;
////                }
////            }
////            return 0;
//        }
//
//        //            string a = "HOME";
////            cout << strRev->solve(a);



#endif //PROJECTPART2_MAIN_H
