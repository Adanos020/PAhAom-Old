/**
 * @file src/program/game/game.h
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef game_h
#define game_h

#include <ctime>
#include "menus/menus.h"
#include "player/player.h"
#include "../program.h"

namespace rr {

    class MainMenu;
    class PauseMenu;

    /// Class for the HUD
    class HUD {
      private:
        Bar* bHP;
        Bar* bMP;
        Bar* bXP;
        Slot* sCarryOn[5];
        Text* tXPlevel;
      public:
        HUD(sf::RenderWindow&);
        ~HUD();

        void update(Player*);
        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

    /// Class for the game
    class Game {
      private:
        MainMenu* mainMenu;
        PauseMenu* pauseMenu;
        HUD* hud;
        Player* player;

        bool started;
        bool paused;
        void controls(float);
      public:
        Game(sf::RenderWindow&);
        ~Game();

        void draw(sf::RenderWindow&, sf::View&);
        void buttonEvents(sf::RenderWindow&, sf::View&);
        void update(float);

        void start(bool);
        void pause(bool);
        void save();
        bool load();
        bool loadNewGame();

        bool isStarted();
        bool isPaused();
    };

}

#endif // game_h
