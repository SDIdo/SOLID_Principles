////
//// Created by roy on 1/5/19.
////
//
//#ifndef PROJECTPART2_MATRIXGRAPH_H
//#define PROJECTPART2_MATRIXGRAPH_H
//
//
//#include "Searchable.h"
//#include "Entry.h"
//#include <unordered_map>
//
///**
// * Matrix graph is searchable, with states each defined
// * by an entry. Therefore it can return the states.
// */
//class MatrixGraph : public Searchable<Entry> {
//unordered_map<string, State<Entry>> matrixStates;
//State<Entry> start, finish;
//int width, height;
//public:
//    MatrixGraph(int width, int height, Entry start, Entry finish);
//    State<Entry> getInitialState();
//    State<Entry> getGoalState();
//    list<State<Entry>> getAllPossibleStates(State<Entry> s);
//};
//
//
//#endif //PROJECTPART2_MATRIXGRAPH_H
