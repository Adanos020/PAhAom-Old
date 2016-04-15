/**
 * @file src/program/game/menus/menus_Quests.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

extern rr::Dictionary dictionary;
extern rr::Settings settings;
extern rr::Resources resources;

namespace rr {

    Quests::Quests(sf::RenderWindow& rw) {
        shadow.setSize((sf::Vector2f)rw.getSize());
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        wQues = new Window(dictionary.gui.window.quests, sf::Vector2f(725, 470), sf::Vector2f(rw.getSize().x/2-362.5, rw.getSize().y/2-225));
            wQues->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
            component(wQues, Button, 0)->setPosition(sf::Vector2f(wQues->getPosition().x+wQues->getSize().x-component(wQues, Button, 0)->getSize().x-15, rw.getSize().y/2+225-component(wQues, Button, 0)->getSize().y-5));

#undef component

    }

    Quests::~Quests() {
        delete wQues;
    }

    void Quests::open() {
        wQues->setVisible(true);
    }

    void Quests::close() {
        wQues->setVisible(false);
    }

    void Quests::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wQues->isVisible()) {
            if (component(wQues, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void Quests::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        wQues->draw(rw);
    }

    bool Quests::isOpen() {
        return wQues->isVisible();
    }

}
