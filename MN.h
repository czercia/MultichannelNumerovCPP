//
// Created by marta on 15.08.16.
//

#ifndef MULTICHANNELNUMEROVCPP_MN_H
#define MULTICHANNELNUMEROVCPP_MN_H

#include <vector>

namespace MN{
    typedef std::vector<double> VecDoub;
    typedef std::vector<int> VecInt;
    typedef double (* Potential) (int, int, double);
}
#endif //MULTICHANNELNUMEROVCPP_MN_H
