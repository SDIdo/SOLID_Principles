//
// Created by roy on 1/10/19.
//

#ifndef PROJECTPART2_SEARCHERSOLVER_H
#define PROJECTPART2_SEARCHERSOLVER_H

#include "../Solver.h"
#include "Searchable.h"
#include "Searcher.h"

/**
 * Class Searcher Solver provides an object adapter from solver to searcher.
 * A searcher solver contains a searcher and the solve method will be
 * applying the search on the searchable problem.
 * @tparam T generic class for the searchable.
 * @tparam Solution generic solution class.
 */
template<class T, class Solution>
class SearcherSolver : public Solver<Searchable<T>, Solution> {
    Searcher<T, Solution> *searcher;

public:
    /**
     * Constructor for searcher solver. receives a searcher.
     * @param searcher
     */
    SearcherSolver(Searcher<T, Solution> *searcher) {
        this->searcher = searcher;
    }

    /**
     * Destructor of searcher solver.
     */
    ~SearcherSolver() {
        delete (this->searcher);
    }

    /**
     * This method applies the adaptation. The solve method of the Solver
     * interface uses the search method of the searcher.
     * @param searchable object for the searching.
     * @return solution from the search.
     */
    virtual Solution solve(Searchable<T> *searchable) {
        return this->searcher->search(searchable);
    }
};

#endif //PROJECTPART2_SEARCHERSOLVER_H
