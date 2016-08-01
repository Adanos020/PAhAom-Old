/**
 * @file src/program/game/ui/MainMenu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_MAINMENU_HPP
#define UI_MAINMENU_HPP

#include <SFML/Graphics.hpp>

#include "../../gui/Window.hpp"
#include "../../gui/Text.hpp"

namespace rr {

    class Game;

/// Class for the main menu
    class MainMenu : public sf::Drawable {
    private: Text    title_;
             Text    version_;
             Window  wMenu_;

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:  MainMenu();
         
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
    };

}

#include "../Game.hpp"

#endif // UI_MAINMENU_HPP
