//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_STRINGREVERSER_H
#define PROJECTPART2_STRINGREVERSER_H

#include "Solver.h"
#include <sstream>

class StringReverser : public Solver<string, string>{
public:
    virtual string solve(string *problemString);
};


#endif //PROJECTPART2_STRINGREVERSER_H
