//
// Created by idox on 1/4/19.
//

#ifndef ALGOS_SEARCHER_H
#define ALGOS_SEARCHER_H
#include "Graph.h"
#include <string>
using namespace std;
template<class Solution>
class Searcher {
public:
    virtual Solution search(Graph &graph, int source, int dest) = 0; //scat! in searcher to string!
    virtual int getNumberOfNodesEvaluated() = 0;
};


#endif //ALGOS_SEARCHER_H
