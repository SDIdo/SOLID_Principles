//
// Created by roy on 1/9/19.
//

#include <cstring>
#include "IO.h"

/**
 * Function recognize = sign as separator for first and second items in map
 * @param path - file address
 * @return - 0 upon success or 1 elsewise.
 */
int IO::readMap(string path, std::unordered_map<string, string> &myMap) {
    ifstream inFile;
    inFile.open(path, ifstream::in);
    if (!inFile) {
        perror("Could not find the file\n");
        return 1;
    }
    std::string info;
    std::string key;
    std::string value;
    std::vector<string> keyVal;
    int insertionCycle = 0;

    while (std::getline(inFile, info)) {
        std::cout << "Current info is: " << info << '\n';

        if (info.at(0) != '{' && info.at(0) != '$') {
            key += info;
            key += "\n";
        } else if (info.at(0) == '{'){
            value = info;
            myMap[key] = value;
            std::cout << key << ":" << value <<'\n';
            key = "";
            value = "";
        }

    }

//    while (std::getline(inFile, info)) {
//        std::cout << "Current info is: " << info << '\n';
//
//        if (insertionCycle == 0) {
//            key = info;
//            insertionCycle = 1;
//            continue;
//        }
//        value = info.substr(0, info.find("\r\n") - 1);
//        myMap[key] = value;
//        std::cout << key << ":" << value <<'\n';
//        key = "";
//        value = "";
//        insertionCycle = 0;
//    }
}

/**
 * Write map only after solver. Not if solution is found.
 * @param path - name of file
 * @param myMap - internal map
 * @return 0 if success, 1 if not.
 */
int IO::writeMap(string path, std::unordered_map<string, string> &myMap) {
    fstream outFile;
    outFile.open(path, ifstream::app);
    if (!outFile) {
        perror("Could not find the file\n");
        return 1;
    }
    string input;
    string key;
    string value;
    string delim;
    std::vector<string> splited;

    for (std::unordered_map<string, string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
        outFile << it->first;
        outFile << "$";
        outFile << it->second;
        outFile << "\r\n";
    }
    outFile.close();
    return 0;
}

/**
 * writing current instance of map to the file
 * @param path - file to write to
 * @param key - key in the map
 * @param value - value of the key
 * @return 0 if success, 1 otherwise.
 */
int IO::writeKeyVal(string path, string key, string val) {
    fstream outFile;
    outFile.open(path, ifstream::app);
    if (!outFile) {
        perror("Could not find the file\n");
        return 1;
    }
    outFile << key;
    outFile << "$";
    outFile << "\n";
    outFile << val;
    outFile << "\n";

    outFile.close();
    return 0;
}

void IO::splitToVecByDelim(std::vector<string> &dualVec, const string &toSplit, const string &delim) {
    std::cout << "[spliByDelim] welcome\n";
    std::size_t current, previous = 0;
    current = toSplit.find(delim);
    while (current != std::string::npos) {
        dualVec.push_back(toSplit.substr(previous, current - previous));
        previous = current + 1;
        current = toSplit.find(delim, previous);
    }
    dualVec.push_back(toSplit.substr(previous, current - previous));
}