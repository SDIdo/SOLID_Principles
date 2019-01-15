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

template <class T, class Solution>
class SearcherSolver : public Solver<Searchable<T>, Solution> {
    Searcher<T, Solution> *searcher;

public:
    SearcherSolver(Searcher<T, Solution> *searcher) {
        this->searcher = searcher;
    }
    ~SearcherSolver() {
        delete(this->searcher);
    }
    virtual Solution solve(Searchable<T> *searchable) {
        return this->searcher->search(searchable);
    }
};

#endif //PROJECTPART2_SEARCHERSOLVER_H
