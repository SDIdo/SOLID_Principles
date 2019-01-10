//
// Created by idox on 1/10/19.
//

#ifndef TEST_IO_H
#define TEST_IO_H


#include <string>
#include <map>
#include <unordered_map>
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
    static int writeMap(string path, std::unordered_map<string, string>&);
    static int writeKeyVal(string path, string key, string val);
    static int readMap(string path, std::unordered_map<string, string>&);      //scat it's string string
};

#endif //TEST_IO_H
