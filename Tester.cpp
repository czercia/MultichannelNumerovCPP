//
// Created by marta on 15.08.16.
//

#include "Tester.h"

Tester::Tester(MN::Potential func) {
    params = Parameters();
    params.userV = func;
    params.calculateVList();
    testSolver = Solver(params);


    VList = params.getVList();

}


void Tester::testSolverU() {

    double E = 1;

    for (int i = 0; i < params.N(); i++) {
        try {
            testSolver.calculateU(i, E);
        }
        catch (...) {
            std::cout << "Error calculating U for E = " << E <<", i = " << i << std::endl;
        }
    }

}

void Tester::testSolve() {
    testSolver.solve();
}





