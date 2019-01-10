//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_DFS_H
#define PROJECTPART2_DFS_H

#include <string>
#include <iostream>
#include <vector>
#include "Searchable.h"
#include "Searcher.h"

class DFS : public Searcher {
    int nodesEvaluated;
public:
    DFS() = default;
    ~DFS() = default;
    virtual std::string search(Searchable<Entry> searchable){
        vector<int> sol = searchable.printAllPaths(source, dest);
        for (std::vector<int>::iterator it = sol.begin(); it != sol.end(); ++it)
            std::cout << ' ' << *it;


        return "Done";
    }
    virtual int getNumberOfNodesEvaluated() {
        return this->nodesEvaluated;
    }
};


#endif //PROJECTPART2_DFS_H
