/**
 * @file src/program/game/ui/PauseMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef UI_PAUSE_HPP
#define UI_PAUSE_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr
{

    class Game;

    class PauseMenu : public sf::Drawable
    {
    private: sf::RectangleShape m_shadow;
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
             PauseMenu();

             ////////////////////////////////////////////////////////////////////////
             /// Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// Opens the pause menu.
             ////////////////////////////////////////////////////////////////////////
             void open() { m_wMenu.setVisible(true); }

             ////////////////////////////////////////////////////////////////////////
             /// Closes the pause menu window.
             ////////////////////////////////////////////////////////////////////////
             void close();

             ////////////////////////////////////////////////////////////////////////
             /// Tells if the pause menu is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return m_wMenu.isVisible();}
    };

}

#include "../Game.hpp"

#endif // UI_PAUSE_HPP
