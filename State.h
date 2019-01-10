//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_STATE_H
#define PROJECTPART2_STATE_H

#include "Entry.h"

template<class T>
class State {
    T *state;
    double cost;
    State<T> *cameFrom;

public:

    /**
    * Constructor of State. receives the state.
    * @param state state for the State object.
    */
     State(T *state) {
        this->state = state;
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
};

#endif //PROJECTPART2_STATE_H
