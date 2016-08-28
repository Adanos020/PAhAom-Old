/**
 * @file src/program/game/ui/BookOfSpells.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "BookOfSpells.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Slot.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    BookOfSpells::BookOfSpells() :
      wBofs_(Window(Resources::dictionary["gui.window.bookOfSpells"], sf::Vector2f(935, 650), (sf::Vector2f) Settings::graphics.resolution/2.f - sf::Vector2f(467.5f, 325)))
    {
        shadow_.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

        wBofs_ += new Image(sf::Vector2f(0, 0), Resources::texture.book_of_spells);

        for (int i=0; i<3; i++)
        {
            wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(175, 150+120*i));
            wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(295, 150+120*i));
            wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(560, 150+120*i));
            wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(680, 150+120*i));
        }
        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(wBofs_.getSize().x - bQuit->getSize().x - 15,
                                             wBofs_.getSize().y - bQuit->getSize().y -  5));

        wBofs_ += bQuit;
    }

    void BookOfSpells::buttonEvents(sf::RenderWindow& rw, sf::Event& ev, Game* g)
    {
        if (isOpen())
        {
            if (  wBofs_.getComponent<Button>(0)->isPressed(rw, ev)
                ) g->pause(false);

            for (int i=0; i<12; i++)
            {
                if (wBofs_.getComponent<Slot>(i)->isPressed(rw, ev))
                {

                }
            }
        }
    }

    void
    BookOfSpells::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(shadow_, states);
            target.draw(wBofs_ , states);
        }
    }

}
