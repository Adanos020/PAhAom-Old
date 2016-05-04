/**
 * @file src/program/game/game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
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
        sf::View            _gameView;
        sf::View            _mapView;

        MainMenu*           _mainMenu;
        PauseMenu*          _pauseMenu;
        Attributes*         _attributes;
        Inventory*          _inventory;
        Quests*             _quests;
        GameMap*            _gameMap;
        HUD*                _hud;
        std::vector<Level*> _level;
        Player*             _player;

        bool                _started;
        bool                _paused;
        unsigned            _levelNumber;

    /// Method for the keyboard controls
        void controls      ();

    /// Method randomizing the disposable items' colors/symbols
        void randomizeItems();
    public:
         Game();
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

/// Class for the HUD
    class HUD {
    private:
        Bar*  _bHP;
        Bar*  _bMP;
        Bar*  _bXP;
        Slot* _sCarryOn[5];
        Text* _tXPlevel;
    public:
         HUD();
        ~HUD();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Updates the HUD state
        void update      (Player*);

    /// Method drawing the HUD components
        void draw        (sf::RenderWindow&);
    };

}

#endif // game_h
