/**
 * @file src/program/menus_Inventory.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Inventory::Inventory() {
        _shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        _shadow.setPosition(sf::Vector2f(0, 0));
        _shadow.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        _wInve = new Window(resources.dictionary["gui.window.inventory"], sf::Vector2f(765, 470), (sf::Vector2f)(settings.graphics.resolution/2u-sf::Vector2u(382, 225)));
            for (int i=0; i<8; i++) {
                for (int j=0; j<4; j++) {
                    *_wInve += new Slot(sf::Vector2f(80, 80), sf::Vector2f(10+i*95, 30+j*95));
                }
            }
            *_wInve += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
            component(_wInve, Button, 0)->setPosition(sf::Vector2f(_wInve->getPosition().x+_wInve->getSize().x-component(_wInve, Button, 0)->getSize().x-15, settings.graphics.resolution.y/2+235-component(_wInve, Button, 0)->getSize().y-5));
        _wInve->setVisible(false);

#undef component

    }

    Inventory::~Inventory() {
        delete _wInve;
    }

    void Inventory::open() {
        _wInve->setVisible(true);
    }

    void Inventory::close() {
        _wInve->setVisible(false);
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (_wInve->isVisible()) {
            if (component(_wInve, Button, 0)->isPressed(rw, e))
                g->pause(false);
            for (int i=0; i<32; i++) {
                if (component(_wInve, Slot, i)->isPressed(rw, e)) {

                }
            }
        }

#undef component

    }

    void Inventory::draw(sf::RenderWindow& rw) {
        rw.draw(_shadow);
        _wInve->draw(rw);
    }

    bool Inventory::isOpen() {
        return _wInve->isVisible();
    }

}
