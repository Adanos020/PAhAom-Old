/**
 * @file src/program/game/menus/menus_BookOfSpells.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "menus.hpp"

namespace rr {

    BookOfSpells::BookOfSpells() {

    }

    BookOfSpells::~BookOfSpells() {
        delete wBofs;
    }

    void BookOfSpells::open() {

    }

    void BookOfSpells::close() {

    }

    void BookOfSpells::buttonEvents(sf::RenderWindow& rw, sf::Event& ev, Game* g) {

    }

    void BookOfSpells::draw(sf::RenderWindow& rw) {

    }

    bool BookOfSpells::isOpen() {
        return wBofs->isVisible();
    }

}
