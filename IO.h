//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_IO_H
#define PROJECTPART2_IO_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

using std::string;
using std::ifstream;
using std::fstream;
using std::vector;

/**
 * Class IO is responsible of reading to given map and writing to a file.
 */
class IO {
public:
    static int writeKeyVal(string path, string key, string val);
    static int readMap(string path, std::unordered_map<string, string> &);      //scat it's string string

    static string readServer(string path);
    static vector<string> readStringVectorServer(string path);
};

#endif //PROJECTPART2_IO_H
