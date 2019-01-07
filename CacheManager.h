//
// Created by idox on 1/5/19.
//

#ifndef CACHE_CACHEMANAGER_H
#define CACHE_CACHEMANAGER_H
#include <string>
#include <map>
using namespace std;

class CacheManager {
protected:
    map<string, string> cache;
public:
    virtual void set(string problem, string solution) = 0;
    virtual string get(string problem) = 0;
    virtual bool check(string problem) = 0;
};


#endif //CACHE_CACHEMANAGER_H
