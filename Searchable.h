//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_SEARCHABLE_H
#define PROJECTPART2_SEARCHABLE_H

#include "State.h"
#include <list>
#include <vector>
#include <string>

using namespace std;

/**
 * Template class Searchable describes an object which
 * could be searched, with a search algorithm for example.
 * Each searchable can return states according to the
 * current state.
 * @tparam T the class of the state representation.
 */
template <class T>
class Searchable {
public:
    virtual State<T> *getInitialState() = 0;
    virtual State<T> *getGoalState() = 0;
    virtual list<State<T>*> getAllPossibleStates(State<T> *s) = 0;
    virtual vector<double> getRelation(State<T> *s1, State<T> * s2) = 0;
    virtual ~Searchable() = default;
};


#endif //PROJECTPART2_SEARCHABLE_H
