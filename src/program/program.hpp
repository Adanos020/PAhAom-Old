/**
 * @file src/program/program.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef program_hpp
#define program_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

#include "game/game.hpp"

namespace rr {

    class Game;

/// Structure for the resources
    struct Resources {
    public: struct {
            public: sf::Font Unifont;
                    sf::Font Pixel;
            } font;
        
            struct {
            public: sf::Texture gui;
                    sf::Texture player;
                    sf::Texture items;
                    sf::Texture tileset;
                    sf::Texture objects;
                    sf::Texture npc;
            } texture;

            struct {
            public: sf::Music menu;
                    sf::Music level;
                    sf::Music boss;
            } music;

            std::map<sf::String, sf::String> dictionary;

        /// Separate method loading the dictionary
            bool loadDict();
        /// Method loading the resources
            bool load    ();
    };

/// Structure for the game settings
    struct Settings {
    public: struct {
            public: sf::Keyboard::Key move_up;
                    sf::Keyboard::Key move_down;
                    sf::Keyboard::Key move_left;
                    sf::Keyboard::Key move_right;

                    sf::Keyboard::Key attack;
                    sf::Keyboard::Key interact;

                    sf::Keyboard::Key open_inventory;
                    sf::Keyboard::Key open_attributes;
                    sf::Keyboard::Key open_quests;
                    sf::Keyboard::Key open_map;
                    sf::Keyboard::Key open_bookOfSpells;

                    sf::Keyboard::Key useslot_1;
                    sf::Keyboard::Key useslot_2;
                    sf::Keyboard::Key useslot_3;
                    sf::Keyboard::Key useslot_4;
                    sf::Keyboard::Key useslot_5;
            } keys;
            
            struct {
            public: float music_volume;
                    float effects_volume;
                    bool  music_muted;
                    bool  effects_muted;
            } sound;
            
            struct {
            public: sf::ContextSettings csettings;
                    sf::Vector2u        resolution;
                    bool                vsync;
                    bool                fullscreen;
            } graphics;
        /// Structure for the game settings
            struct {
            public: std::string language;
            } game;

        /// Method printing the current settings
            void print();
        /// Method overwriting the current settings
            void save ();
        /// Method loading the current settings
            bool load ();
    };


/// Class for the program
    class Program {
    private: sf::Event        event_;
             sf::RenderWindow window_;
         
             Game*            game_;
         
         /// Loads all the resources, settings and dictionary
             bool loadResources();
         
         /// Runs the game
             void runGame      ();
         
         /// Runs the game's main loop
             void mainLoop     ();
         
         /// Handles the window events
             void handleEvents ();
         
         /// Updates the game's state
             void update       (sf::Clock&);
         
         /// Draws the game's components
             void draw         ();
    
    public:  Program();
            ~Program();
         
             Game* getGame     () const { return game_; }
    };

}

#endif // program_h
