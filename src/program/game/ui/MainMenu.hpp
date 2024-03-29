/**
 * @file src/program/game/ui/MainMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr
{

    class Game;

    class MainMenu : public sf::Drawable
    {
    private: sf::RectangleShape m_background;
             sf::Texture        m_backTexture;
             Text               m_title;
             Text               m_version;
             Window             m_wMenu;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             MainMenu();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the interface.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
    };

}

#include "../../Game.hpp"
