/**
 * @file src/program/game/menu/BookOfSpells.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_BOOKOFSPELLS_HPP
#define MENU_BOOKOFSPELLS_HPP

#include <SFML/Graphics.hpp>

#include "../Game.hpp"

#include "../../gui/Window.hpp"

namespace rr {

    class Game;

/// Class for the book of Runes
    class BookOfSpells {
    private: sf::RectangleShape shadow_;
             Window             wBofs_;
   
    public:  BookOfSpells();
         
         /// Opens the window of the book of Runes
             void open        ();
         /// Closes the window of the book of Runes
             void close       ();
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the components of the window of the book of Runes
             void draw        (sf::RenderWindow&);
         /// Tells if the window of the book of Runes is open
             bool isOpen      ();
    };

}

#endif
