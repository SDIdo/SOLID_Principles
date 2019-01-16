//
// Created by roy on 1/9/19.
//

#include "IO.h"

/**
 * Function recognize = sign as separator for first and second items in map
 * @param path - file address
 * @return - 1 upon success or 0 otherwise.
 */
int IO::readMap(string path, std::unordered_map<string, string> &myMap) {
    ifstream inFile;
    inFile.open(path, ifstream::in);
    if (!inFile) {
        return 0;
    }
    std::string info;
    std::string key;
    std::string value;
    std::vector<string> keyVal;

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
    return 1;
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

string IO::readServer(string path) {
    ifstream inFile;
    inFile.open(path, ifstream::in);
    if (!inFile) {
        return 0;
    }
    string all;
    string input;
    while (std::getline(inFile, input)) {
        input += "\r\n";
        all += input;

    }
    return all;
}

vector<string> IO::readStringVectorServer(string path) {
    ifstream inFile;
    inFile.open(path, ifstream::in);

    vector<string> vec;
    string input;
    while (std::getline(inFile, input)) {
        vec.push_back(input);

    }
    return vec;
}