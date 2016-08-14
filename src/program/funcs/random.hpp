/**
 * @file src/program/funcs/random.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_RANDOM_HPP
#define FUNCS_RANDOM_HPP

#include <cstdlib>
#include <vector>

namespace rr {

    ////////////////////////////////////////////////////////////////////////
    /// \brief Returns a random integer in a range between given values.
    ///
    /// \param a the lower limit
    /// \param b the upper limit
    ////////////////////////////////////////////////////////////////////////
    inline int range(int a, int b) {
        return rand()%(b-a+1)+a;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Returns a boolean value depending on the given probability.
    ///
    /// There is a chance equal to (numerator/denominator) that this
    /// function will return true.
    ////////////////////////////////////////////////////////////////////////
    inline bool chance(int numerator, int denominator) {
        return rand()%denominator < numerator;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Returns a boolean value depending on the given probability.
    ///
    /// There is a chance equal to the percentage that this function will
    /// return true. To make it work you need to pass the percentage as a
    /// number in range between 0 and 1, eg. 15.27% = 0.1527. Note: the
    /// maximal handled accuracy is to 0.001 so if you use any bigger
    /// accuracy then it just will be rounded, eg. 0.12345 will become 0.123
    ////////////////////////////////////////////////////////////////////////
    inline bool chance(double percentage) {
        percentage *= 1000;
        return rand()%1000 < (int) percentage;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Returns a random element of a given array.
    ////////////////////////////////////////////////////////////////////////
    template <typename T> inline T elementOf(T arr[], unsigned size) {
        return arr[rand()%size];
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Returns a random element of a given vector.
    ////////////////////////////////////////////////////////////////////////
    template <typename T> inline T elementOf(std::vector<T> vec) {
        return vec[rand()%vec.size()];
    }

}

#endif // FUNCS_RANDOM_HPP
