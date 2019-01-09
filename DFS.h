//
// Created by idox on 1/4/19.
//

#ifndef ALGOS_DFS_H
#define ALGOS_DFS_H
#include "Searcher.h"
#include <string>
using namespace std;
class DFS : public Searcher<std::string>{
public:
    DFS() = default;
    ~DFS() = default;

    virtual std::string search(Graph &graph, int source, int dest); //scat! in seacher to Graph.
    virtual int getNumberOfNodesEvaluated();
};


#endif //ALGOS_DFS_H
