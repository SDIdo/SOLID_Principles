//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_BFS_H
#define PROJECTPART2_BFS_H


#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include "Searcher.h"

using namespace std;

template<class T>
class BFS : public Searcher<T, vector<State<T> *>> {
    vector<State<T> *> grey;
    std::queue<State<T> *> queue;
    vector<State<T> *> path;

    vector<State<T> *> bfs(State<T> *currentState, Searchable<T> *searchable) {
        queue.push(currentState);
        grey.push_back(currentState);
        this->numberOfEvaluated += 1;

        while (!queue.empty()) {
            currentState = queue.front();
            queue.pop();
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
            for (State<T> *neighbor : neighborsList) {
                // if the state is in the grey list.
                if (find(grey.begin(), grey.end(), neighbor) != grey.end()) {
                    std::cout << "Element found in grey: " << '\n';
                    continue;
                }
                // if the neighbor was not visited yet, set the father to be the current state and visit it.
                neighbor->setCameFrom(currentState);
                grey.push_back(neighbor);
                queue.push(neighbor);
            }
        }
    }

public:
    BFS() =
    default;

    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        State<T> *currentState = searchable->getInitialState();
        return this->bfs(currentState, searchable);
    }

    virtual int getNumberOfNodesEvaluated() {
        return this->numberOfEvaluated;
    }

};


#endif //PROJECTPART2_BFS_H
