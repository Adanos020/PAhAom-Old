/**
 * @file src/program/game/menu/BookOfSpells.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "BookOfSpells.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Slot.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr {

    BookOfSpells::BookOfSpells() :
      wBofs_(Window(Resources::dictionary["gui.window.bookOfSpells"], sf::Vector2f(765, 470), (sf::Vector2f) Settings::graphics.resolution/2.f - sf::Vector2f(382.5f, 235)))
    {

#define component(w, c, i) w.getComponent<c>(i)

        shadow_.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

            for (int i=0; i<3; i++) {
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(145, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(245, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(450, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(550, 100+100*i));
            }
            wBofs_+= new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                component(wBofs_, Button, 0)->setPosition(sf::Vector2f(wBofs_.getPosition().x+wBofs_.getSize().x - component(wBofs_, Button, 0)->getSize().x-15,
                                                          	           Settings::graphics.resolution.y/2+235      - component(wBofs_, Button, 0)->getSize().y-5));
    }

    void BookOfSpells::buttonEvents(sf::RenderWindow& rw, sf::Event& ev, Game* g) {
        if (isOpen()) {
            if (  component(wBofs_, Button, 0)->isPressed(rw, ev)
                ) g->pause(false);

            for (int i=0; i<12; i++) {
                if (component(wBofs_, Slot, i)->isPressed(rw, ev)) {

                }
            }
        }

#undef component

    }

    void BookOfSpells::draw(sf::RenderWindow& rw) {
        if (isOpen()) {
            rw.draw(shadow_);
            wBofs_.draw(rw);
        }
    }

}
