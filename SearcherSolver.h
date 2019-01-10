//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_SEARCHERSOLVER_H
#define PROJECTPART2_SEARCHERSOLVER_H

#include "../Solver.h"
#include "Searchable.h"
#include "Searcher.h"

/**
 * Object adapter from solver to searcher.
 */
class SearcherSolver : Solver<Searchable<Entry>, string> {
    Searcher *searcher;

public:
    SearcherSolver(Searcher *searcher) {
        this->searcher = searcher;
    }
    virtual string solve(Searchable<Entry> *searchable) {
        return this->searcher->search(searchable);
    }
};

#endif //PROJECTPART2_SEARCHERSOLVER_H
