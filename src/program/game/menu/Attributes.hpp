/**
 * @file src/program/game/menu/Attributes.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_ATTRIBUTES_HPP
#define MENU_ATTRIBUTES_HPP

#include <SFML/Graphics.hpp>

#include "../Game.hpp"

#include "../../gui/Window.hpp"

#include "../entity/Player.hpp"

namespace rr {

    class Game;

/// Class for the player attributes window
    class Attributes {
    private: sf::RectangleShape shadow_;
             Window             wAttr_;
    
    public:  Attributes();

         /// Opens the player attributes window
             void open        ();
         /// Closes the player attributes window
             void close       ();
         /// Updates the info about the player attributes
             void update      (Player*);
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the player attributes components
             void draw        (sf::RenderWindow&);
         /// Tells if the player attributes is open
             bool isOpen      ();
    };

}

#endif
