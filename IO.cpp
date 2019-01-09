//
// Created by idox on 1/9/19.
//

#include "IO.h"

int IO::write(string path) {

    std::fstream fs;
    fs.open (path, std::fstream::app);
    if (!fs){
        std::perror("File not found!");
        return 1;
    }

    fs << "1\n2\n3\n4\n";

    fs.close();

    return 0;
}
/**
 * sum lines of numbers from text file
 * @param path - address of text file
 * @param sum - int container of number from lines of file
 * @return - 0 upon success, 1 otherwise.
 */
int IO::read(string path, int &sum){
    ifstream inFile;
    inFile.open(path, std::fstream::in);
    if (!inFile){
        std::perror("Unable to read from the file");
        return 1;
    }
    int x;
    //summing up the numbers
    while(inFile >> x){
        sum += x;
    }
    return 0;
}

void IO::splitString(std::vector<string> &splitted, string &toSplit, const string &delimiter){
    string sub;
    string::size_type pos = 0;
    string::size_type old_pos = 0;
    bool flag=true;

    while(flag)
    {
        pos=toSplit.find_first_of(delimiter,pos);
        if(pos == string::npos)
        {
            flag = false;
            pos = toSplit.size();
        }
        sub = toSplit.substr(old_pos,pos-old_pos);  // Disregard the '.'
        splitted.push_back(sub);
        old_pos = ++pos;
    }
}

/**
 * Function recognize = sign as separator for first and second items in map
 * @param path - file address
 * @return - 0 upon success or 1 elsewise.
 */
int IO::readMap(string path, std::map<string, string>&myMap) {
    ifstream inFile;
    inFile.open(path, ifstream::in);
    if (!inFile) {
        perror("Could not find the file\n");
        return 1;
    }
    string input;
    string key;
    string value;
    string delim;
    std::vector<string> splitted;
//    inFile.getline(&input, "="){

//    }
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