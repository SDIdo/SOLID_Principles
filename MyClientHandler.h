//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_MYCLIENTHANDLER_H
#define PROJECTPART2_MYCLIENTHANDLER_H

#include "../ClientHandler.h"
#include "../Solver.h"
#include "../CacheManager.h"
#include "Searchable.h"
#include "MatrixGraph.h"
#include "Entry.h"
#include <string>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <vector>

using namespace std;

template<class T, class Solution, class Problem>
class MyClientHandler : public ClientHandler {
    Solver<Searchable<T>, vector<State<Entry> *>> *solver;
    CacheManager<Problem, Solution> *cacheManager;
public:
    MyClientHandler(Solver<Searchable<T>, vector<State<Entry> *>> *solver,
                    CacheManager<Problem, Solution> *cacheManager) {
        this->solver = solver;
        this->cacheManager = cacheManager;
    }

    ~MyClientHandler() = default;
    void handleClient(int sockfd) {
        // get input from input stream until "/n", each will be a row of the matrix.
        int index = 0;
        int n = 0;
        int rowCounter = 0;
        char buffer[256];
        string remainder, backRemainder, information;
        bool isDataEnd = false;
        vector<string> rowsVector;

        while (true) {
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            if (n < 0) {
                throw "Error reading from socket";
            }
            information = string(buffer);

            index = information.find("\r\n");
            // if the line terminator was not found, append all of the information.
            if (index == std::string::npos) {
                remainder += information;
            } else {
                // appends the remainder of the information until the next line.
                remainder += information.substr(0, index);
                backRemainder = information.substr(index + 1, information.length());
                isDataEnd = true;
            }
            if (isDataEnd) {
                // if the user wrote 'end' - the matrix is assembled and sent to solver.
                if (remainder == "end") {
                    vector<vector<int>> matrixGrid;
                    for (string str : rowsVector) {
                        matrixGrid.push_back(line_parse(str));
                    }
                    int columnsSize = matrixGrid[0].size();

                    Entry start(matrixGrid.at(matrixGrid.size() - 2).at(0), matrixGrid.at(matrixGrid.size() - 2).at(1));
                    Entry finish(matrixGrid.at(matrixGrid.size() - 1).at(0), matrixGrid.at(matrixGrid.size() - 1).at(1));
                    // this will delete the entry and exit points of the matrix from vector.
                    matrixGrid.pop_back();
                    matrixGrid.pop_back();
                    // create the matrix as searchable.
                    Searchable<Entry> *searchable = new MatrixGraph(rowCounter, columnsSize, &start, &finish, matrixGrid);
                    string answerString;
                    // if the answer is in the cache - it will be written to client.
                    if (this->cacheManager->check(searchable->toString())) {
                        answerString = this->cacheManager->get(searchable->toString());
                    }
                        // if the answer is not in the cache - send the problem to solver and save the answer in cache.
                    else {
                        vector<State<Entry>*> s = this->solver->solve(searchable);
                        this->cacheManager->set(searchable->toString(), answerString);
                    }
                    answerString += "\r\n";
                    char *answer = &answerString[0];
                    n = write(sockfd, answer, answerString.length());
                    break;
                }
                rowCounter += 1; // another row of the matrix.
                rowsVector.push_back(remainder); // insert the row string to the vector.
                remainder = "";
                isDataEnd = false;
            }
        }
    }

    vector<int> line_parse(string line) {
        int startPos = 0;
        int endPos;
        vector<int> line_vec;
        if (line[line.length() - 1] != ',') {
            line += ",";
        }
        while (true) {
            endPos = line.find(',', startPos);
            if (endPos != -1) {
                line_vec.push_back(stoi(line.substr(startPos, endPos - startPos)));
                startPos = endPos + 1;
            } else {
                return line_vec;
            }
        }
    }
};


#endif //PROJECTPART2_MYCLIENTHANDLER_H
