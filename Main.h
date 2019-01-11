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
#include "Algos/DFSb.h"
#include "Algos/MyClientHandler.h"
#include "Algos/MatrixGraph.h"

namespace boot {

    class Main {
    public:
        int main(int port) {
            // create serial server, string reverser, file cache manager.
            server_side::Server *server = new MySerialServer;


//            Searchable<> searchable = new MatrixGraph();

            Searcher<Entry,vector<State<Entry> *>> *dfsSearcher = new DFSb<Entry>();
            Solver<Searchable<Entry>,vector<State<Entry> *>> *searcherSolver = new SearcherSolver<Entry, vector<State<Entry> *>>(dfsSearcher);


            CacheManager<string, string> *cacheManager = new FileCacheManager("try.txt");
            // create the handling of clients.
            ClientHandler *clientHandler = new MyClientHandler<Entry, string, string>(searcherSolver, cacheManager);
            // open server with port and client handler.
            server->open(port, clientHandler);

            server->stop();

//        string str = "1,2\r\n5,7\r\n0,0\r\n1,1\r\nend\r\n";
//        ClientHandler *myClientHandler = new MyClientHandler<Entry, vector<State<Entry> *>, string>();
//        vector<vector<int>> vector1 = {{1,2},{5,7}};
//        MatrixGraph *matrixGraph = new MatrixGraph(2,2,new Entry(0,0), new Entry(1,1),vector1);
//        DFSb<Entry> dfs;
//        vector<State<Entry>*> vec = dfs.search(matrixGraph);
//        for (State<Entry>* state : vec) {
//                cout  << " i:"<< state->getState()->getI()  << " j:"<< state->getState()->getJ() << " cost:"<< state->getCost();
//        }

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
