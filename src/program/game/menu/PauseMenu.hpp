/**
 * @file src/program/game/menu/PauseMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_PAUSE_HPP
#define MENU_PAUSE_HPP

#include <SFML/Graphics.hpp>

#include "../Game.hpp"

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr {

    class Game;

/// Class for the pause menu
    class PauseMenu {
    private: sf::RectangleShape shadow_;
             Text               title_;
             Window             wMenu_;
    
    public:  PauseMenu();
            ~PauseMenu();
         
         /// Opens the pause menu
             void open        ();
         /// Closes the pause menu window
             void close       ();
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the pause menu's components
             void draw        (sf::RenderWindow&);
         /// Tells if the pause menu is open
             bool isOpen      ();
    };

}

#endif
