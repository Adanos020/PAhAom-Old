/**
 * @file src/program/game/menu/MainMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_MAINMENU_HPP
#define MENU_MAINMENU_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr {

    class Game;

/// Class for the main menu
    class MainMenu {
    private: Text    title_;
             Window  wMenu_;
    
    public:  MainMenu();
         
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the main menu's components
             void draw        (sf::RenderWindow&);
    };

}

#include "../Game.hpp"

#endif
