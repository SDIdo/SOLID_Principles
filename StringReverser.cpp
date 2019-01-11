//
// Created by roy on 1/3/19.
//

#include "StringReverser.h"

string StringReverser::solve(string *problemString) {
    stringstream ss;
    int strLength = problemString->length();
    for (int i = strLength; i > 0; i--) {
        ss << problemString->at(i - 1);
    }
    return ss.str();
}