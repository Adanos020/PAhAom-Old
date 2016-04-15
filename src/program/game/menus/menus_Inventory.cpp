/**
 * @file src/program/menus_Inventory.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"


extern rr::Settings settings;

extern rr::Resources resources;

namespace rr {

    Inventory::Inventory(sf::RenderWindow& rw) {
        shadow.setSize((sf::Vector2f)rw.getSize());
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define dict(x) dictionary[x]
#define component(w, c, i) w->getComponent<c>(i)

        wInve = new Window(resources.dictionary["gui.window.inventory"], sf::Vector2f(725, 470), sf::Vector2f(rw.getSize().x/2-362.5, rw.getSize().y/2-225));
            for (int i=0; i<8; i++) {
                for (int j=0; j<4; j++) {
                    wInve->addComponent(new Slot(sf::Vector2f(75, 75), sf::Vector2f(10+i*90, 30+j*90)), true);
                }
            }
            wInve->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
            component(wInve, Button, 0)->setPosition(sf::Vector2f(wInve->getPosition().x+wInve->getSize().x-component(wInve, Button, 0)->getSize().x-15, rw.getSize().y/2+225-component(wInve, Button, 0)->getSize().y-5));
        wInve->setVisible(false);

#undef dict
#undef component

    }

    Inventory::~Inventory() {
        delete wInve;
    }

    void Inventory::open() {
        wInve->setVisible(true);
    }

    void Inventory::close() {
        wInve->setVisible(false);
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wInve->isVisible()) {
            if (component(wInve, Button, 0)->isPressed(rw, e))
                g->pause(false);
            for (int i=0; i<32; i++) {
                if (component(wInve, Slot, i)->isPressed(rw, e)) {

                }
            }
        }

#undef component

    }

    void Inventory::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        wInve->draw(rw);
    }

    bool Inventory::isOpen() {
        return wInve->isVisible();
    }

}
