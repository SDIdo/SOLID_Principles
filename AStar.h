//
// Created by idox on 1/11/19.
//

#ifndef PROJECTPART2_BSTAR_H
#define PROJECTPART2_BSTAR_H

#include "Searcher.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <queue>
#include <map>
#include <cfloat>

template <class T>
class AStar : public Searcher<T, string>{
private:
    //initialize cost maps
    map <State<T>*,double> globalCost;   //state costs + heuristics
    map <State<T>*,double> localCost;   //only state costs
    //initializing operations queue
    queue<State<T> *> exploringQueue;

/**
 * Function sets additional cost to consider shortest path using goalState coordinates
 * @param currentState - a state to add heuristic to
 * @return the additional heuristic
 */
    double calculateHeuristic(State<T> *currentState) //@TODO return or set?
    {

        int currentRow = currentState->getState()->getI();
        int currentCol = currentState->getState()->getJ();
        int goalRow = this->searchable->getGoalState()->getState()->getI();
        int goalCol = this->searchable->getGoalState()->getState()->getJ();

        // Return using the distance formula
        return sqrt(currentRow - goalRow * (currentRow - goalRow) + (currentCol - goalCol) * (currentCol - goalCol));
    }
/**
 * Function checks whether a state got it's heuristic value or not
 * @param state - subject state
 * @return true or false accordingly
 */
    bool checkInHeuristicsMap(State<T>* state) {
        typename map<State<T> *, double>::iterator it;
        it = globalCost.find(state);
        return (it != globalCost.end());
    }
public:
/**
 * Search using the AStar algorithm that in addition to using cost calculations uses heuristic
 * @param searchable - the graph/matrix/any searchable puzzle
 * @return - the least expensive path to the finish.
 */
    virtual string search(Searchable<T> * searchable){
        this->numberOfEvaluated = 0;
        this->searchable = searchable;

        //Would like to know your starting state.
        State<T> *currentState = searchable->getInitialState();
        if (currentState->equals(this->searchable->getGoalState())) {
            return "Just stay in place";
        }
        this->astar(currentState);
        //clearing stage except for the path
        while (!exploringQueue.empty()){
            exploringQueue.pop();
        }
        localCost.clear();
        globalCost.clear();
        reverse(this->path.begin(), this->path.end());
        return this->get2DPathString();
    }
/**
 * function simulates a priority queue //@TODO learn to use the native priority queue.
 * @param q - a queue to sort.
 * note: all that in the queue has heuristic value.
 */
    void prioritize(queue<State<T>*> &q) {
//        cout <<"[Welcome to prioritize]\n";
        double minimumCost = DBL_MAX;
        queue<State<T> *> priority;
        State<T> *previousState;

        while (!q.empty()) {
            State<T> *currentState = q.front();
//            cout << "[Prioritize]Current T by cost " << currentState->getCost() << '\n';
            q.pop();

            if (currentState->getCost() < minimumCost) {
                minimumCost = currentState->getCost();
//                cout << "current state is cheaper, updated minimum cost\n";
                if (!priority.empty()) {
//                    cout << "queue wasn't empty so taking out the first and switching\n";
                    previousState = priority.front();
                    priority.pop();
                    priority.push(currentState);
                    priority.push(previousState);
                    continue;
                } else {
                    priority.push(currentState);
                    continue;
                }
            };
            priority.push(currentState);
        }
        State<T> *toPut;
        while (!priority.empty()) {
            toPut = priority.front();
            q.push(toPut);
            priority.pop();
        }
    }
/**
 *
 * @param currentState - state from which to look for the goal
 * @param searchable - a puzzle or any searchable field
 * @return the least expensive path to the finish.
 */
    virtual void astar(State<T> *currentState) {
        if (currentState->getCost() == -1){
            return;
        }
        double travelCost = 0;
        exploringQueue.push(currentState);

        //Set local cost & set Heuristic
        this->localCost[currentState] = currentState->getCost();
        this->globalCost[currentState] = currentState->getCost() + this->calculateHeuristic(currentState);


        while (!exploringQueue.empty()) {
            currentState = exploringQueue.front();
            exploringQueue.pop();
            //explore all neighbors of current queued state

            if (currentState->equals(this->searchable->getGoalState())){
                continue;
            }
            this->numberOfEvaluated += 1;
            list<State<T> *> neighbors = this->searchable->getAllPossibleStates(currentState);

            for (State<T> *neighbor : neighbors) {
                if (neighbor->getCost() == -1){
                    continue;
                }
                //That's the road's cost to here.
                travelCost = this->localCost[currentState] + neighbor->getCost();

                //TEST ZONE
//                cout << "[ASTAR]Current neigbor is " << "(" << neighbor->getState()->getI()
//                     << ", " << neighbor->getState()->getJ() << ")" << " with travlCost: " << travelCost << "\n";
                //#

                //first check if was added to heuristics:
                if (!this->checkInHeuristicsMap(neighbor)) {
                    //Well not in Heuristic so should be set and added!
//                    cout << neighbor->getCost() << " wasn't in local cost, so adding it\n";
                    this->localCost[neighbor] = travelCost;
                    //also set the heuristic for this neighbor according to it we'll sort in queue.
                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
                //should we add this state? check using comparisons between local costs
                if ((this->localCost[neighbor]) > travelCost) {
//                    cout << "Found a better rout to this neighbor, updating! but won't be added to queue\n";
//                    cout << "So " << neighbor->getCost() << " will get it's came , from : " << currentState->getCost() << "\n";
                    this->localCost[neighbor] = travelCost;
                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
            }
            this->prioritize(exploringQueue);
        }
        //So now that the queue is emptry traverse the states from the last one by each parent and parent
        State<T> *state = this->searchable->getGoalState();
        this->path.push_back(state);

        while (state->getCameFrom()) {
            this->path.push_back(state->getCameFrom());
            state = state->getCameFrom();
        }
    }

    virtual int getNumberOfNodesEvaluated(){
        return this->numberOfEvaluated;
    }
};


#endif //PROJECTPART2_BSTAR_H