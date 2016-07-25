/**
 * @file src/program/game/menu/Journal.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */
 
#ifndef MENU_JOURNAL_HPP
#define MENU_JOURNAL_HPP

#include <SFML/Graphics.hpp>

#include "../Game.hpp"

#include "../../gui/Window.hpp"

namespace rr {

    class Game;

/// Class for the task list
    class Journal {
    private: sf::RectangleShape shadow_;
             Window             wJour_;
    
    public:  Journal();
            ~Journal();
        
         /// Opens the task list window
             void open        ();
         /// Closes the task list window
             void close       ();
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the task list components
             void draw        (sf::RenderWindow&);
         /// Tells if the task list is open
             bool isOpen      ();
    };

}

#endif
