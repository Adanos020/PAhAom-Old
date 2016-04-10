/**
 * @file src/program/game/menus/menus.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
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

        void buttonEvents(sf::RenderWindow&, Game*);
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

        void open        ();
        void buttonEvents(sf::RenderWindow&, Game*);
        void draw        (sf::RenderWindow&);

        bool isOpen      ();
    };

/// Class for the player attributes window
    class Attributes {
    private:
        Window* wAttr;
    public:
         Attributes(sf::RenderWindow&);
        ~Attributes();

        void open        ();
        void update      (Player*);
        void buttonEvents(sf::RenderWindow&, Game*);
        void draw        (sf::RenderWindow&);

        bool isOpen      ();
    };

/// Class for the player inventory
    class Inventory {
    private:
        Window* wInve;
    public:
         Inventory(sf::RenderWindow&);
        ~Inventory();

        void open        ();
        void buttonEvents(sf::RenderWindow&, Game*);
        void draw        (sf::RenderWindow&);

        bool isOpen      ();
    };

}

#endif // menus_h
