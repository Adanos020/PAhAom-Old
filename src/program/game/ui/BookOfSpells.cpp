/**
 * @file src/program/game/ui/BookOfSpells.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "BookOfSpells.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Slot.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    BookOfSpells::BookOfSpells() :
      m_wBofs(Window(Resources::dictionary["gui.window.bookOfSpells"], sf::Vector2f(935, 650), (sf::Vector2f) Settings::graphics.resolution/2.f - sf::Vector2f(467.5f, 325)))
    {
        m_shadow.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition (sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 172));

        m_wBofs += new Image(sf::Vector2f(0, 0), Resources::texture.book_of_spells);

        for (int i = 0; i < 3; i++)
        {
            m_wBofs += new Slot(sf::Vector2f(80, 80), sf::Vector2f(175, 150+120*i));
            m_wBofs += new Slot(sf::Vector2f(80, 80), sf::Vector2f(295, 150+120*i));
            m_wBofs += new Slot(sf::Vector2f(80, 80), sf::Vector2f(560, 150+120*i));
            m_wBofs += new Slot(sf::Vector2f(80, 80), sf::Vector2f(680, 150+120*i));
        }
        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(m_wBofs.getSize().x - bQuit->getSize().x - 15,
                                             m_wBofs.getSize().y - bQuit->getSize().y -  5));

        m_wBofs += bQuit;
    }

    void BookOfSpells::buttonEvents(sf::RenderWindow& rw, sf::Event& ev, Game* g)
    {
        if (isOpen())
        {
            if (m_wBofs.getComponent <Button> (0)->isPressed(rw, ev))
                g->pause(false);

            for (int i = 0; i < 12; i++)
            {
                if (m_wBofs.getComponent <Slot> (i)->isPressed(rw, ev))
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
            target.draw(m_shadow, states);
            target.draw(m_wBofs , states);
        }
    }

}
