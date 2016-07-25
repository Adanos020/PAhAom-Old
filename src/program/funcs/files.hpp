/**
 * @file src/program/funcs/files.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_FILES_HPP
#define FUNCS_FILES_HPP

#include <fstream>

#include "../game/entity/ALL.hpp"

namespace rr {

/// Reads a variable data from file
    template <typename T>
    inline void readFile(std::ifstream& f, T& x) {
        f >> x;
        if (f.fail()) {
            std::string param;
            f.clear();
            f.sync ();
            f >> param;
            throw std::invalid_argument("Wrong data: " + param);
        }
    }

/// Reads an entity's data from file
    inline void readEntity(std::ifstream& f, Entity* x) {
        *x << f;
        if (f.fail()) {
            std::string param;
            f.clear();
            f.sync();
            f >> param;
            throw std::invalid_argument("Wrong data: " + param);
        }
    }

}

#endif // FUNCS_FILES_HPP
