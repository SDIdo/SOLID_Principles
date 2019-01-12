//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_DFSB_H
#define PROJECTPART2_DFSB_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Searcher.h"

using namespace std;

template<class T>
class DFS : public Searcher<T, vector<State<T> *>> {
    vector<State<T> *> black;
    vector<State<T> *> grey;
    vector<State<T> *> path;

    vector<State<T> *> dfs(State<T> *currentState, Searchable<T> *searchable) {
        grey.push_back(currentState);
        this->numberOfEvaluated += 1;
        // if the algorithm reached the goal state.
        if (currentState->equals(searchable->getGoalState())) {
            // get the path, as long as the father is not null.
            path.push_back(currentState);
            while (currentState->getCameFrom()) {
                path.push_back(currentState->getCameFrom());
                currentState = currentState->getCameFrom();
            }
            return path;
        }
        list<State<T> *> neighborsList = searchable->getAllPossibleStates(currentState);
        for (State<T> * neighbor : neighborsList) {
            // if the state is in the black list.
            if (find(black.begin(), black.end(), neighbor) != black.end()) {
                std::cout << "Element found in black: " << '\n';
                continue;
            }
            // if the state is in the grey list.
            if (find(grey.begin(), grey.end(), neighbor) != grey.end()) {
                std::cout << "Element found in grey: " << '\n';
                continue;
            }
            // if the neighbor was not visited yet, set the father to be the current state and visit it.
            neighbor->setCameFrom(currentState);
            return dfs(neighbor, searchable);
        }
        // when finished with current state, it is already evaluated.
        black.push_back(currentState);
    }

public:
    DFS() = default;

    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        State<T> *currentState = searchable->getInitialState();
        return this->dfs(currentState, searchable);
    }

    virtual int getNumberOfNodesEvaluated() {
        return this->numberOfEvaluated;
    }
};

#endif //PROJECTPART2_DFSB_H
