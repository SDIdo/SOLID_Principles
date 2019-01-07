//
// Created by idox on 1/5/19.
//

#ifndef CACHE_FILECACHEMANAGER_H
#define CACHE_FILECACHEMANAGER_H
#include "CacheManager.h"
#include <iostream>
#include <zconf.h>
#include <cstring>

class FileCacheManager : public CacheManager{
    string myFilePath;
public:
    FileCacheManager(string filePath);
    ~FileCacheManager() = default;

    virtual void set(string problem, string solution);
    virtual string get(string problem);
    virtual bool check(string problem);

    int read();
    int write();
};


#endif //CACHE_FILECACHEMANAGER_H
