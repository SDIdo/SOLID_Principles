//
// Created by roy on 1/9/19.
//

#include "IO.h"

/**
 * Function recognize = sign as separator for first and second items in map
 * @param path - file address
 * @return - 0 upon success or 1 elsewise.
 */
int IO::readMap(string path, std::map<string, string>&myMap) {
    ifstream inFile;
    inFile.open(path, ifstream::in);
    if (!inFile) {
        cout << "no existing file\n";
        return 1;
    }
    string input;
    string key;
    string value;
    string delim;
    std::vector<string> splitted;
    while (inFile >> key) {
        inFile >> delim;
        inFile >> value;
        std::cout << "This is going to be in the map: " << key << " = " << value << "\n";
        myMap[key] = value;
    }
}
/**
 * Write map only after solver. Not if solution is found.
 * @param path - name of file
 * @param myMap - internal map
 * @return 0 if success, 1 if not.
 */
int IO::writeMap(string path, std::map<string, string>&myMap){
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
    std::vector<string> splitted;

    for (std::map<string,string>::iterator it=myMap.begin(); it!=myMap.end(); ++it) {
        outFile << it->first;
        outFile << " = ";
        outFile << it->second;
        outFile << "\n";
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
int IO::writeKeyVal(string path, string key, string val){
    fstream outFile;
    outFile.open(path, ifstream::app);
    if (!outFile) {
        perror("Could not find the file\n");
        return 1;
    }
    outFile << key;
    outFile << " = ";
    outFile << val;
    outFile << "\n";

    outFile.close();
    return 0;
}