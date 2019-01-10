//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_MYCLIENTHANDLER_H
#define PROJECTPART2_MYCLIENTHANDLER_H

#include "../ClientHandler.h"
#include "../Solver.h"
#include "../CacheManager.h"
#include "Searchable.h"
#include "Entry.h"
#include <string>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <vector>

using namespace std;

class MyClientHandler : public ClientHandler {
    Solver<Searchable<Entry>, string> *solver;
    CacheManager<Searchable<Entry>, string> *cacheManager;
public:
    MyClientHandler(Solver<Searchable<Entry>, string> *solver,
            CacheManager<Searchable<Entry>, string> *cacheManager) {
        this->solver = solver;
        this->cacheManager = cacheManager;
    }
    ~MyClientHandler() = default;
    void handleClient(int sockfd);
    vector<int> line_parse(string line);
};


#endif //PROJECTPART2_MYCLIENTHANDLER_H
