//
// Created by marta on 15.08.16.
//

#include "Solver.h"


Solver::Solver(const Parameters &params) : params(params) {}

arma::mat Solver::calculateU(int j, double E) {

    arma::mat Id, T, U;
    Id = arma::eye<arma::mat>(params.getNChannels(), params.getNChannels());

    T = -(E * Id - params.getVList().slice(j)) / 12;
//    std::cout << "E = " <<E << std::endl;
//    (Id - T).print();
    try{
    U = (Id-T).i() * (2 * Id + 10 * T);}
    catch(std::runtime_error){
        (Id - T).print();
    }

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
    arma::mat INV_RBef;
    for (int j = 1; j < params.N(); j++) {
        if (j == 1) INV_RBef = RList.slice(j - 1);
        else INV_RBef = RList.slice(j - 1).i();
        arma::mat U = UList.slice(j);
        RList.slice(j) = calculateR(U, INV_RBef);
    }
    return RList;
}

arma::cube Solver::ROutward(arma::cube UList) {
    arma::cube RList(params.getNChannels(), params.getNChannels(), params.N());
    RList.slice(params.N() - 1) = params.getINV_R0_Inw();
    arma::mat INV_RBef;
    for (int j = params.N() - 2; j > -1; j--) {
        if (j == params.N() - 2) INV_RBef = RList.slice(j + 1);
        else INV_RBef = RList.slice(j + 1).i();
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
    double energy;
    int nE = 10;
    arma::cube RInw, ROutw, RInwBef, ROutwBef;
    int nodesNumber, nodesNumberBef;
    MN::VecDoub EList, numberOfNodesList;
    MN::VecDoub detRInw, detROutw;

    energy = params.E(0);
    stdCalculationsForE(RInwBef, ROutwBef, nodesNumberBef, energy, detRInw, detROutw);
    EList.push_back(energy);
    numberOfNodesList.push_back(nodesNumber);


    for (int j = 1; j < nE ; ++j) {
        energy = params.E(j);
        stdCalculationsForE(RInw, ROutw, nodesNumber, energy, detRInw, detROutw);
        EList.push_back(energy);
        numberOfNodesList.push_back(nodesNumber);


        if (nodesNumber > nodesNumberBef){
            bisection(params.E(j - 1), params.E(j));
        }
        else{
        RInwBef = RInw;
        ROutwBef = ROutw;
        nodesNumberBef = nodesNumber;
            continue;
 }
    }





}

int Solver::findM(MN::VecInt nodesIndInwH, MN::VecInt nodesIndInwL, MN::VecInt nodesIndOutwH, MN::VecInt nodesIndOutwL) {
    return 0;
}

double Solver::bisection(double EL, double EH) {

    double s;
    arma::cube RInwL, ROutwL, RInwH, ROutwH, RInwS, ROutwS;
    int nodesNumberL, nodesNumberH, nodesNumberS;
    MN::VecDoub EList, numberOfNodesList;
    MN::VecDoub detRInwL, detROutwL, detRInwH, detROutwH, detRInwS, detROutwS;
    stdCalculationsForE(RInwL, ROutwL, nodesNumberL, EL, detRInwL, detROutwL);
    stdCalculationsForE(RInwH, ROutwH, nodesNumberH, EH, detRInwH, detROutwH);

    MN::VecInt nodesIndicesLInw = findNodesIndices(detRInwL);
    MN::VecInt nodesIndicesHInw = findNodesIndices(detRInwH);
    MN::VecInt nodesIndicesLOutw = findNodesIndices(detROutwL);
    MN::VecInt nodesIndicesHOutw = findNodesIndices(detROutwH);

    int M = findM(nodesIndicesHInw, nodesIndicesLInw, nodesIndicesHOutw, nodesIndicesLOutw);

    if (nodesNumberL < nodesNumberH){
        s = EL;
        while((EH - EL )> params.getEpsilon()){
            s = (EH + EL)/2;
            stdCalculationsForE(RInwS, ROutwS, nodesNumberS, s, detRInwS, detROutwS);
            if ( nodesNumberL < nodesNumberS )
            {
                EH = s;
                nodesNumberH = nodesNumberS;
            }
            else if(nodesNumberH > nodesNumberS){
                EL = s;
                nodesNumberL = nodesNumberS;
            }
            else break;
        }
    }
    else{
        s=0;;
    }
    std::cout << s << std::endl;

    return s;

}
//double bisekcja(double E_1, double E_2, Parameters params) {
//    double s;
//    if (HF(E_1, params) * HF(E_2, params) < 0) {
//        s = E_1;
//        while ((E_2 - E_1) > params.epsilon) {
//            s = (E_1 + E_2) / 2;
//            if (HF(E_1, params) * HF(s, params) < 0) {
//                E_2 = s;
//            }
//            else if (HF(E_2, params) * HF(s, params) < 0) {
//                E_1 = s;
//            }
//            else break;
//        }
//    }
//    else {
//        s = 0;;
//    }
//    return s;
//}

void Solver::stdCalculationsForE(arma::cube &RInw, arma::cube &ROutw, int &nNodes, double E, MN::VecDoub &detsInw,
                                 MN::VecDoub &detsOutw) {
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










