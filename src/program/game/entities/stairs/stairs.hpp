/**
 * @file src/program/game/entities/stairs/stairs.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef stairs_hpp
#define stairs_hpp

#include "../entities.hpp"

namespace rr {

    class Stairs {
    private:
        sf::Sprite body_;
        bool       upwards_;
    public:
         Stairs();
        ~Stairs();
    };

}

#endif // stairs_hpp
