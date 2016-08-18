//
// Created by marta on 14.08.16.
//

#include "Parameters.h"

double Parameters::x(int i) {
    return this->xMin + i * this->dx;
}

double Parameters::E(int i) {
    return this->EMin + i * this->dE;
}

Parameters::Parameters() {
    xMin = 0.1;
    xMax = 1;
    dx = 0.1;
    EMin = -10;
    dE = 1;
    EMax = 10;
    epsilon = 0.01;
    nChannels = 2;
    nStates = 10;
    arma::mat A(nChannels, nChannels);
    A.fill(0);
    INV_R0_Inw = A;
    INV_R0_Outw = A;

}

void Parameters::calculateVList() {
    arma::cube V_list(nChannels, nChannels, N());
    int ind;
    #pragma omp parallel for
    for (ind = 0; ind < N(); ind++) {
        for (int i = 0; i < nChannels; ++i) {
            for (int j = 0; j < nChannels; ++j) {
                V_list.slice(ind)(i, j) = V(i, j, x(ind));
            }
        }
    }
    VList = V_list;
}

int Parameters::N() {
    return (xMax - xMin) / dx;
}

double Parameters::V(int i, int j, double x) {
    return  userV(i, j, x);

}

void Parameters::setUserV(MN::Potential userV) {
    Parameters::userV = userV;
}

const arma::cube &Parameters::getVList() const {
    return VList;
}
