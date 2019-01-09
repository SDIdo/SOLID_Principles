//
// Created by roy on 1/3/19.
//

#include <unistd.h>
#include <strings.h>
#include <iostream>
#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solver,
                                         CacheManager<string, string> *cacheManager) {
    this->solver = solver;
    this->cacheManager = cacheManager;
}

void MyTestClientHandler::handleClient(int sockfd) {
    // get input from input stream until "/n" and put it in the solver's solve func.
    int index = 0;
    int n = 0;
    char buffer[256];
    string remainder, backRemainder, information;
    bool isDataEnd = false;

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
            // if the user wrote 'end' - the communication ends.
            if (remainder == "end") {
                break;
            }
            string answerString;
            // if the answer is in the cache - it will be written to client.
            if (this->cacheManager->check(remainder)) {
                answerString = this->cacheManager->get(remainder);
            }
            // if the answer is not in the cache - send the problem to solver and save the answer in cache.
            else {
                answerString = this->solver->solve(remainder);
                this->cacheManager->set(remainder, answerString);
            }
            answerString += "\r\n";
            char *answer = &answerString[0];
            n = write(sockfd, answer, answerString.length());
            remainder = "";
            isDataEnd = false;
        }
    }

}
