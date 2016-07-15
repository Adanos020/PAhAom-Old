/**
 * @file src/program/funcs/files.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef files_h
#define files_h

#include <fstream>

namespace rr {

/// Reads a variable data from file
    template <typename T>
    inline void readFile(std::ifstream& f, T& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw std::invalid_argument("Wrong data: " + param);
        }
    }

/// Reads an entity's data from file
    inline void readEntity(std::ifstream& f, Entity* x) {
        std::string param;
        *x << f;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw std::invalid_argument("Wrong data: " + param);
        }
    }

}

#endif // files_h
