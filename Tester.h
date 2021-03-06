//
// Created by marta on 15.08.16.
//

#ifndef MULTICHANNELNUMEROVCPP_TESTER_H
#define MULTICHANNELNUMEROVCPP_TESTER_H

#include "Parameters.h"
#include "Solver.h"
#include "MN.h"

class Tester {
    Parameters params;
    Solver testSolver;
    arma::cube VList;


public:
    Tester(MN::Potential func);
    void testParamsSetV(MN::Potential func);
    void testSolverU();
    void testSolve();

};


#endif //MULTICHANNELNUMEROVCPP_TESTER_H
