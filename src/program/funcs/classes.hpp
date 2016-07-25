/**
 * @file src/program/funcs/funcs.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_CLASSES_HPP
#define FUNCS_CLASSES_HPP

namespace rr {

/// Tells if a given pointer points an object which has a base of a given class.
    template<class Base, class T>
    inline bool instanceof(const T* ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

}

#endif // FUNCS_CLASSES_HPP
