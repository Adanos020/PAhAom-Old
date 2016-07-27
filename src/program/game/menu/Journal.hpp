/**
 * @file src/program/game/menu/Journal.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */
 
#ifndef MENU_JOURNAL_HPP
#define MENU_JOURNAL_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"

namespace rr {

    class Game;

/// Class for the task list
    class Journal {
    private: sf::RectangleShape shadow_;
             Window             wJour_;
    
    public:  Journal();
        
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Opens the task list window
             void open        ()       { wJour_.setVisible(true); }
         /// Closes the task list window
             void close       ()       { wJour_.setVisible(false); }
         /// Draws the task list components
             void draw        (sf::RenderWindow&);
         /// Tells if the task list is open
             bool isOpen      () const { return wJour_.isVisible(); }
    };

}

#include "../Game.hpp"

#endif
