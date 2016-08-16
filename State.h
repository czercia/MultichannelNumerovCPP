//
// Created by marta on 14.08.16.
//

#ifndef MULTICHANNELNUMEROVCPP_STATE_H
#define MULTICHANNELNUMEROVCPP_STATE_H

#include <vector>

class State {

    double E;
    int n;

    int degeneracy;
    std::vector<int> nodesIndicesInw;
    std::vector<int> nodesIndicesOutw;
    int M;


};


#endif //MULTICHANNELNUMEROVCPP_STATE_H
