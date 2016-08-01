/**
 * @file src/program/game/ui/PauseMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_PAUSE_HPP
#define UI_PAUSE_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr {

    class Game;

/// Class for the pause menu
    class PauseMenu : public sf::Drawable {
    private: sf::RectangleShape shadow_;
             Text               title_;
             Text               version_;
             Window             wMenu_;

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:  PauseMenu();
         
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Opens the pause menu
             void open        ()       { wMenu_.setVisible(true); }
         /// Closes the pause menu window
             void close       ();
         /// Tells if the pause menu is open
             bool isOpen      () const { return wMenu_.isVisible();}
    };

}

#include "../Game.hpp"

#endif // UI_PAUSE_HPP
