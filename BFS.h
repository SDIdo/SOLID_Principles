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
class BFS : public Searcher<T, string> {
    vector<State<T> *> grey;
    std::queue<State<T> *> queue;

    vector<State<T> *> bfs(State<T> *currentState) {
        queue.push(currentState);
        grey.push_back(currentState);

        while (!queue.empty()) {
            currentState = queue.front();
            queue.pop();
            this->numberOfEvaluated += 1;
            // if the algorithm reached the goal state.
            if (currentState->equals(this->searchable->getGoalState())) {
                // get the reversed path, as long as the father is not null.
                this->path.push_back(currentState);
                while (currentState->getCameFrom()) {
                    this->path.push_back(currentState->getCameFrom());
                    currentState = currentState->getCameFrom();
                }
                return this->path;
            }
            list<State<T> *> neighborsList = this->searchable->getAllPossibleStates(currentState);
            for (State<T> *neighbor : neighborsList) {
                // if the state is in the grey list.
                if (find(grey.begin(), grey.end(), neighbor) != grey.end() || neighbor->getCost() == -1) {
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
    BFS() = default;

    virtual string search(Searchable<T> *searchable) {
        this->searchable = searchable;
        vector<State<T> *> path;
        State<T> *startState;
        string pathString;

        startState = searchable->getInitialState();
        this->bfs(startState); // search by BFS and return reversed path.

        reverse(this->path.begin(), this->path.end()); // reverse the path to get shortest path to finish.
        pathString = this->get2DPathString();
        return pathString;
    }

    virtual int getNumberOfNodesEvaluated() {
        return this->numberOfEvaluated;
    }

};


#endif //PROJECTPART2_BFS_H
