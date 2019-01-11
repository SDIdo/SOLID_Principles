//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_IO_H
#define PROJECTPART2_IO_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>      // std::fstream
using std::string;
using std::ifstream;
using std::fstream;

class IO {
    static void splitToVecByDelim(std::vector<string> &keyVal, const string &info, const string &delimiter);
public:
    static int writeMap(string path, std::map<string, string>&);
    static int writeKeyVal(string path, string key, string val);
    static int readMap(string path, std::map<string, string>&);      //scat it's string string
};
#endif //PROJECTPART2_IO_H
