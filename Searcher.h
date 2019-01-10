//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_SEARCHER_H
#define PROJECTPART2_SEARCHER_H

#include "Searchable.h"
#include <string>

using namespace std;

template <class Solution>
class Searcher {
public:
    virtual Solution search(Searchable<class T> *searchable) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //PROJECTPART2_SEARCHER_H
