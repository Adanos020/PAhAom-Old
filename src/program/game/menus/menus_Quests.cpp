/**
 * @file src/program/game/menus/menus_Quests.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Quests::Quests() {
        shadow_.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        wQues_ = new Window(resources.dictionary["gui.window.quests"], sf::Vector2f(725, 470), sf::Vector2f(settings.graphics.resolution.x/2-362.5, settings.graphics.resolution.y/2-225));
            wQues_->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
            component(wQues_, Button, 0)->setPosition(sf::Vector2f(wQues_->getPosition().x+wQues_->getSize().x-component(wQues_, Button, 0)->getSize().x-15, settings.graphics.resolution.y/2+225-component(wQues_, Button, 0)->getSize().y-5));

#undef component

    }

    Quests::~Quests() {
        delete wQues_;
    }

    void Quests::open() {
        wQues_->setVisible(true);
    }

    void Quests::close() {
        wQues_->setVisible(false);
    }

    void Quests::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wQues_->isVisible()) {
            if (component(wQues_, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void Quests::draw(sf::RenderWindow& rw) {
        rw.draw(shadow_);
        wQues_->draw(rw);
    }

    bool Quests::isOpen() {
        return wQues_->isVisible();
    }

}
