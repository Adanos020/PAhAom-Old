/**
 * @file src/program/game/Game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "menu/ALL.hpp"
#include "entity/ALL.hpp"
#include "Level.hpp"
#include "HUD.hpp"
#include "../messages/MessageManager.hpp"

namespace rr {

    class MainMenu;
    class PauseMenu;
    class Attributes;
    class Inventory;
    class Journal;
    class BookOfSpells;
    class HUD;

    class Level;
    class FOV;
    class MessageManager;

    class Player;

    class Bar;
    class Slot;
    class Text;

/// Class for the game
    class Game {
    private: sf::View            gameView_;
             sf::View            mapView_;
             
             Level*              currentLevel_;
         
             MessageManager      messageManager_;
         
             Player              player_;
         
             MainMenu            mainMenu_;
             PauseMenu           pauseMenu_;
             Attributes          attributes_;
             Inventory           inventory_;
             Journal             journal_;
             BookOfSpells        bookOfSpells_;
             HUD                 hud_;
         
             bool                started_;
             bool                paused_;
             bool                mapOpen_;
             unsigned            levelNumber_;
             unsigned            seed_;
         
         /// Keyboard controls
             void controls      (sf::Event&);
         /// Randomizes the disposable items' colors/symbols
             void randomizeItems();
         /// Switches to the level of a given index
             void switchLevel   (int index);
    
    public:  Game();
            ~Game();
        
         /// Method drawing the game components
             void                draw           (sf::RenderWindow&);
         /// Method for handling the button events
             void                buttonEvents   (sf::RenderWindow&, sf::Event&);
         /// Method drawing the game components
             void                update         (sf::Event&       , sf::Time);
         /// Method starting the game or not, depending on the argument's value
             void                start          (bool);
         /// Method pause the game or not, depending on the argument's value
             void                pause          (bool);
         /// Method saving the game progress
             void                save           ();
         /// Method loading the game progress
             bool                load           ();
         /// Method the new game
             bool                loadNewGame    ();
         /// Method telling if the game is started
             bool                isStarted      () { return started_; }
         /// Method telling if the game is paused
             bool                isPaused       () { return paused_; }
         /// Returns the pointer to the player
             Player*             getPlayer      () { return &player_; }
         /// Returns the vector of game levels
             Level*              getCurrentLevel() { return currentLevel_; }
         /// Resets the game state
             void                reset          ();
    };

}

#endif // GAME_HPP
