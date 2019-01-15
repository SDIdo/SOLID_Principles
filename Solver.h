//
// Created by roy on 1/3/19.
//

#ifndef PROJECTPART2_SOLVER_H
#define PROJECTPART2_SOLVER_H

#include <string>
using namespace std;

/**
 * Interface of solver.
 * Solvers could solve a given problem.
 */
template <class Problem, class Solution>
class Solver {
public:
    virtual Solution solve(Problem *problem) = 0; // solving the problem returns a solution.
    virtual ~Solver() = default;
};

#endif //PROJECTPART2_SOLVER_H
