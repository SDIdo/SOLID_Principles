//
// Created by roy on 1/5/19.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int width, int height, Entry *start, Entry *finish,
                         vector<vector<int>> matrixGrid) : start(start), finish(finish) {
    this->width = width;
    this->height = height;
    // for each entry in the matrix create a state and store in map.
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Entry *entry = new Entry(i, j);
            State<Entry> *s = new State<Entry>(entry);
            s->setCost(matrixGrid.at(i).at(j)); // set the starting cost for each state entry.
            this->matrixStates[to_string(i) + "," + to_string(j)] = s;
        }
    }
}

vector<vector<int>> MatrixGraph::getStateGrid() {
    return this->matrixGrid;
}

/**
 * This method returns the initial state of the graph (starting vertex).
 * @return initial state of the graph.
 */
State<Entry> MatrixGraph::getInitialState() {
    return this->start;
}

/**
 * This method returns the goal state of the graph (finish vertex).
 * @return goal state of the graph.
 */
State<Entry> MatrixGraph::getGoalState() {
    return this->finish;
}

/**
 * This method receives current state of the matrix graph, and
 * returns a list of all the possible states which are
 * reachable from it.
 * @param currentState current state entry.
 * @return list of all reachable state entries.
 */
list<State<Entry>*> MatrixGraph::getAllPossibleStates(State<Entry> currentState) {
    list<State<Entry>*> possibleStates;

    int iValue = currentState.getState()->getI();
    int jValue = currentState.getState()->getJ();

    if (jValue + 1 < this->width) {
        possibleStates.push_back(this->matrixStates.at(to_string(iValue) + to_string(jValue + 1)));
    }
    if (jValue - 1 >= 0) {
        possibleStates.push_back(this->matrixStates.at(to_string(iValue) + to_string(jValue - 1)));
    }

    if (iValue + 1 < this->height) {
        possibleStates.push_back(this->matrixStates.at(to_string(iValue + 1) + to_string(jValue)));
    }
    if (iValue - 1 >= 0) {
        possibleStates.push_back(this->matrixStates.at(to_string(iValue - 1) + to_string(jValue)));
    }
    return possibleStates;
}

template
class State<Entry>;