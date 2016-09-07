/**
 * @file src/program/funcs/files.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef FUNCS_FILES_HPP
#define FUNCS_FILES_HPP

#include <fstream>
#include <string>

#include "../game/entity/Entity.hpp"

namespace rr
{

    ////////////////////////////////////////////////////////////////////////
    /// \brief Reads a variable data from file.
    ////////////////////////////////////////////////////////////////////////
    template <typename T> inline void
    readFile(std::ifstream& f, T& x)
    {
        f >> x;
        if (f.fail())
        {
            std::string param;
            f.clear();
            f.sync ();
            int pos = f.tellg();
            f >> param;
            throw std::invalid_argument("Wrong data in some type: " + param + ", position: " + std::to_string(pos));
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Reads an entity's data from file.
    ////////////////////////////////////////////////////////////////////////
    inline void
    readEntity(std::ifstream& f, Entity* x)
    {
        *x << f;
        if (f.fail())
        {
            std::string param;
            f.clear();
            f.sync();
            f >> param;
            int pos = f.tellg();
            throw std::invalid_argument("Wrong data in entity: " + param + ", position: " + std::to_string(pos));
        }
    }

}

#endif // FUNCS_FILES_HPP
