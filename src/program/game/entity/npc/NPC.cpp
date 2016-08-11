/**
 * @file src/program/game/entity/npc/NPC.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "NPC.hpp"

namespace rr {

    void NPC::placeDetectors() {
        playerDetectors_[0] = getGridPosition() + sf::Vector2i(-1, -1); // TOP LEFT
        playerDetectors_[1] = getGridPosition() + sf::Vector2i( 0, -1); // TOP
        playerDetectors_[2] = getGridPosition() + sf::Vector2i(+1, -1); // TOP RIGHT
        playerDetectors_[3] = getGridPosition() + sf::Vector2i(+1,  0); // RIGHT
        playerDetectors_[4] = getGridPosition() + sf::Vector2i(+1, +1); // BOTTOM RIGHT
        playerDetectors_[5] = getGridPosition() + sf::Vector2i( 0, +1); // BOTTOM
        playerDetectors_[6] = getGridPosition() + sf::Vector2i(-1, +1); // BOTTOM LEFT
        playerDetectors_[7] = getGridPosition() + sf::Vector2i(-1,  0); // LEFT
    }

    void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &Resources::texture.items;
        target.draw(body_, states);
    }

    void NPC::setGridPosition(sf::Vector2i pos) {
        body_.setPosition((sf::Vector2f) pos*80.f);
        placeDetectors();
    }

    sf::Vector2i NPC::getGridPosition() const {
        return (sf::Vector2i) body_.getPosition()/80;
    }

    void NPC::setPosition(sf::Vector2f pos) {
        body_.setPosition(pos);
        placeDetectors();
    }

    sf::Vector2f NPC::getPosition() const {
        return body_.getPosition();
    }

    bool NPC::collides(Entity* e) const {
        return e->getBounds().intersects(getBounds());
    }

    sf::FloatRect NPC::getBounds() const {
        return body_.getGlobalBounds();
    }

    void NPC::setAttitude(Attitude attitude) {
        attitude_ = attitude;
    }

    void NPC::setState(State state) {
        state_ = state;
    }

    NPC::Attitude NPC::getAttitude() const {
        return attitude_;
    }

    NPC::State NPC::getState() const {
        return state_;
    }

    NPC::Attrs NPC::getAttributes() const {
        return attrs_;
    }

    int NPC::detects(Player* p) const {
        for (int i=0; i<8; ++i) {
            if (  p->getGridPosition() == playerDetectors_[i]
                ) return i;
        }
        return -1;
    }

}
