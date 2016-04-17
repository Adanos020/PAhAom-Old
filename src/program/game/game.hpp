/**
 * @file src/program/game/game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
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
    class Quests;
    class GameMap;

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

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Updates the HUD state
        void update      (Player*);

    /// Method drawing the HUD components
        void draw        (sf::RenderWindow&);
    };

/// Class for the game
    class Game {
    private:
        sf::View             gameView;
        sf::View             mapView;

        MainMenu*            mainMenu;
        PauseMenu*           pauseMenu;
        Attributes*          attributes;
        Inventory*           inventory;
        Quests*              quests;
        GameMap*             gameMap;
        HUD*                 hud;
        Player*              player;
        std::vector<Item*>   items;

        bool                 started;
        bool                 paused;

        void controls    (float);
    public:
         Game(sf::RenderWindow&);
        ~Game();

    /// Method drawing the game components
        void draw        (sf::RenderWindow&);

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Method drawing the game components
        void update      (float);

    /// Method starting the game or not, depending on the argument's value
        void start       (bool);

    /// Method pause the game or not, depending on the argument's value
        void pause       (bool);

    /// Method saving the game progress
        void save        ();

    /// Method loading the game progress
        bool load        ();

    /// Method the new game
        bool loadNewGame ();

    /// Method telling if the game is started
        bool isStarted   ();

    /// Method telling if the game is paused
        bool isPaused    ();
    };

}

#endif // game_h
