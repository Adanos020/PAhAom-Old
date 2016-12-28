/**
 * @file src/program/game/ui/DeathScreen.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "DeathScreen.hpp"

#include "../../Resources.hpp"
#include "../../Settings.hpp"

namespace rr
{

    DeathScreen::DeathScreen() :
      m_visible(false)
    {
        reset();
    }

    void
    DeathScreen::reset()
    {
        m_tYouDied = Text(Resources::dictionary["gui.text.you_died"], Resources::font.FinalFantasy, 200, sf::Color(255, 0, 0, 0));
        m_bNewGame = Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.newgame"], 52);
        m_bQuit = Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 52);

        m_shadow.setSize((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition (sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(255, 0, 0, 0));

        m_tYouDied.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2 - m_tYouDied.getSize().x/2 - 2.5f,
                                            Settings::graphics.resolution.y/2 - m_tYouDied.getSize().y/0.5));

        m_bNewGame.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2 - (m_bNewGame.getSize().x + m_bQuit.getSize().x + 7.5f) / 2,
                                            Settings::graphics.resolution.y/2 + m_bNewGame.getSize().y * 0.25f));

        m_bQuit.setPosition(sf::Vector2f(m_bNewGame.getSize().x + 5, 0) + m_bNewGame.getPosition());

        m_endAnimation = sf::Time::Zero;
        m_tYouDied.setFillColor(sf::Color(255, 0, 0, 0));
        m_shadow  .setFillColor(sf::Color(255, 0, 0, 0));
    }

    void
    DeathScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_visible)
        {
            target.draw(m_shadow  , states);
            target.draw(m_tYouDied, states);
            target.draw(m_bNewGame, states);
            target.draw(m_bQuit   , states);
        }
    }

    void
    DeathScreen::buttonEvents(sf::RenderWindow& rw, sf::Event& event, Game* g)
    {
        if (m_visible)
        {
            if (m_bNewGame.isPressed(rw, event))
            {
                m_visible = false;

                auto generatingWorld = Text(Resources::dictionary["gui.text.generating_world"], Resources::font.Unifont);
                generatingWorld.setPosition((sf::Vector2f) Settings::graphics.resolution/2.f - generatingWorld.getSize()/2.f);

                auto currView = rw.getView();
                rw.setView(rw.getDefaultView());

                rw.clear();
                rw.draw(generatingWorld);
                rw.display();

                rw.setView(currView);
                    
                g->loadNewGame();
            }
            if (m_bQuit.isPressed(rw, event))
            {
                m_visible = false;
                reset();
                g->start(false);
            }
        }
    }

    void
    DeathScreen::update(sf::Time& time)
    {
        if (m_visible)
        {
            if (m_endAnimation.asSeconds() <= 1.f)
            {
                sf::Color shadow  = m_shadow  .getFillColor();
                sf::Color youdied = m_tYouDied.getFillColor();

                shadow .a = 140 * m_endAnimation.asSeconds();
                youdied.a = 255 * m_endAnimation.asSeconds();

                m_shadow  .setFillColor(shadow);
                m_tYouDied.setFillColor(youdied);

                m_endAnimation += time;
            }
        }
    }

}
