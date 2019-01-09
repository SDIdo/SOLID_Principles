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

class MyClientHandler : public ClientHandler {
    Solver<Searchable<Entry>, string> *solver;
    CacheManager<Searchable<Entry>, string> *cacheManager;
public:
    void handleClient(int sockfd);
};


#endif //PROJECTPART2_MYCLIENTHANDLER_H
