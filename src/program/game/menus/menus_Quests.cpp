/**
 * @file src/program/game/menus/menus_Quests.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Quests::Quests() {
        _shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        _shadow.setPosition(sf::Vector2f(0, 0));
        _shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        _wQues = new Window(resources.dictionary["gui.window.quests"], sf::Vector2f(725, 470), sf::Vector2f(settings.graphics.resolution.x/2-362.5, settings.graphics.resolution.y/2-225));
            _wQues->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
            component(_wQues, Button, 0)->setPosition(sf::Vector2f(_wQues->getPosition().x+_wQues->getSize().x-component(_wQues, Button, 0)->getSize().x-15, settings.graphics.resolution.y/2+225-component(_wQues, Button, 0)->getSize().y-5));

#undef component

    }

    Quests::~Quests() {
        delete _wQues;
    }

    void Quests::open() {
        _wQues->setVisible(true);
    }

    void Quests::close() {
        _wQues->setVisible(false);
    }

    void Quests::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (_wQues->isVisible()) {
            if (component(_wQues, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void Quests::draw(sf::RenderWindow& rw) {
        rw.draw(_shadow);
        _wQues->draw(rw);
    }

    bool Quests::isOpen() {
        return _wQues->isVisible();
    }

}
