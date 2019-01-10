#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "Solver.h"
#include "StringReverser.h"
#include "Main.h"
#include "Algos/Searchable.h"
#include "Algos/Entry.h"
#include "Algos/State.h"
#include "Algos/MatrixGraph.h"

using namespace boot;

int main(int argc, char** argv) {
    /**
     * Main try for the project!
     */
    Main mainBoot;
    mainBoot.main(stoi(argv[1]));


/**
 * Try for the states, entries, Matrix Graph and Best First Search.
 */
//MatrixGraph matrixGraph(2,2, Entry(0,0), Entry(2,2));

//State<Entry> s = matrixGraph.getInitialState();
//cout << to_string(s.getState().getI()) << to_string(s.getState().getJ());

    return 0;
}
