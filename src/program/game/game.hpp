/**
 * @file src/program/game/game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef game_h
#define game_h

#include <ctime>
#include <vector>

#include "item/item_Potion.hpp"
#include "menus/menus.hpp"
#include "player/player.hpp"
#include "../program.hpp"

namespace rr {

    class MainMenu;
    class PauseMenu;
    class Inventory;
    class Attributes;

/// Class for the HUD
    class HUD {
    private:
        Bar*  bHP;
        Bar*  bMP;
        Bar*  bXP;
        Slot* sCarryOn[5];
        Text* tXPlevel;
    public:
         HUD(sf::RenderWindow&);
        ~HUD();

        void buttonEvents(sf::RenderWindow&);
        void update      (Player*);
        void draw        (sf::RenderWindow&);
    };

/// Class for the game
    class Game {
    private:
        MainMenu*            mainMenu;
        PauseMenu*           pauseMenu;
        Attributes*          attributes;
        Inventory*           inventory;
        HUD*                 hud;
        Player*              player;
        std::vector<Potion*> potions;
        bool                 started;
        bool                 paused;

        void controls    (float);
    public:
         Game(sf::RenderWindow&);
        ~Game();

        void draw        (sf::RenderWindow&, sf::View&);
        void buttonEvents(sf::RenderWindow&, sf::View&);
        void update      (float, sf::View&);

        void start       (bool);
        void pause       (bool);
        void save        ();
        bool load        ();
        bool loadNewGame ();

        bool isStarted   ();
        bool isPaused    ();
    };

}

#endif // game_h
