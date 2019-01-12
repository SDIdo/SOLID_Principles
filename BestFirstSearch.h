//
// Created by idox on 1/12/19.
//

#ifndef PROJECTPART2_BESTFIRSTSEARCH_H
#define PROJECTPART2_BESTFIRSTSEARCH_H


#include "Entry.h"
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
        return ((left->getCost()) > (right->getCost()));
    }
};

class BestFirstSearch : public Searcher<Entry, vector <State< Entry>*>> {
private:
    State<Entry> *goalState;
    map<State<Entry> *, double> globalCost; //TODO maybe only by cost
    map<State<Entry> *, double> localCost;  //TODO maybe wont need it
    vector<State<Entry> *> path;
    priority_queue<State<Entry>*, vector<State<Entry>*>, pr_greater > exploringQueue;
    vector<State<Entry>*> closedList;


    /**
* Function sets additional cost to consider shortest path using goalState coordinates
* @param currentState - a state to add heuristic to
* @return the additional heuristic
*/
    double calculateHeuristic(State<Entry> *currentState) //@TODO return or set?
    {

        int currentRow = currentState->getState()->getI();
        int currentCol = currentState->getState()->getJ();
        int goalRow = this->goalState->getState()->getI();
        int goalCol = this->goalState->getState()->getJ();

        // Return using the distance formula
        return sqrt(currentRow - goalRow * (currentRow - goalRow) + (currentCol - goalCol) * (currentCol - goalCol));
    }

    /**
 * Function checks whether a state got it's heuristic value or not
 * @param state - subject state
 * @return true or false accordingly
 */
    bool checkInHeuristicsMap(State<Entry> *state) {    //might be redundant here.
        map<State<Entry>*, double>::iterator it;
        it = globalCost.find(state);
        return (it != globalCost.end());
    }
public:
    /**
 * Search using the AStar algorithm that in addition to using cost calculations uses heuristic
 * @param searchable - the graph/matrix/any searchable puzzle
 * @return - the least expensive path to the finish.
 */
    virtual vector<State<Entry>*> search(Searchable<Entry> * searchable){
        //Would like to know your goal.
        this->goalState = searchable->getGoalState();
        //Would like to know your starting state.
        State<Entry>* currentState = searchable->getInitialState();
        return bestFirstSearch(currentState, searchable);
    }
    /**
 *
 * @param currentState - state from which to look for the goal
 * @param searchable - a puzzle or any searchable field
 * @return the least expensive path to the finish.
 */
    virtual vector<State<Entry>*> bestFirstSearch(State<Entry> *currentState, Searchable<Entry> *searchable) {
        if (currentState->getCost() == -1) {
            return path;
        }
        double travelCost = 0;
        this->exploringQueue.push(currentState); //TODO Added!


        //Set local cost & set Heuristic
        this->localCost[currentState] = currentState->getCost();
        this->globalCost[currentState] = currentState->getCost() + this->calculateHeuristic(currentState);
        currentState->setCost(currentState->getCost() + this->calculateHeuristic(currentState)); //TODO added!

        while (!exploringQueue.empty()) {
            currentState = exploringQueue.top();
            exploringQueue.pop();

            this->closedList.push_back(currentState); //TODO Added!
            //explore all neighbors of current queued state

            if (currentState == goalState) {
                cout << "That's it! found the route :P\n";
                path.push_back(currentState);
                while (currentState->getCameFrom()) {
                    cout << "Getting the path\n";
                    path.push_back(currentState->getCameFrom());
                    //"currentState++"
                    currentState = currentState->getCameFrom();
                }
                return path;
            }
            if (currentState->getCost() == -1) {
                continue;
            }
            this->numberOfEvaluated += 1;
            list<State<Entry> *> neighbors = searchable->getAllPossibleStates(currentState);

            for (State<Entry> *neighbor : neighbors) {
                if (neighbor->getCost() == -1) {
                    continue;
                }
                //That's the road's cost to here.
                travelCost = this->localCost[currentState] + neighbor->getCost();

                //TEST ZONE
                cout << "[BestFirstSearch]Current neigbor is " << "(" << neighbor->getState()->getI()
                     << ", " << neighbor->getState()->getJ() << ")" << " with travlCost: " << travelCost << "\n";
                //#

                //first check if was added to heuristics:
                bool found = find(closedList.begin(), closedList.end(), currentState) != closedList.end();
                if (!this->checkInHeuristicsMap(neighbor) && !found) {
                    //Well not in Heuristic so should be set and added!
                    cout << neighbor->getCost() << " wasn't in local cost, so adding it\n";
                    this->localCost[neighbor] = travelCost;
                    //also set the heuristic for this neighbor according to it we'll sort in queue.
                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
                //should we add this state? check using comparisons between local costs
                if ((this->localCost[neighbor]) > travelCost) {
                    cout << "Found a better rout to this neighbor, updating! but won't be added to queue\n";
                    cout << "So " << neighbor->getCost() << " will get it's came , from : " << currentState->getCost()
                         << "\n";
                    this->localCost[neighbor] = travelCost;
                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
            }
            cout << "next state queued, please sort! Already Sorted!\n";
        }
    }
        //So now that the queue is empty traverse the states from the last one by each parent and parent
//        State<Entry> *state = searchable->getGoalState();
//        path.push_back(state);
//        while (state->getCameFrom()) {
//            cout << "Getting the path\n";
//            path.push_back(state->getCameFrom());
//            state = state->getCameFrom();
//        }
//        return path;
//    }
    virtual int getNumberOfNodesEvaluated(){
        return this->numberOfEvaluated;
    }
};




#endif //PROJECTPART2_BESTFIRSTSEARCH_H
