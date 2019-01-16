//
// Created by idox on 1/12/19.
//

#ifndef PROJECTPART2_BESTFIRSTSEARCH_H
#define PROJECTPART2_BESTFIRSTSEARCH_H

#include <iostream>
#include <queue>
#include <cfloat>
#include <vector>
#include "State.h"
#include "Searcher.h"
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct pr_greater {
    template <class T>
    bool operator()(const T& left, const T& right) const {
        return ((left->getDistance()) >= (right->getDistance()));
    }
};

template <class T>
class BestFirstSearch : public Searcher<T, string> {
private:
    State<T> *goalState;
    vector<State<T>*> closedList;

public:
    /**
 * Search using the BestFirstSearch algorithm that in addition to using cost calculations uses heuristic
 * @param searchable - the graph/matrix/any searchable puzzle
 * @return - the least expensive path to the finish.
 */
    virtual string search(Searchable<T> * searchable){
        this->numberOfEvaluated = 0;
        this->searchable = searchable;
        //3 Edge Cases (The forth one, goal blocked, is found within the process):

        if (searchable->getGoalState()->getCost() == -1) {
            return "Legnth: 0 Goal is a block\n";
        }
        if (searchable->getInitialState()->getCost() == -1) {
            return "Legnth: 0 Start is a block\n";;
        }
        if (searchable->getInitialState()->equals(searchable->getGoalState())) {
            cout << "Goal is desti\n";
            return "Legnth: 0 Start is the Goal\n";
        }

        //Would like to know your goal.
        this->goalState = searchable->getGoalState();
        //Would like to know your starting state.
        State<T> *currentState = searchable->getInitialState();
        this->path = bestFirstSearch(currentState);
        reverse(this->path.begin(), this->path.end());
//        globalCost.clear();
//        localCost.clear();
        closedList.clear();
        return this->get2DPathString();
    }
    /**
 *
 * @param currentState - state from which to look for the goal
 * @param searchable - a puzzle or any searchable field
 * @return the least expensive path to the finish.
 */
    virtual vector<State<T>*> bestFirstSearch(State<T> *currentState) {
        priority_queue<State<T>*, vector<State<T>*>, pr_greater > exploringQueue;

        double travelCost = 0;
        exploringQueue.push(currentState); //TODO Added!


        travelCost = currentState->getCost();
        currentState->setDistance(currentState->getCost());

        while (!exploringQueue.empty()) {
            currentState = exploringQueue.top();
            exploringQueue.pop();

            this->closedList.push_back(currentState); //TODO Added!

            if (currentState == goalState) {
                this->path.push_back(currentState);
                while (currentState->getCameFrom()) {
                    this->path.push_back(currentState->getCameFrom());
                    //"currentState++"
                    currentState = currentState->getCameFrom();
                }
                return this->path;
            }
            this->numberOfEvaluated += 1;
            list<State<T> *> neighbors = this->searchable->getAllPossibleStates(currentState);

            for (State<T> *neighbor : neighbors) {
                if (neighbor->getCost() == -1) {
                    continue;
                }

                //first check if was added to heuristics:
                if (!(find(closedList.begin(), closedList.end(), neighbor) != closedList.end())){
                    travelCost+= neighbor->getCost();
                    neighbor->setDistance(travelCost);
                    travelCost = currentState->getDistance();
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }

            }
        }
        return this->path;
    }

    virtual int getNumberOfNodesEvaluated(){
        return this->numberOfEvaluated;
    }
};

#endif //PROJECTPART2_BESTFIRSTSEARCH_H