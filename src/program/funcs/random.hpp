/**
 * @file src/program/funcs/random.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_RANDOM_HPP
#define FUNCS_RANDOM_HPP

#include <cstdlib>

namespace rr {

/// There is a chance equal to (numerator/denominator) that this function will return true.
    inline bool chance(int numerator, int denominator) {
        return rand()%denominator < numerator;
    }

/// There is a chance equal to the percentage that this function will return true.
/// To make it work you need to pass the percentage as a number in range between 0 and 1
/// eg. 15.27% = 0.1527
    inline bool chance(double percentage) {
        return false;
    }

}

#endif // FUNCS_RANDOM_HPP