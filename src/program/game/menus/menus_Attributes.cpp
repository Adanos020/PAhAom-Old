/**
 * @file src/program/game/menus/Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

#include <cstdio>

extern rr::Dictionary dictionary;
extern rr::Resources resources;

namespace rr {

    Attributes::Attributes(sf::RenderWindow& rw) {
#define component(w, c, i) w->getComponent<c>(i)
        wAttr = new Window(dictionary.gui.window.attributes, sf::Vector2f(400, 300), (sf::Vector2f)rw.getSize()/2.f-sf::Vector2f(200, 150));
            wAttr->addComponent(new Text(sf::Vector2f(10,  20), "stats",  resources.font.Unifont, 30),                   true); // stats
            wAttr->addComponent(new Text(sf::Vector2f(250, 20), "values", resources.font.Unifont, 30, sf::Color::Green), true); // values
            wAttr->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                component(wAttr, Button, 0)->setPosition(sf::Vector2f(wAttr->getPosition().x+wAttr->getSize().x/2-component(wAttr, Button, 0)->getSize().x/2,
                                                                      wAttr->getPosition().y+wAttr->getSize().y-component(wAttr, Button, 0)->getSize().y-10));
#undef component
    }

    Attributes::~Attributes() {
        delete wAttr;
    }

    void Attributes::open() {
        wAttr->setVisible(true);
    }

    void Attributes::update(Player* p) {
        puts("Attributes updated!"); // yeah...
    }

    void Attributes::buttonEvents(sf::RenderWindow& rw, Game* g) {
#define component(w, c, x) w->getComponent<c>(x)

        if (wAttr->isVisible()) {
            if (component(wAttr, Button, 0)->isPressed(rw)) {
                wAttr->setVisible(false);
                g->pause(false);
            }
        }

#undef component
    }

    void Attributes::draw(sf::RenderWindow& rw) {
        wAttr->draw(rw);
    }

    bool Attributes::isOpen() {
        return wAttr->isVisible();
    }

}
