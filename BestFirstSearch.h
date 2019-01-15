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
class BestFirstSearch : public Searcher<T, string> { //TODO what happens when cost is greater than greater heuristic
private:
    State<T> *goalState;
//    map<State<T> *, double> globalCost; //TODO maybe only by cost
//    map<State<T> *, double> localCost;  //TODO maybe wont need it
    vector<State<T>*> closedList;


    /**
* Function sets additional cost to consider shortest path using goalState coordinates
* @param currentState - a state to add heuristic to
* @return the additional heuristic
*/
    double calculateHeuristic(State<T> *currentState) //@TODO return or set?
    {

        int currentRow = currentState->getState()->getI();
        int currentCol = currentState->getState()->getJ();
        int goalRow = this->goalState->getState()->getI();
        int goalCol = this->goalState->getState()->getJ();

        // Return using the distance formula
        return sqrt(currentRow - goalRow * (currentRow - goalRow) + (currentCol - goalCol) * (currentCol - goalCol));
    }

//    /**
// * Function checks whether a state got it's heuristic value or not
// * @param state - subject state
// * @return true or false accordingly
// */
//    bool checkInHeuristicsMap(State<T> *state) {    //might be redundant here.
//        typename map<State<T>*, double>::iterator it;
//        it = globalCost.find(state);
//        return (it != globalCost.end());
//    }
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


        //Set local cost & set Heuristic
//        this->localCost[currentState] = currentState->getCost();
//        this->globalCost[currentState] = this->calculateHeuristic(currentState);
//        currentState->setCost(this->globalCost[currentState]);
        currentState->setDistance(this->calculateHeuristic(currentState));
//        currentState->setCost(currentState->getCost() + this->calculateHeuristic(currentState)); //TODO added!

        while (!exploringQueue.empty()) {
            currentState = exploringQueue.top();
            exploringQueue.pop();

            this->closedList.push_back(currentState); //TODO Added!
//            cout << "Current Node is: " << currentState->getCost() << '\n';
            //explore all neighbors of current queued state

            if (currentState == goalState) {
//                cout << "That's it! found the route :P\n";
                this->path.push_back(currentState);
                while (currentState->getCameFrom()) {
//                    cout << "Getting the path\n";
                    this->path.push_back(currentState->getCameFrom());
                    //"currentState++"
                    currentState = currentState->getCameFrom();
                }
                return this->path;
            }
//            //Skip blocks please.
//            if (currentState->getCost() == -1) {
//                continue;
//            }
            this->numberOfEvaluated += 1;
            list<State<T> *> neighbors = this->searchable->getAllPossibleStates(currentState);

            for (State<T> *neighbor : neighbors) {
                if (neighbor->getCost() == -1) {
                    continue;
                }
                //That's the road's cost to here.
//                travelCost = this->localCost[currentState] + neighbor->getCost();

                //TEST ZONE
//                cout << "[BestFirstSearch]Current neigbor is " << "(" << neighbor->getState()->getI()
//                     << ", " << neighbor->getState()->getJ() << ")" << " with travlCost: " << travelCost << "\n";
                //#

                //first check if was added to heuristics:
                if (!(find(closedList.begin(), closedList.end(), neighbor) != closedList.end())){
                    //Well not in Heuristic so should be set and added!
//                    cout << neighbor->getCost() << " wasn't in local cost, so adding it\n";
//                    this->localCost[neighbor] = travelCost;
                    //also set the heuristic for this neighbor according to it we'll sort in queue.
//                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
                    neighbor->setDistance(this->calculateHeuristic(neighbor));
                    exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
                //should we add this state? check using comparisons between local costs
//                if ((this->localCost[neighbor]) > travelCost) {
////                    cout << "Found a better rout to this neighbor, updating! but won't be added to queue\n";
////                    cout << "So " << neighbor->getCost() << " will get it's came , from : " << currentState->getCost()
////                         << "\n";
//                    this->localCost[neighbor] = travelCost;
//                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
//                    exploringQueue.push(neighbor);
//                    neighbor->setCameFrom(currentState);
//                    continue;
//                }
            }
//            cout << "next state queued, please sort!\n";
        }
        return this->path;
    }
    //So now that the queue is empty traverse the states from the last one by each parent and parent
//        State<T> *state = searchable->getGoalState();
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