//
// Created by marta on 15.08.16.
//

#ifndef MULTICHANNELNUMEROVCPP_SOLVER_H
#define MULTICHANNELNUMEROVCPP_SOLVER_H
//#define ARMA_USE_LAPACK
//#define ARMA_DONT_USE_WRAPPER
#include <armadillo>
#include <iostream>
#include "Parameters.h"
#include "MN.h"

class Solver {
    Parameters params;
public:
    Solver();

    Solver(const Parameters &params);

//private:

    arma::mat calculateU(int j, double E);
    arma::mat calculateR(arma::mat U, arma::mat INV_RBef);

public:
    arma::cube RInward(arma::cube UList);
    arma::cube ROutward(arma::cube UList);
    MN::VecInt findNodesIndices(MN::VecDoub detR_List);
    int countNodes(MN::VecDoub detR_List);
    MN::VecDoub detRList(arma::cube RList);
    int findM(MN::VecInt nodesIndInwH, MN::VecInt nodesIndInwL, MN::VecInt nodesIndOutwH, MN::VecInt nodesIndOutwL);
    void bisection(double EL, double EH);
    void solve();
    void stdCalculationsForE(arma::cube &RInw, arma::cube &ROutw, int &nNodes, double E, arma::cube VList,
                             MN::VecDoub &detsInw, MN::VecDoub &detsOutw);

};


#endif //MULTICHANNELNUMEROVCPP_SOLVER_H
