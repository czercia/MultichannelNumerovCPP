#include <iostream>
//#define ARMA_USE_LAPACK
//#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

#include"Tester.h"

using namespace std;

double V(int i, int j, double x) {
    return (i + j)*x + 2;}

int main() {

    Tester test;
    test.testParamsSetV(V);
    test.testSolverU();
    std::cout << "Hihi" ;


    return 0;


}