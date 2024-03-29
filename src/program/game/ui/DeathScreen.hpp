/**
 * @file src/program/game/ui/DeathScreen.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "../../gui/Text.hpp"
#include "../../gui/Button.hpp"

namespace rr
{

    class Game;

    class DeathScreen : public sf::Drawable
    {
    private: sf::RectangleShape m_shadow;
             sf::Time           m_endAnimation;

             Text               m_tYouDied;
             Button             m_bNewGame;
             Button             m_bQuit;

             bool               m_visible;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             DeathScreen();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the interface.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the screen of death.
             ////////////////////////////////////////////////////////////////////////
             void open() { m_visible = true; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the screen of death.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() { return m_visible; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the screen of death's state.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Time&);
    };

}

#include "../../Game.hpp"
