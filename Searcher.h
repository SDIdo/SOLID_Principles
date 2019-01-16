//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_SEARCHER_H
#define PROJECTPART2_SEARCHER_H

#include "Searchable.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Abstract class Searcher.
 * Searchers can search in given searchables and return solutions
 * according to the search.
 * @tparam T generic class of the template for the search.
 * @tparam Solution return value of the search.
 */
template<class T, class Solution>
class Searcher {
protected:
    int numberOfEvaluated;
    vector<State<T> *> path;
    Searchable<T> *searchable;

    /**
     * This method returns the string representation of the searcher's path.
     * @return string representation of the path.
     */
    virtual string get2DPathString() {
        string pathString;
        vector<double> relation;
        State<T> *currentState;
        State<T> *nextState;
        if (this->path.empty()) {
            pathString = "No such path.\n";
        } else {
            cout << "length : " << to_string(this->path.size() - 1) + "   ";
            for (int i = 0; i < this->path.size() - 1; i++) {
                if (i == 0) {
                    pathString += "{";
                } else {
                    pathString += ", ";
                }


                currentState = this->path.at(i);
                nextState = this->path.at(i + 1);
                // get the relation between the two states, and append the step in the path string.
                relation = this->searchable->getRelation(currentState, nextState);
                if (relation.at(0) == 1) {
                    pathString += "Up";
                } else if (relation.at(0) == -1) {
                    pathString += "Down";
                } else if (relation.at(1) == 1) {
                    pathString += "Left";
                } else if (relation.at(1) == -1) {
                    pathString += "Right";
                }

                if (i == this->path.size() - 2) {
                    pathString += "}";
                }
            }
        }
        this->path.clear();
        return pathString;
    }

public:
    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual ~Searcher() = default;

    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //PROJECTPART2_SEARCHER_H
