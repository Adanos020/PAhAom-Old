/**
 * @file src/program/funcs/classes.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_CLASSES_HPP
#define FUNCS_CLASSES_HPP

namespace rr {

    ////////////////////////////////////////////////////////////////////////
    /// \brief Tells if a given pointer points an object which has a base of
    /// a given class.
    ///
    /// \param Base the base class of which we want to check if the pointed
    /// object is an instance
    /// \param T the class of which we know that the pointed object is an
    /// instance
    /// \param ptr the pointer to the object we want to check.
    ////////////////////////////////////////////////////////////////////////
    template <class Base, class T>
    inline bool instanceof(const T* ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

}

#endif // FUNCS_CLASSES_HPP
