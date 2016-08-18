//
// Created by marta on 15.08.16.
//

#include "Solver.h"


Solver::Solver(const Parameters &params) : params(params) {}

arma::mat Solver::calculateU(int j, double E) {

    arma::mat Id, T, U;
    Id = arma::eye<arma::mat>(params.getNChannels(), params.getNChannels());

    T = -(E * Id - params.getVList().slice(j)) / 12;
    U = (Id-T).i() * (2 * Id + 10 * T);

    return U;
}

Solver::Solver() {}

arma::mat Solver::calculateR(arma::mat U, arma::mat INV_RBef) {
    arma::mat R;
    R = U - INV_RBef;
    return R;
}

arma::cube Solver::RInward(arma::cube UList) {
    arma::cube RList(params.getNChannels(), params.getNChannels(), params.N());
    RList.slice(0) = params.getINV_R0_Inw();
    for (int j = 1; j < params.N(); j++) {
        arma::mat INV_RBef = RList.slice(j - 1).i();
        arma::mat U = UList.slice(j);
        RList.slice(j) = calculateR(U, INV_RBef);
    }
    return RList;
}

arma::cube Solver::ROutward(arma::cube UList) {
    arma::cube RList(params.getNChannels(), params.getNChannels(), params.N());
    RList.slice(params.N() - 1) = params.getINV_R0_Inw();
    for (int j = params.N() - 2; j > -1; j--) {
        arma::mat INV_RBef = RList.slice(j + 1).i();
        arma::mat U = UList.slice(j);
        RList.slice(j) = calculateR(U, INV_RBef);
    }
    return RList;
}

MN::VecDoub Solver::detRList(arma::cube RList) {
    MN::VecDoub detList;
    double det;
    for (int i = 0; i < params.N(); i++) {
        det = arma::det(RList.slice(i));
        detList.push_back(det);
    }
    return detList;
}


MN::VecInt Solver::findNodesIndices(MN::VecDoub detR_List) {
    MN::VecInt nodesIndices;
    for (int i = 0; i < detR_List.size(); ++i) {
        if (detR_List[i] < 0) { nodesIndices.push_back(i); }
    }
    return nodesIndices;
}

int Solver::countNodes(MN::VecDoub detR_List) {
    int numberOfNodes = 0;
    for (int i = 0; i < detR_List.size(); ++i) {
        if (detR_List[i] < 0) { numberOfNodes ++; }
    }
    return numberOfNodes;
}



void Solver::solve() {
    params.calculateVList();
    arma::cube VList = params.getVList();
    double E;
    int nE = 2;
    arma::cube RInw, ROutw, RInwBef, ROutwBef;
    int nodesNumber, nodesNumberBef;
    MN::VecDoub EList, numberOfNodesList;
    MN::VecDoub detRInw, detROutw;

    E = params.E(0);
    stdCalculationsForE(RInwBef, ROutwBef, nodesNumberBef, E, VList, detRInw, detROutw);
    EList.push_back(E);
    numberOfNodesList.push_back(nodesNumber);


    for (int j = 1; j < nE ; ++j) {
        E = params.E(j);
        stdCalculationsForE(RInw, ROutw, nodesNumber, E, VList, detRInw, detROutw);
        EList.push_back(E);
        numberOfNodesList.push_back(nodesNumber);

    }





}

int Solver::findM(MN::VecInt nodesIndInwH, MN::VecInt nodesIndInwL, MN::VecInt nodesIndOutwH, MN::VecInt nodesIndOutwL) {
    return 0;
}

void Solver::bisection(double EL, double EH) {

}

void Solver::stdCalculationsForE(arma::cube &RInw, arma::cube &ROutw, int &nNodes, double E, arma::cube VList,
                                 MN::VecDoub &detsInw, MN::VecDoub &detsOutw) {
    arma::cube UList(params.getNChannels(), params.getNChannels(), params.N());
    for (int j = 0; j < params.N(); j++){
        UList.slice(j) = calculateU(j, E);
    }
    RInw = RInward(UList);
    ROutw = ROutward(UList);
    detsInw = detRList(RInw);
    detsOutw = detRList(ROutw);

    int nodesInw = countNodes(detsInw);
    int nodesOutw = countNodes(detsOutw);

    if (nodesInw != nodesOutw)
        std::cout << "number of nodes calculated inward and outward is different";
    else nNodes = nodesInw;
}








