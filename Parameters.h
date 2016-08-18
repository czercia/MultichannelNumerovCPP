//
// Created by marta on 14.08.16.
//

#ifndef MULTICHANNELNUMEROVCPP_PARAMETERS_H
#define MULTICHANNELNUMEROVCPP_PARAMETERS_H
//#define ARMA_USE_LAPACK
#include <armadillo>
#include <string>
#include "MN.h"


class Parameters {

    double xMin;
    double xMax;
    double dx;
    double EMin;
    double dE;
    double EMax;
    double epsilon;
    int nChannels;
    int nStates;
    arma::mat INV_R0_Inw;
    arma::mat INV_R0_Outw;
    std::string resultsDirectory;
    arma::cube VList;





public:
    MN::Potential userV;
    void setUserV(MN::Potential userV);

    double x(int);
    double E(int);
    int N();
    void calculateVList();
    double V(int i, int j, double x);


    Parameters();

    void setINV_R0_Inw(const arma::mat &INV_R0_Inw) {
        Parameters::INV_R0_Inw = INV_R0_Inw;
    }

    void setINV_R0_Outw(const arma::mat &INV_R0_Outw) {
        Parameters::INV_R0_Outw = INV_R0_Outw;
    }

    const arma::mat &getINV_R0_Inw() const {
        return INV_R0_Inw;
    }

    const arma::mat &getINV_R0_Outw() const {
        return INV_R0_Outw;
    }


    int getNChannels() const {
        return nChannels;
    }

    void setNChannels(int nChannels) {
        Parameters::nChannels = nChannels;
    }

    const arma::cube &getVList() const;

    double getEpsilon() const {
        return epsilon;
    }
};


#endif //MULTICHANNELNUMEROVCPP_PARAMETERS_H
