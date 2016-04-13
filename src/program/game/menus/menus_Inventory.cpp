#include "menus.hpp"

extern rr::Dictionary dictionary;
extern rr::Settings settings;

extern rr::Resources resources;

namespace rr {

    Inventory::Inventory(sf::RenderWindow& rw) {
#define dict(x) dictionary[x]
#define component(w, c, i) w->getComponent<c>(i)
        wInve = new Window(dictionary.gui.window.inventory, sf::Vector2f(725, 470), sf::Vector2f(rw.getSize().x/2-362.5, rw.getSize().y/2-225));
            for (int i=0; i<8; i++)
                for (int j=0; j<4; j++)
                    wInve->addComponent(new Slot(sf::Vector2f(75, 75), sf::Vector2f(10+i*90, 30+j*90)), true);
            wInve->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
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

    void Inventory::buttonEvents(sf::RenderWindow& rw, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)
        if (wInve->isVisible()) {
            if (component(wInve, Button, 0)->isPressed(rw)){
                wInve->setVisible(false);
                g->pause(false);
            }
            for (int i=0; i<32; i++) {
                if (component(wInve, Slot, i)->isPressed(rw)) {

                }
            }
        }

#undef component

    }

    void Inventory::draw(sf::RenderWindow& rw) {
        wInve->draw(rw);
    }

    bool Inventory::isOpen() {
        return wInve->isVisible();
    }

}
