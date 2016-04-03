/**
 * @file src/program/game/menus/Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "menus.h"

#include <cstdio>

extern std::map<sf::String, sf::String> dictionary;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;

namespace rr {

    Attributes::Attributes(sf::RenderWindow& rw) {
#define dict(s) dictionary[s]

        wAttr = new Window(nullptr, dict("gui.window.attributes"), sf::Vector2f(400, 220), (sf::Vector2f)rw.getSize()/2.f-sf::Vector2f(200, 110));
        wAttr->addComponent(new Button(wAttr, sf::Vector2f(10, 180), dict("gui.button.quit"), 30));
        wAttr->setVisible(false);

#undef dict
    }

    Attributes::~Attributes() {
        delete wAttr;
    }

    void Attributes::update(Player* p) {
        puts("Attributes updated!"); // yeah...
    }

    void Attributes::buttonEvents(sf::RenderWindow& rw) {
#define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define cmc(w, c, x) w->getComponent<c>(x)->containsMouseCursor(rw)

        if (wAttr->isVisible()) {
            if (cmc(wAttr, Button, 0) && isMLBPressed) wAttr->setVisible(false);
        }

#undef isMLBPressed
#undef cmc
    }

    void Attributes::draw(sf::RenderWindow& rw) {
        wAttr->draw(rw);
    }

}
