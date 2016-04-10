/**
 * @file src/program/program.h
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef program_h
#define program_h

#include <SFML/Graphics.hpp>

#include "game/game.h"

namespace rr {

    class Game;

/// Structure for the key bindings
    struct KeyBindings {
    public:
        sf::Keyboard::Key move_up;
        sf::Keyboard::Key move_down;
        sf::Keyboard::Key move_left;
        sf::Keyboard::Key move_right;

        sf::Keyboard::Key interact;
        sf::Keyboard::Key attack;
        sf::Keyboard::Key pickup;

        sf::Keyboard::Key open_inventory;
        sf::Keyboard::Key open_attributes;
        sf::Keyboard::Key open_quests;
        sf::Keyboard::Key open_map;

        sf::Keyboard::Key useslot_1;
        sf::Keyboard::Key useslot_2;
        sf::Keyboard::Key useslot_3;
        sf::Keyboard::Key useslot_4;
        sf::Keyboard::Key useslot_5;
    };

/// Structure for the game settings
    struct Settings {
    public:
        sf::ContextSettings csettings;
        sf::Vector2u        resolution;
        KeyBindings         keys;
        bool                vsync;
        bool                fullscreen;
        std::string         language;

        void print();
        void save ();
        bool load ();
    };


/// Class for the program
    class Program {
    private:
        sf::Event        event;
        sf::RenderWindow window;
        sf::View         view;

        Game*            game;

        bool readDictionary();
        bool loadResources ();
        void runGame       ();
        void mainLoop      ();
        void handleEvents  ();
        void update        (sf::Clock&);
        void draw          ();
    public:
         Program();
        ~Program();
    };

}

#endif // program_h
