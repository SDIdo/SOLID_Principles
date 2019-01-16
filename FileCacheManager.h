//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_FILECACHEMANAGER_H
#define PROJECTPART2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <iostream>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <string>
#include "Algos/IO.h"

using namespace std;

/**
 * This class saves answers for a problem in a map, and could check if
 * a solution is saved. It also writes given solutions to files, so
 * answers could be accessed to in the future.
 */
class FileCacheManager : public CacheManager<string, string> {
    unordered_map<string, string> cache;
    string myFilePath;
    mutex m;
public:
    /**
     * Constructor of the file cache manager, receives a file path. if
     * the file exists, the manager read the solutions from it to the cache.
     * @param filePath string of the file path.
     */
    FileCacheManager(string filePath) {
        this->myFilePath = filePath;
        IO::readMap(filePath, this->cache);
    }
    /**
     * Destructor of the cache manager.
     */
    ~FileCacheManager() = default;

    /**
     * This method sets a new problem-solution pair to the map of cached solutions.
     * @param problem string of the given problem.
     * @param solution string of the given solution to the problem.
     */
    virtual void set(string *problem, string *solution) {
        lock_guard<mutex> guard(this->m);
        this->cache[*problem] = *solution;
        IO::writeKeyVal(this->myFilePath, *problem, *solution);
    }

    /**
     * This method returns the solution to a given problem.
     * @param problem string of the given problem.
     * @return answer for the problem.
     */
    virtual string get(string *problem) {
        lock_guard<mutex> guard(this->m);
        return this->cache[*problem];

    }

    /**
     * This method checks if a solution exists in cache for the given problem.
     * @param problem given problem for the check.
     * @return true if there exists a solution cached to the problem, else false.
     */
    virtual bool check(string *problem) {
        lock_guard<mutex> guard(this->m);
        cout << *problem;
        if (this->cache[*problem] != "") {
            return true;
        }
        this->cache.erase(*problem);
        return false;
    }
};

#endif //PROJECTPART2_FILECACHEMANAGER_H
