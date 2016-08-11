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

    class BookOfSpells : public sf::Drawable {
    private: sf::RectangleShape shadow_;
             Window             wBofs_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             BookOfSpells();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the window of the book of Runes.
             ////////////////////////////////////////////////////////////////////////
             void open() { wBofs_.setVisible(true); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the window of the book of Runes.
             ////////////////////////////////////////////////////////////////////////
             void close() { wBofs_.setVisible(false); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the window of the book of Runes is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return wBofs_.isVisible(); }
    };

}

#include "../Game.hpp"

#endif // UI_BOOKOFSPELLS_HPP
