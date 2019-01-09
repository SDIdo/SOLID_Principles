//
// Created by idox on 1/9/19.
//

#ifndef RWS_IO_H
#define RWS_IO_H
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>      // std::fstream
using std::string;
using std::ifstream;
using std::fstream;

class IO {
public:
    static int write(string path);
    static int writeMap(string path, std::map<string, string>&);
    static int read(string path, int &sum);
    static int readMap(string path, std::map<string, string>&);      //scat it's string string
};


#endif //RWS_IO_H
