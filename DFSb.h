//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_DFSB_H
#define PROJECTPART2_DFSB_H

#include <vector>
#include <iostream>
#include "Searcher.h"

using namespace std;

template<class Solution>
class DFSb : public Searcher<Solution> {
    vector<State<T> *> black;
    vector<State<T> *> grey;
    vector<State<T> *> path;

    Solution *dfs(State<T> *currentState, Searchable<T> *searchable) {
        grey.push_back(currentState);
        // if the algorithm reached the goal state.
        if (currentState->equals(searchable->getGoalState())) {
            // get the path, as long as the father is not null.
            path.push_back(currentState);
            while (currentState->getCameFrom() != nullptr) {
                path.push_back(currentState->getCameFrom());
            }
            return path;
        }
        for (State<T> *state : searchable->getAllPossibleStates(currentState)) {
            std::vector<int>::iterator it;
            it = find(black.begin(), black.end(), currentState);
            // if the state is in the black list.
            if (it != black.end()) {
                std::cout << "Element found in black: " << *it << '\n';
                continue;
            }
            it = find(grey.begin(), grey.end(), currentState);
            // if the state is in the grey list.
            if (it != grey.end()) {
                std::cout << "Element found in grey: " << *it << '\n';
                continue;
            }
            // if the state was not visited yet.
            if (dfs(currentState, searchable) != nullptr) {
                // get the path, as long as the father is not null.
                path.push_back(currentState);
                while (currentState->getCameFrom() != nullptr) {
                    path.push_back(currentState->getCameFrom());
                }
                return path;
            }

        }
        black.push_back(currentState);
    }

public:
    virtual Solution search(Searchable<class T> *searchable) {
        State<T> *currentState = searchable->getInitialState();
        return this->dfs(currentState, searchable);
    }
};

#endif //PROJECTPART2_DFSB_H
