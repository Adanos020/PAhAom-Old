/**
 * @file src/program/program.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
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

    /// Structure for the fonts
        struct {
        public:
            sf::Font Unifont;
            sf::Font Pixel;
        } font;

    /// Structure for the textures
        struct {
        public:
            sf::Texture gui;
            sf::Texture player;
            sf::Texture items;
            sf::Texture tileset;
            sf::Texture keyboard;
        } texture;

    /// Method loading the resources
        bool load();
    };

/// Structure for the dictionary
    struct Dictionary {
    public:
    /// Structure for the gui part of the dictionary
        struct {
        public:

    /// Structure for the button part of the gui dictionary
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

    /// Structure for the checkbox part of the gui dictionary
            struct {
            public:
                sf::String fullscreen;
                sf::String vsync;
            } checkbox;

    /// Structure for the text part of the gui dictionary
            struct {
            public:
                sf::String resolution;
                sf::String language;
                sf::String killurslf;
                sf::String wholegame;
                sf::String usedlib;
                sf::String music;
                sf::String effects;
                sf::String mute;
            } text;

    /// Structure for the button part of the gui dictionary
            struct {
            public:
                sf::String attributes;
                sf::String inventory;
            } window;
        } gui;

    /// Structure for the item part of the dictionary
        struct {
        public:

    /// Structure for the potion part of the item dictionary
            struct {

        /// Structure for the size part of the potion dictionary
            public:
                sf::String potion;
                struct {
                public:
                    sf::String small;
                    sf::String medium;
                    sf::String big;
                } size;

        /// Structure for the color part of the potion dictionary
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

        /// Structure for the effect part of the potion dictionary
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

    /// Structure for the player part of the dictionary
        struct {
        public:

        /// Structure for player attributes
            struct {
                sf::String health;
                sf::String strength;
                sf::String dexterity;
                sf::String experience;
                sf::String level;
                sf::String skill_points;
            } attributes;

        /// Structure for player skills
            struct {
                sf::String crafting;
                sf::String alchemy;
                sf::String cold_weapon_mastery;
                sf::String ranged_weapon_mastery;
                sf::String better_sight;
            } skills;

        } player;

    /// Method loading the dictionary
        bool load();
    };

/// Structure for the game settings
    struct Settings {
    public:
    /// Structure for the key bindings
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

    /// Structure for the sound settings
        struct {
            float music_volume;
            float effects_volume;
            bool  music_muted;
            bool  effects_muted;
        } sound;

    /// Structure for the video settings
        struct {
            sf::ContextSettings csettings;
            sf::Vector2u        resolution;
            bool                vsync;
            bool                fullscreen;
        } graphics;

    /// Structure for the game settings
        struct {
            std::string language;
        } game;

    /// Method printing the actual settings
        void print();

    /// Method overwriting the actual settings
        void save ();

    /// Method loading the actual settings
        bool load ();
    };


/// Class for the program
    class Program {
    private:
        sf::Event        event;
        sf::RenderWindow window;
        sf::View         view;

        Game*            game;


    /// Method loading all the resources, settings and dictionary
        bool loadResources ();

    /// Method running the game
        void runGame       ();

    /// Method running the game's main loop
        void mainLoop      ();

    /// Method for handling the window events
        void handleEvents  ();

    /// Updates the game's state
        void update        (sf::Clock&);

    /// Method drawing the game's component
        void draw          ();
    public:
         Program();
        ~Program();
    };

}

#endif // program_h
