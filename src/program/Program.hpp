/**
 * @file src/program/Program.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>

#include <map>

#include "Settings.hpp"
#include "Resources.hpp"
#include "game/Game.hpp"

namespace rr {

    class Game;

/// Class for the program
    class Program {
    private: sf::Event        event_;
             sf::RenderWindow window_;
         
             Game*            game_;
         
         /// Loads all the resources, settings and dictionary
             bool        loadResources();
         
         /// Runs the game
             void        runGame      ();
         
         /// Runs the game's main loop
             void        mainLoop     ();
         
         /// Handles the window events
             void        handleEvents ();
         
         /// Updates the game's state
             void        update       (sf::Clock&);
         
         /// Draws the game's components
             void        draw         ();
    
    public:  Program();
         
             Game*            getGame      () const { return game_; }
    };

}

#endif // PROGRAM_HPP
