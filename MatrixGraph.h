//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_MATRIXGRAPH_H
#define PROJECTPART2_MATRIXGRAPH_H


#include "Searchable.h"
#include "Entry.h"
#include <unordered_map>
#include <map>
#include <vector>

/**
 * Matrix graph is searchable, with states each defined
 * by an entry. Therefore it can return the states.
 */
class MatrixGraph : public Searchable<Entry> {
    map<string, State<Entry> *> matrixStates;
    vector<vector<int>> matrixGrid;
    State<Entry> *start, *finish;
    int width, height;
public:

    MatrixGraph(int width, int height, Entry *start, Entry *finish, vector<vector<int>> matrixGrid) {
        this->width = width;
        this->height = height;
        // for each entry in the matrix create a state and store in map.
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == start->getI() && j == start->getJ()) {
                    this->start = new State<Entry>(new Entry(i,j));
                    this->start->setCost(matrixGrid.at(i).at(j));
                    this->matrixStates[to_string(i) + "," + to_string(j)] = this->start;
                    continue;
                }
                if (i == finish->getI() && j == finish->getJ()) {
                    this->finish = new State<Entry>(new Entry(i,j));
                    this->finish->setCost(matrixGrid.at(i).at(j));
                    this->matrixStates[to_string(i) + "," + to_string(j)] = this->finish;
                    continue;
                }
                Entry *entry = new Entry(i, j);
                State<Entry> *s = new State<Entry>(entry);
                s->setCost(matrixGrid.at(i).at(j)); // set the starting cost for each state entry.
                this->matrixStates[to_string(i) + "," + to_string(j)] = s;
            }
        }
    }

    /**
     * This method returns the initial state of the graph (starting vertex).
     * @return initial state of the graph.
     */
    virtual State<Entry> *getInitialState() {
        return this->start;
    }

    /**
     * This method returns the goal state of the graph (finish vertex).
     * @return goal state of the graph.
     */
    virtual State<Entry> *getGoalState() {
        return this->finish;
    }

    /**
     * This method receives current state of the matrix graph, and
     * returns a list of all the possible states which are
     * reachable from it.
     * @param currentState current state entry.
     * @return list of all reachable state entries.
     */
    virtual list<State<Entry> *> getAllPossibleStates(State<Entry> *currentState) {
        list<State<Entry> *> possibleStates;

        int iValue = currentState->getState()->getI();
        int jValue = currentState->getState()->getJ();

        if (jValue + 1 < this->width) {
            possibleStates.push_back(this->matrixStates.at(to_string(iValue) + "," + to_string(jValue + 1)));
        }
        if (jValue - 1 >= 0) {
            possibleStates.push_back(this->matrixStates.at(to_string(iValue) + "," + to_string(jValue - 1)));
        }

        if (iValue + 1 < this->height) {
            possibleStates.push_back(this->matrixStates.at(to_string(iValue + 1) + "," + to_string(jValue)));
        }
        if (iValue - 1 >= 0) {
            possibleStates.push_back(this->matrixStates.at(to_string(iValue - 1) + "," + to_string(jValue)));
        }
        return possibleStates;
    }

    vector<vector<int>> getStateGrid() {
        return this->matrixGrid;
    }
};


#endif //PROJECTPART2_MATRIXGRAPH_H
