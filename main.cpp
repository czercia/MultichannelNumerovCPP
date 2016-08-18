#include <iostream>
//#define ARMA_USE_LAPACK
//#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

#include"Tester.h"

using namespace std;

double V(int i, int j, double x) {
    return (i - j)*x  + 5 + i + j* j;}

int main() {

    Tester test(V);
    test.testSolverU();
    std::cout << "solve" << std::endl;
    test.testSolve();
    std::cout << "Hihi" ;


    return 0;


}