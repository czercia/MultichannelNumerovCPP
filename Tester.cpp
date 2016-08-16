//
// Created by marta on 15.08.16.
//

#include "Tester.h"

Tester::Tester() {
    params = Parameters();
    testSolver = Solver(params);
}

void Tester::testParamsSetV(MN::Potential func) {
    params.userV = func;
    params.calculateVList();
    VList = params.getVList();
}

void Tester::testSolverU() {
    double E = 1;
    for(int i = 0; i < params.N(); i++) {
        testSolver.calculateU(i, E);
    }

}


