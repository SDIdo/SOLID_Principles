//
// Created by roy on 1/3/19.
//

#include <unistd.h>
#include "FileCacheManager.h"

FileCacheManager::FileCacheManager(string filePath) {
    this->myFilePath = filePath;
    IO::readMap(filePath, this->cache);
}

void FileCacheManager::set(string *problem, string *solution) {
    cache[*problem] = *solution;
    IO::writeKeyVal(this->myFilePath, *problem, *solution);
}

bool FileCacheManager::check(string *problem) {
    cout << "checking in map\n";
    return !(cache.find(*problem) == cache.end());
}

string FileCacheManager::get(string *problem) {
    if (check(problem)) {        //check in map
        return this->cache[*problem];
    }
}
