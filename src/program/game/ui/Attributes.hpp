/**
 * @file src/program/game/ui/Attributes.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"

namespace rr
{

    class Game;
    class Player;

    class Attributes : public sf::Drawable
    {
    private: sf::RectangleShape m_shadow;
             Window             m_wAttr;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Attributes();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the interface.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the info about the player attributes.
             ////////////////////////////////////////////////////////////////////////
             void update(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the player attributes window.
             ////////////////////////////////////////////////////////////////////////
             void open() { m_wAttr.setVisible(true); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the player attributes window.
             ////////////////////////////////////////////////////////////////////////
             void close() { m_wAttr.setVisible(false); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the player attributes window is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return m_wAttr.isVisible(); }
    };

}

#include "../../Game.hpp"

#include "../entity/Player.hpp"
