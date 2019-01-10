//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_CACHEMANAGER_H
#define PROJECTPART2_CACHEMANAGER_H

#include <map>
#include <string>

using namespace std;

template <class Problem, class Solution>
class CacheManager{

protected:
    map<Problem, Solution> cache;
public:
    virtual Solution get(Problem *problem) = 0; // gets a solution to the problem.
    virtual void set(Problem *problem, Solution solution) = 0; // sets a solution to the given problem.
    virtual bool check(Problem *problem) = 0; // check if there is a solution cached for the problem.
};

#endif //PROJECTPART2_CACHEMANAGER_H
