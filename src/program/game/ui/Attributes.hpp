/**
 * @file src/program/game/ui/Attributes.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_ATTRIBUTES_HPP
#define UI_ATTRIBUTES_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"

#include "../entity/Player.hpp"

namespace rr {

    class Game;

/// Class for the player attributes window
    class Attributes : public sf::Drawable {
    private: sf::RectangleShape shadow_;
             Window             wAttr_;

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:  Attributes();

         /// Updates the info about the player attributes
             void update      (Player*);
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Opens the player attributes window
             void open        ()       { wAttr_.setVisible(true); }
         /// Closes the player attributes window
             void close       ()       { wAttr_.setVisible(false); }
         /// Tells if the player attributes is open
             bool isOpen      () const { return wAttr_.isVisible(); }
    };

}

#include "../Game.hpp"

#endif // UI_ATTRIBUTES_HPP
