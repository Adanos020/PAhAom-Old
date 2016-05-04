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
        shadow_.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        wInve_ = new Window(resources.dictionary["gui.window.inventory"], sf::Vector2f(765, 470), (sf::Vector2f)(settings.graphics.resolution/2u-sf::Vector2u(382, 225)));
            for (int i=0; i<8; i++) {
                for (int j=0; j<4; j++) {
                    *wInve_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(10+i*95, 30+j*95));
                }
            }
            *wInve_ += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
            component(wInve_, Button, 0)->setPosition(sf::Vector2f(wInve_->getPosition().x+wInve_->getSize().x-component(wInve_, Button, 0)->getSize().x-15, settings.graphics.resolution.y/2+235-component(wInve_, Button, 0)->getSize().y-5));
        wInve_->setVisible(false);

#undef component

    }

    Inventory::~Inventory() {
        delete wInve_;
    }

    void Inventory::open() {
        wInve_->setVisible(true);
    }

    void Inventory::close() {
        wInve_->setVisible(false);
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wInve_->isVisible()) {
            if (component(wInve_, Button, 0)->isPressed(rw, e))
                g->pause(false);
            for (int i=0; i<32; i++) {
                if (component(wInve_, Slot, i)->isPressed(rw, e)) {

                }
            }
        }

#undef component

    }

    void Inventory::draw(sf::RenderWindow& rw) {
        rw.draw(shadow_);
        wInve_->draw(rw);
    }

    bool Inventory::isOpen() {
        return wInve_->isVisible();
    }

}
