//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_SEARCHER_H
#define PROJECTPART2_SEARCHER_H

#include "Searchable.h"
#include <string>

using namespace std;

template<class T, class Solution>
class Searcher {
protected:
    int numberOfEvaluated;
    vector<State<T> *> path;
    Searchable<T> *searchable;

    virtual string get2DPathString() {
        string pathString;
        vector<double> relation;
        for (int i = 0; i < this->path.size() - 1; i++) {
            State<T> *currentState = this->path.at(i);
            State<T> *nextState = this->path.at(i + 1);
            // get the relation between the two states, and append the step in the path string.
            relation = this->searchable->getRelation(currentState, nextState);
            if (relation.at(0) == 1) {
                pathString += ", Up";
            } else if (relation.at(0) == -1) {
                pathString += ", Down";
            } else if (relation.at(1) == 1) {
                pathString += ", Left";
            } else if (relation.at(1) == -1) {
                pathString += ", Right";
            }
        }
        return pathString;
    }

public:
    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //PROJECTPART2_SEARCHER_H
