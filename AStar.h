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

class AStar : public Searcher<Entry, vector<State<Entry>*>>{
private:
    //Always set your goals first ;)
    State<Entry> *goalState;
    //initialize cost maps
    map <State<Entry>*,double> globalCost;   //state costs + heuristics
    map <State<Entry>*,double> localCost;   //only state costs
    //initialize path
    vector<State<Entry>*> path;
    //initialize grayList
    vector<State<Entry>*> greyList;
    //initializing operations queue
    queue<State<Entry> *> exploringQueue;

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
    bool checkInHeuristicsMap(State<Entry>* state) {
        map<State<Entry> *, double>::iterator it;
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
        return astar(currentState, searchable);
    }
///**
// * function simulates a priority queue //@TODO learn to use the native priority queue.
// * @param q - a queue to sort.
// * note: all that in the queue has heuristic value.
// */
//    void prioritize(queue<State<Entry>*> &q){
//        double minimumCost = DBL_MAX;
//        queue<State<Entry>*> priority;
//        State<Entry>* previousState;
//
//        while(!q.empty()){
//            State<Entry>* currentState = q.front();
//            cout << "[Prioritize]Current entry by cost " << currentState->getCost() << '\n';
//            q.pop();
//
//            if (currentState->getCost() < minimumCost){
//                minimumCost = currentState->getCost();
//                cout << "current state is cheaper, updated minimum cost\n";
//                if (!priority.empty()){
//                    cout << "queue wasn't empty so taking out the first and switching\n";
//                    previousState = priority.front();
//                    priority.pop();
//                    priority.push(currentState);
//                    priority.push(previousState);
//                }
//              else{
//              cout << "queue was empty! great! simply add.
//                priority.push(currentState);
//            }
//        }
//       cout << "so q is finished.. transfer!\n";
//       State<Entry>* toPut;
//       while (!priority.empty()){
//       toPut = priority.front();      //TODO might be wrong
//       q.push(toPut);
//       priority.pop();
//      }
//    }
/**
 *
 * @param currentState - state from which to look for the goal
 * @param searchable - a puzzle or any searchable field
 * @return the least expensive path to the finish.
 */
    virtual vector<State<Entry>*> astar(State<Entry> *currentState, Searchable<Entry> *searchable) {
        exploringQueue.push(currentState);
        greyList.push_back(currentState);
        this->numberOfEvaluated += 1;

        //Set local cost & set Heuristic             //@TODO if recursion this might be wrong to do here..
        this->localCost[currentState] = currentState->getCost();
        this->globalCost[currentState] = currentState->getCost() + this->calculateHeuristic(currentState);

        while (!exploringQueue.empty()) {
            this->numberOfEvaluated += 1;
            currentState = exploringQueue.front();
            exploringQueue.pop();

            cout << "[ASTAR]Current subject is " << currentState->getCost() << '\n';
            cout << "##################################\n";
            //explore all neighbors of current queued state
            list<State<Entry> *> neighbors = searchable->getAllPossibleStates(currentState);

            for (State<Entry> *neighbor : neighbors) {
                //That's the road's cost to here.
                double travelCost = currentState->getCost() + neighbor->getCost();

                //TEST ZONE
                cout << "[ASTAR]Current neigbor is " << "(" << neighbor->getState()->getI()
                     << ", " << neighbor->getState()->getJ() << ")" << " with travlCost: " << travelCost << "\n";
                //#

                //first check if was added to heuristics:
                if (!this->checkInHeuristicsMap(neighbor)) {
                    //Well not in Heuristic so should be set and added!
                    cout << neighbor->getState()->getI() << "wasn't in local cost, so adding it\n";
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
                    this->localCost[neighbor] = travelCost;
                    this->globalCost[neighbor] = travelCost + this->calculateHeuristic(neighbor);
//                exploringQueue.push(neighbor);
                    neighbor->setCameFrom(currentState);
                    continue;
                }
            }
            cout << "next state queued, please sort!\n";
//            this->prioritize(exploringQueue);
        }
        //So now that the queue is emptry traverse the states from the last one by each parent and parent
        State<Entry> *state = searchable->getGoalState();
        path.push_back(state);
        while (state->getCameFrom()) {
            cout << "Loop?\n";
            path.push_back(state->getCameFrom());
            state = state->getCameFrom();
        }
        return path;
    }

//        cout << "Let's see some heuristics: " << calculateHeuristic(searchable->getInitialState()) << '\n';

//        Entry *e1 = new Entry(0,0);
//        Entry *e2 = new Entry(0,1);
//        Entry *e3 = new Entry(1,0);
//        Entry *e4 = new Entry(1,1);
//        State<Entry> *s1 = new State<Entry>(e1);
//        State<Entry> *s2 = new State<Entry>(e2);
//        State<Entry> *s3 = new State<Entry>(e3);
//        State<Entry> *s4 = new State<Entry>(e4);
//        vector<State<Entry>*> vec;
//        return vec;
//    }
    virtual int getNumberOfNodesEvaluated(){
        return this->numberOfEvaluated;
    }
};


#endif //PROJECTPART2_BSTAR_H
