//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_FILECACHEMANAGER_H
#define PROJECTPART2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <iostream>
#include <cstring>
#include <mutex>
#include "Algos/IO.h"

using namespace std;

/**
 * This class saves answers for a problem in a map, and could check if
 * a solution is saved. It also writes given solutions to files, so
 * then can be accessed in the future.
 */
class FileCacheManager : public CacheManager<string, string> {
    string myFilePath;
    mutex m;
public:
    FileCacheManager(string filePath) {
        this->myFilePath = filePath;
        IO::readMap(filePath, this->cache);
    }

    ~FileCacheManager() = default;

    virtual void set(string *problem, string *solution) {
        lock_guard<mutex> guard(this->m);
        this->cache[*problem] = *solution;
        IO::writeKeyVal(this->myFilePath, *problem, *solution);
    }

    virtual string get(string *problem) {
        lock_guard<mutex> guard(this->m);
        return this->cache[*problem];

    }

    virtual bool check(string *problem) {
        lock_guard<mutex> guard(this->m);
        cout << "here in check with:\n";
        cout << *problem;
        if (this->cache[*problem] != "") {
            cout << "prob found!!!";
            return true;
        }
        cout << "prob not found!!!";
        this->cache.erase(*problem);
        return false;
    }
};

#endif //PROJECTPART2_FILECACHEMANAGER_H
