/**
 * @file src/program/game/entities/stairs/stairs_Stairs.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "stairs.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Stairs::Stairs(bool upwards)
    : upwards_ (upwards) {

        body_.setTexture(resources.texture.objects);
        body_.setScale(sf::Vector2f(5, 5));
        body_.setTextureRect(sf::IntRect(upwards?16:0, 64, 16, 16));
    }

    Stairs::Stairs(Stairs const& stairs)
    : body_    (stairs.body_),
      upwards_ (stairs.upwards_) {}

    void Stairs::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
