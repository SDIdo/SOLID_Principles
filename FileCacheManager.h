//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_FILECACHEMANAGER_H
#define PROJECTPART2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <iostream>
#include <cstring>
#include "Algos/IO.h"

using namespace std;

/**
 * This class saves answers for a problem in a map, and could check if
 * a solution is saved. It also writes given solutions to files, so
 * then can be accessed in the future.
 */
class FileCacheManager : public CacheManager<string, string>{
    string myFilePath;
public:
    FileCacheManager(string filePath);
    ~FileCacheManager() = default;

    virtual void set(string *problem, string solution);
    virtual string get(string *problem);
    virtual bool check(string *problem);
};

#endif //PROJECTPART2_FILECACHEMANAGER_H
