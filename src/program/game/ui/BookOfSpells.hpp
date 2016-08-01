/**
 * @file src/program/game/ui/BookOfSpells.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_BOOKOFSPELLS_HPP
#define UI_BOOKOFSPELLS_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"

namespace rr {

    class Game;

/// Class for the book of Runes
    class BookOfSpells : public sf::Drawable {
    private: sf::RectangleShape shadow_;
             Window             wBofs_;

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
    public:  BookOfSpells();
         
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Opens the window of the book of Runes
             void open        ()       { wBofs_.setVisible(true); }
         /// Closes the window of the book of Runes
             void close       ()       { wBofs_.setVisible(false); }
         /// Tells if the window of the book of Runes is open
             bool isOpen      () const { return wBofs_.isVisible(); }
    };

}

#include "../Game.hpp"

#endif // UI_BOOKOFSPELLS_HPP
