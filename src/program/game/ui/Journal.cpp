/**
 * @file src/program/game/ui/Journal.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Journal.hpp"

#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr {

    Journal::Journal() :
      wJour_ (Window(Resources::dictionary["gui.window.journal"], sf::Vector2f(725, 470),
              sf::Vector2f(Settings::graphics.resolution.x/2-362.5, Settings::graphics.resolution.y/2-225)))
    {
        shadow_.setSize((sf::Vector2f)Settings::graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w.getComponent<c>(i)

            wJour_.addComponent(new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30), true);
            component(wJour_, Button, 0)->setPosition(sf::Vector2f(wJour_.getPosition().x + wJour_.getSize().x - component(wJour_, Button, 0)->getSize().x-15,
                                                                   Settings::graphics.resolution.y/2+225       - component(wJour_, Button, 0)->getSize().y-5));

    }

    void Journal::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {
        if (wJour_.isVisible()) {
            if (  component(wJour_, Button, 0)->isPressed(rw, e)
                ) g->pause(false);
        }

#undef component

    }

    void Journal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (isOpen()) {
            target.draw(shadow_, states);
            target.draw(wJour_ , states);
        }
    }

}
