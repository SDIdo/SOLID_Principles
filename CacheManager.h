//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_CACHEMANAGER_H
#define PROJECTPART2_CACHEMANAGER_H

using namespace std;

/**
 * Interface of cache manager.
 * Cache managers can handle the storing of data
 * related to problems and solutions.
 * Given a problem, the cache could be checked for
 * a solution, and also getting it. Also solved problems
 * could be stored in cache with a solution.
 * @tparam Problem problem for the storage.
 * @tparam Solution solution for the storage.
 */
template <class Problem, class Solution>
class CacheManager{
public:
    virtual Solution get(Problem *problem) = 0; // gets a solution to the problem.
    virtual void set(Problem *problem, Solution *solution) = 0; // sets a solution to the given problem.
    virtual bool check(Problem *problem) = 0; // check if there is a solution cached for the problem.
    virtual ~CacheManager() = default;
};

#endif //PROJECTPART2_CACHEMANAGER_H
