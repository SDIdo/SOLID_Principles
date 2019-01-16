//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_STATE_H
#define PROJECTPART2_STATE_H

#include "Entry.h"

template<class T>
class State {
    T *state;
    double cost, distance;
    State<T> *cameFrom;

public:

    /**
    * Constructor of State. receives the state.
    * @param state state for the State object.
    */
     State(T *state) {
        this->state = state;
        this->cameFrom = nullptr;
        this->cost = 0;
    }

    ~State() {
         delete(this->state);
     }

    /**
    * This method returns the state.
    * @return state of the State object.
    */
    T *getState() {
        return this->state;
    }

    /**
    * This method sets the new cost of getting to the state.
    * @param newCost cost of the state.
    */
    void setCost(double newCost) {
        this->cost = newCost;
    }

    /**
     * This method returns the cost to get to it.
     * @return value of the cost.
     */
    double getCost() {
        return this->cost;
    }

    /**
     * This method sets the new father state of the state.
     * @param newFatherState father state of the state.
     */
    void setCameFrom(State<T> *newFatherState) {
        this->cameFrom = newFatherState;
    }

    /**
     * This method returns the father of the state.
     * @return previous state (father of the state).
     */
    State<T> *getCameFrom() {
        return this->cameFrom;
    }

    /**
     * This method checks if a given state is equal to the state.
     * @param s given state.
     * @return true if the same state, else false.
     */
    bool equals(State<T> *otherState) {
        return this->state == otherState->getState();
    }

    /**
     * This method sets the distance of the state from the goal state.
     * @param newDistance new distance.
     */
    void setDistance(double newDistance) {
        this->distance = newDistance;
    }

    /**
     * This method returns the distance from the goal state.
     * @return distance from goal state.
     */
    double getDistance() {
        return this->distance;
    }
};

#endif //PROJECTPART2_STATE_H
