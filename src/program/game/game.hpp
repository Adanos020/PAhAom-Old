/**
 * @file src/program/game/game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef game_hpp
#define game_hpp

#include <ctime>
#include <vector>

#include "menus/menus.hpp"
#include "entities/entities.hpp"

namespace rr {

    class MainMenu;
    class PauseMenu;
    class Inventory;
    class Attributes;
    class Quests;
    class GameMap;
    class HUD;
    class Level;

/// Class for the game
    class Game {
    private:
        sf::View            gameView_;
        sf::View            mapView_;

        MainMenu*           mainMenu_;
        PauseMenu*          pauseMenu_;
        Attributes*         attributes_;
        Inventory*          inventory_;
        Quests*             quests_;
        GameMap*            gameMap_;
        HUD*                hud_;
        std::vector<Level*> level_;
        Player*             player_;

        bool                started_;
        bool                paused_;
        unsigned            levelNumber_;

    /// Method for the keyboard controls
        void controls      ();

    /// Method randomizing the disposable items' colors/symbols
        void randomizeItems();
    public:
         Game();
        ~Game();

    /// Method drawing the game components
        void    draw        (sf::RenderWindow&);

    /// Method for handling the button events
        void    buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Method drawing the game components
        void    update      (float);

    /// Method starting the game or not, depending on the argument's value
        void    start       (bool);

    /// Method pause the game or not, depending on the argument's value
        void    pause       (bool);

    /// Method saving the game progress
        void    save        ();

    /// Method loading the game progress
        bool    load        ();

    /// Method the new game
        bool    loadNewGame ();

    /// Method telling if the game is started
        bool    isStarted   () { return started_; }

    /// Method telling if the game is paused
        bool    isPaused    () { return paused_; }

    /// Returns the pointer to the player
        Player* getPlayer   () { return player_; }

    /// Resets the game state
        void    reset       ();
    };

/// Class for the HUD
    class HUD {
    private:
        Bar*  bHP_;
        Bar*  bMP_;
        Bar*  bXP_;
        Slot* sCarryOn_[5];
        Text* tXPlevel_;
        Text* tLevelNumber;
    public:
         HUD();
        ~HUD();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Updates the HUD state
        void update      (Player*, int lvl);

    /// Method drawing the HUD components
        void draw        (sf::RenderWindow&);
    };

}

#endif // game_h
