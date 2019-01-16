//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_DFSB_H
#define PROJECTPART2_DFSB_H

#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include "Searcher.h"

using namespace std;

/**
 * DFS algorithm class. DFS is a searcher, which, given a searchable could
 * search it and return the string value of the path found from start to end states.
 * @tparam T generic class for the searcher.
 */
template<class T>
class DFS : public Searcher<T, string> {
    vector<State<T> *> grey;
    std::stack<State<T> *> stack;

    /**
     * This method is the dfs recursive search. receives a current state for the search.
     * It updates the path (solution).
     * @param currentState current state of the search.
     */
    void dfs(State<T> *currentState) {

        this->grey.push_back(currentState);

        while (!this->stack.empty()) {
            currentState = this->stack.top();
            this->stack.pop();
            this->numberOfEvaluated += 1;
            // if the algorithm reached the goal state.
            if (currentState->equals(this->searchable->getGoalState())) {
                // get the reversed path, as long as the father is not null.
                this->path.push_back(currentState);
                while (currentState->getCameFrom()) {
                    this->path.push_back(currentState->getCameFrom());
                    currentState = currentState->getCameFrom();
                }
                break;
            }
            list<State<T> *> neighborsList = this->searchable->getAllPossibleStates(currentState);
            for (State<T> *neighbor : neighborsList) {
                // if the state is in the grey list.
                if (find(grey.begin(), grey.end(), neighbor) != grey.end() || neighbor->getCost() == -1) {
                    continue;
                }
                // if the neighbor was not visited yet, set the father to be the current state and visit it.
                neighbor->setCameFrom(currentState);
                this->stack.push(neighbor);
            }
            if (!this->stack.empty()) {
                return dfs(this->stack.top());
            }

        }
    }

public:
    /**
     * Constructor of DFS algorithm.
     */
    DFS() = default;

    /**
     * This method starts the search from the initial state to the finish state, and then
     * returns string of the path.
     * @param searchable searchable for the search.
     * @return string of the path.
     */
    virtual string search(Searchable<T> *searchable) {
        State<T> *startState;
        string pathString;
        this->searchable = searchable;
        this->numberOfEvaluated = 0;

        // if the start of goal are blocked and can't be reached.
        if (this->searchable->getGoalState()->getCost() == -1 || this->searchable->getInitialState()->getCost() == -1) {
            return "Blocked start or finish.";
        }
        // if the initial state is the goal state.
        if (this->searchable->getInitialState()->equals(this->searchable->getGoalState())) {
            return "Start is the goal state.";
        }

        startState = searchable->getInitialState();
        this->stack.push(startState);
        this->dfs(startState); // search by BFS and return reversed path.
        if (this->path.empty()) {
            return "No such path.\n";
        }
        reverse(this->path.begin(), this->path.end()); // reverse the path to get shortest path to finish.
        pathString = this->get2DPathString();
        return pathString;
    }

    /**
     * This method returns the number of nodes that the algorithm evaluated
     * in the search.
     * @return number of nodes evaluated by the search.
     */
    virtual int getNumberOfNodesEvaluated() {
        return this->numberOfEvaluated;
    }
};

#endif //PROJECTPART2_DFSB_H
