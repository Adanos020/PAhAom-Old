/**
 * @file src/program/game/menus/menus.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef menus_h
#define menus_h

#include "../../gui/gui.hpp"
#include "../game.hpp"
#include "../player/player.hpp"

namespace rr {

    class Game;

/// Class for the main menu
    class MainMenu {
    private:
        Text*   title;
        Window* wMenu;
    public:
         MainMenu(sf::RenderWindow&);
        ~MainMenu();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, Game*);

    /// Method drawing the main menu's components
        void draw        (sf::RenderWindow&);
    };

/// Class for the pause menu
    class PauseMenu {
    private:
        sf::RectangleShape shadow;
        Text*              title;
        Window*            wMenu;
    public:
         PauseMenu(sf::RenderWindow&);
        ~PauseMenu();

    /// Method opening the pause menu
        void open        ();

    /// Method closing the pause menu window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, Game*);

    /// Method drawing the pause menu's components
        void draw        (sf::RenderWindow&);

    /// Method telling if the pause menu is open
        bool isOpen      ();
    };

/// Class for the player attributes window
    class Attributes {
    private:
        Window* wAttr;
    public:
         Attributes(sf::RenderWindow&);
        ~Attributes();

    /// Method opening the player attributes window
        void open        ();

    /// Method closing the player attributes window
        void close       ();

    /// Updates the info about the player attributes
        void update      (Player*);

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, Game*);

    /// Method drawing the player attributes components
        void draw        (sf::RenderWindow&);

    /// Method telling if the player attributes is open
        bool isOpen      ();
    };

/// Class for the player inventory
    class Inventory {
    private:
        Window* wInve;
    public:
         Inventory(sf::RenderWindow&);
        ~Inventory();

    /// Method opening the inventory window
        void open        ();

    /// Method closing the inventory window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, Game*);

    /// Method drawing the inventory components
        void draw        (sf::RenderWindow&);

    /// Method telling if the inventory is open
        bool isOpen      ();
    };

}

#endif // menus_h
