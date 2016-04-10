/**
 * @file src/program/program.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef program_h
#define program_h

#include <SFML/Graphics.hpp>

#include "game/game.hpp"

namespace rr {

    class Game;

/// Structure for the resources
    struct Resources {
    public:
        struct {
        public:
            sf::Font Unifont;
            sf::Font Pixel;
        } font;
        struct {
        public:
            sf::Texture gui;
            sf::Texture player;
            sf::Texture items;
        } texture;

        bool load();
    };

/// Structure for the dictionary
    struct Dictionary {
    public:
        struct {
        public:
            struct {
            public:
                sf::String newgame;
                sf::String resume;
                sf::String save;
                sf::String load;
                sf::String options;
                sf::String help;
                sf::String credits;
                sf::String quit;
                sf::String game;
                sf::String graphical;
                sf::String sound;
                sf::String controls;
            } button;
            struct {
            public:
                sf::String fullscreen;
                sf::String vsync;
            } checkbox;
            struct {
            public:
                sf::String resolution;
                sf::String language;
                sf::String killurslf;
                sf::String wholegame;
                sf::String usedlib;
            } text;
            struct {
            public:
                sf::String attributes;
                sf::String inventory;
            } window;
        } gui;
        struct {
        public:
            struct {
            public:
                sf::String potion;
                struct {
                public:
                    sf::String small;
                    sf::String medium;
                    sf::String big;
                } size;
                struct {
                public:
                    sf::String red;
                    sf::String blue;
                    sf::String brown;
                    sf::String green;
                    sf::String gray;
                    sf::String pink;
                    sf::String purple;
                    sf::String black;
                    sf::String white;
                } color;
                struct {
                public:
                    sf::String healing;
                    sf::String magic;
                    sf::String strength;
                    sf::String dexterity;
                    sf::String speed;
                    sf::String poison;
                    sf::String regeneration;
                    sf::String slowness;
                    sf::String weakness;
                } effect;
            } potion;
        } item;

        bool load();
    };

/// Structure for the game settings
    struct Settings {
    public:/// Structure for the key bindings
        struct {
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
        }                   keys;
        sf::ContextSettings csettings;
        sf::Vector2u        resolution;
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
