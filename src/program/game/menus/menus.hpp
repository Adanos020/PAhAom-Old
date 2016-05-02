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
#include "../entities/player/player.hpp"

namespace rr {

    class Game;

/// Class for the main menu
    class MainMenu {
    private:
        Text*   title;
        Window* wMenu;
    public:
         MainMenu();
        ~MainMenu();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

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
         PauseMenu();
        ~PauseMenu();

    /// Method opening the pause menu
        void open        ();

    /// Method closing the pause menu window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Method drawing the pause menu's components
        void draw        (sf::RenderWindow&);

    /// Method telling if the pause menu is open
        bool isOpen      ();
    };

/// Class for the player attributes window
    class Attributes {
    private:
        sf::RectangleShape shadow;
        Window* wAttr;
    public:
         Attributes();
        ~Attributes();

    /// Method opening the player attributes window
        void open        ();

    /// Method closing the player attributes window
        void close       ();

    /// Updates the info about the player attributes
        void update      (Player*);

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Method drawing the player attributes components
        void draw        (sf::RenderWindow&);

    /// Method telling if the player attributes is open
        bool isOpen      ();
    };

/// Class for the player inventory
    class Inventory {
    private:
        sf::RectangleShape shadow;
        Window* wInve;
    public:
         Inventory();
        ~Inventory();

    /// Method opening the inventory window
        void open        ();

    /// Method closing the inventory window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Method drawing the inventory components
        void draw        (sf::RenderWindow&);

    /// Method telling if the inventory is open
        bool isOpen      ();
    };

/// Class for the task list
    class Quests {
    private:
        sf::RectangleShape shadow;
        Window* wQues;
    public:
         Quests();
        ~Quests();

    /// Method opening the task list window
        void open        ();

    /// Method closing the task list window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Method drawing the task list components
        void draw        (sf::RenderWindow&);

    /// Method telling if the task list is open
        bool isOpen      ();
    };

/// Class for the game map
    class GameMap {
    private:
        sf::RectangleShape shadow;
        Window* wGmap;
    public:
         GameMap();
        ~GameMap();

    /// Method opening the game map window
        void open        ();

    /// Method closing the game map window
        void close       ();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Method drawing the game map components
        void draw        (sf::RenderWindow&);

    /// Method telling if the game map is open
        bool isOpen      ();
    };

}

#endif // menus_h
