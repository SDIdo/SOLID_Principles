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
    Solver<Searchable<T>, string> *solver;
    CacheManager<Problem, Solution> *cacheManager;
public:
    MyClientHandler(Solver<Searchable<T>, string> *solver,
                    CacheManager<Problem, Solution> *cacheManager) {
        this->solver = solver;
        this->cacheManager = cacheManager;
    }

    virtual ~MyClientHandler() {
        delete(this->cacheManager);
        delete(this->solver);
    }

    virtual void handleClient(int *sockfdPtr) {
        // get input from input stream until "/n", each will be a row of the matrix.
        int index = 0;
        int n = 0;
        int numOfRows, columnsSize;
        int sockfd = *sockfdPtr;
        char buffer[256];
        string remainder, backRemainder, information, problemString, answerString;
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
                    if (problemString.empty()) {
                        break;
                    }

                    // if the answer to the problem is in the cache - it will be written to client.
                    if (this->cacheManager->check(&problemString)) {
                        cout << "FOUND IN THE CACHE!\n";
                        answerString = this->cacheManager->get(&problemString);
                    }
                        // if the answer is not in the cache - create searchable for solver and save answer in cache.
                    else {
                        vector<vector<int>> matrixGrid;
                        for (string str : rowsVector) {
                            matrixGrid.push_back(line_parse(str));
                        }
                        // create the start and finish entries.
                        Entry start(matrixGrid.at(matrixGrid.size() - 2).at(0),
                                    matrixGrid.at(matrixGrid.size() - 2).at(1));
                        Entry finish(matrixGrid.at(matrixGrid.size() - 1).at(0),
                                     matrixGrid.at(matrixGrid.size() - 1).at(1));
                        // this will delete the entry and exit points of the matrix from vector.
                        matrixGrid.pop_back();
                        matrixGrid.pop_back();
                        // get the size of the matrix.

                        columnsSize = matrixGrid[0].size();
                        numOfRows = matrixGrid.size();

                        // create the matrix as searchable.
                        Searchable<Entry> *searchable = new MatrixGraph(columnsSize, numOfRows, &start, &finish,
                                                                        matrixGrid);
                        answerString = this->solver->solve(searchable);
                        delete(searchable);
                        this->cacheManager->set(&problemString, &answerString);
                    }
                    answerString += "\r\n";
                    char *answer = &answerString[0];
                    n = write(sockfd, answer, answerString.length());
                    break;
                }
                problemString += information;
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
