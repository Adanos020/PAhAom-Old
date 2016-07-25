/**
 * @file src/program/game/menu/Journal.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Journal.hpp"

#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Journal::Journal()
    :
      wJour_ (Window(resources.dictionary["gui.window.journal"], sf::Vector2f(725, 470),
              sf::Vector2f(settings.graphics.resolution.x/2-362.5, settings.graphics.resolution.y/2-225))) {

        shadow_.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w.getComponent<c>(i)

            wJour_.addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
            component(wJour_, Button, 0)->setPosition(sf::Vector2f(wJour_.getPosition().x+wJour_.getSize().x - component(wJour_, Button, 0)->getSize().x-15,
                                                                   settings.graphics.resolution.y/2+225      - component(wJour_, Button, 0)->getSize().y-5));

#undef component

    }

    Journal::~Journal() {}

    void Journal::open() {
        wJour_.setVisible(true);
    }

    void Journal::close() {
        wJour_.setVisible(false);
    }

    void Journal::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w.getComponent<c>(i)

        if (wJour_.isVisible()) {
            if (  component(wJour_, Button, 0)->isPressed(rw, e)
                ) g->pause(false);
        }

#undef component

    }

    void Journal::draw(sf::RenderWindow& rw) {
        if (isOpen()) {
            rw.draw(shadow_);
            wJour_.draw(rw);
        }
    }

    bool Journal::isOpen() {
        return wJour_.isVisible();
    }

}
