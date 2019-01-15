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
#include "Algos/SearcherSolver.h"
#include "Algos/DFS.h"
#include "Algos/MyClientHandler.h"
#include "Algos/MatrixGraph.h"
#include "Algos/BFS.h"
#include "Algos/AStar.h"
#include "Algos/BestFirstSearch.h"
#include "Algos/MyParallelServer.h"
#include "Algos/MatrixTester.h"

namespace boot {

    /**
     * class Main is responsible for running the boot - setting
     * a server side for solving problems.
     */
    class Main {
    public:
        int main(int port) {
//            // create server.
//            server_side::Server *server = new MyParallelServer;
//            // create best searcher algorithm, and searcher solver (object adapter).
//            Searcher<Entry, string> *searcher = new AStar<Entry>();
//            Solver<Searchable<Entry>, string> *searcherSolver = new SearcherSolver<Entry, string>(searcher);
//
//            // create file cache manager.
//            CacheManager<string, string> *cacheManager = new FileCacheManager("try.txt");
//            // create the handling of clients with the searcher solver.
//            ClientHandler *clientHandler = new MyClientHandler<Entry, string, string>(searcherSolver, cacheManager);
//            // open server with port and client handler.
//            server->open(port, clientHandler);
//
//            delete (server);
//            delete (clientHandler);

        MatrixTester mt;
        mt.runTest();
            return 0;
        }
    };
}
#endif //PROJECTPART2_MAIN_H
