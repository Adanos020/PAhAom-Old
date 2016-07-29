/**
 * @file src/program/game/menu/PauseMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_PAUSE_HPP
#define MENU_PAUSE_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr {

    class Game;

/// Class for the pause menu
    class PauseMenu {
    private: sf::RectangleShape shadow_;
             Text               title_;
             Text               version_;
             Window             wMenu_;
    
    public:  PauseMenu();
         
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the pause menu's components
             void draw        (sf::RenderWindow&);
         /// Opens the pause menu
             void open        ()       { wMenu_.setVisible(true); }
         /// Closes the pause menu window
             void close       ();
         /// Tells if the pause menu is open
             bool isOpen      () const { return wMenu_.isVisible();}
    };

}

#include "../Game.hpp"

#endif // MENU_PAUSE_HPP
