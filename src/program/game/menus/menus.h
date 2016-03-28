/**
 * @file src/program/game/menus/menus.h
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef menus_h
#define menus_h

#include "../../gui/gui.h"
#include "../game.h"
#include "../../program.h"


namespace rr {

    class Game;

    /// Class for the main menu
    class MainMenu {
      private:
        Text* title;
        Window* wMenu;
        Window* wOpts;
        Window* wHelp;
        Window* wCred;
      public:
        MainMenu(sf::RenderWindow&);
        ~MainMenu();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

    /// Class for the pause menu
    class PauseMenu {
      private:
        Text* title;
        Window* wMenu;
        Window* wOpts;
        Window* wHelp;
      public:
        PauseMenu(sf::RenderWindow&);
        ~PauseMenu();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

    /// Class for the player statistics window
    class Statistics {
      private:
        Window* wStats;
      public:
        Statistics(sf::RenderWindow&);
        ~Statistics();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

    /// Class for the player attributes window
    class Attributes {
      private:
        Window* wAttr;
      public:
        Attributes(sf::RenderWindow&);
        ~Attributes();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

}

#endif // menus_h
