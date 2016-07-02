/**
 * @file src/program/game/entities/npc/npc_Teacher.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "npc.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Teacher::Teacher(Type type)
    : type_(type) {

        standingStill_.setSpriteSheet(resources.texture.npc);

        for (int i=0; i<((type_ == KUNG_FU_MASTER)?20:10); i++) {
            standingStill_.addFrame(sf::IntRect(i*16, type_*16, 16, 16));
        }

        currentAnimation_ = &standingStill_;

        body_.setAnimation      (*currentAnimation_);
        body_.setLooped         (true);
        if (  type_ == MAGE
            ) body_.setFrameTime(sf::seconds(.4f));
        else  body_.setFrameTime(sf::seconds(.2f));
        body_.scale             (sf::Vector2f(5, 5));
    }

    Teacher::Teacher(Teacher const& teacher)
    : type_(teacher.type_) {

        body_             = teacher.body_;
        currentAnimation_ = teacher.currentAnimation_;
    }

    void Teacher::talk() {

    }

    void Teacher::update(sf::Time timeStep) {
        body_.update(timeStep);
        body_.play(*currentAnimation_);
    }

}
