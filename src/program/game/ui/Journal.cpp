/**
 * @file src/program/game/ui/Journal.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Journal.hpp"

#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    Journal::Journal() :
      m_wJour(Window(Resources::dictionary["gui.window.journal"], sf::Vector2f(725, 470), sf::Vector2f(Settings::graphics.resolution.x/2-362.5,
                                                                                                       Settings::graphics.resolution.y/2-225)))
    {
        m_shadow.setSize((sf::Vector2f)Settings::graphics.resolution);
        m_shadow.setPosition(sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 128));

        

        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(m_wJour.getSize().x - bQuit->getSize().x - 15,
                                             m_wJour.getSize().y - bQuit->getSize().y -  5));

        m_wJour += bQuit;
    }

    void
    Journal::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        if (m_wJour.isVisible())
        {
            if (m_wJour.getComponent <Button> (0)->isPressed(rw, e))
                g->pause(false);
        }
    }

    void
    Journal::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(m_shadow, states);
            target.draw(m_wJour , states);
        }
    }

}
