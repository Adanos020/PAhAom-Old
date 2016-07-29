/**
 * @file src/program/Settings.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>

namespace rr {

/// Structure for the game settings
    struct Settings {
    public: static struct Keys {
            public: sf::Keyboard::Key move_up;
                    sf::Keyboard::Key move_down;
                    sf::Keyboard::Key move_left;
                    sf::Keyboard::Key move_right;

                    sf::Keyboard::Key attack;
                    sf::Keyboard::Key interact;

                    sf::Keyboard::Key open_inventory;
                    sf::Keyboard::Key open_attributes;
                    sf::Keyboard::Key open_journal;
                    sf::Keyboard::Key open_map;
                    sf::Keyboard::Key open_bookOfSpells;

                    sf::Keyboard::Key useslot_1;
                    sf::Keyboard::Key useslot_2;
                    sf::Keyboard::Key useslot_3;
                    sf::Keyboard::Key useslot_4;
                    sf::Keyboard::Key useslot_5;

                    Keys() {
                        move_up           = sf::Keyboard::W;
                        move_down         = sf::Keyboard::S;
                        move_left         = sf::Keyboard::A;
                        move_right        = sf::Keyboard::D;
                        interact          = sf::Keyboard::E;
                        attack            = sf::Keyboard::Space;
                        open_inventory    = sf::Keyboard::Tab;
                        open_attributes   = sf::Keyboard::B;
                        open_journal      = sf::Keyboard::N;
                        open_map          = sf::Keyboard::M;
                        open_bookOfSpells = sf::Keyboard::V;
                        useslot_1         = sf::Keyboard::Num1;
                        useslot_2         = sf::Keyboard::Num2;
                        useslot_3         = sf::Keyboard::Num3;
                        useslot_4         = sf::Keyboard::Num4;
                        useslot_5         = sf::Keyboard::Num5;
                    }
            } keys;
            
            static struct Sound {
            public: float music_volume;
                    float effects_volume;
                    bool  music_muted;
                    bool  effects_muted;

                    Sound() {
                        music_volume   = 50.f;
                        effects_volume = 50.f;
                        music_muted    = false;
                        effects_muted  = false;
                    }
            } sound;
            
            static struct Graphics {
            public: sf::ContextSettings csettings;
                    sf::Vector2u        resolution;
                    bool                vsync;
                    bool                fullscreen;

                    Graphics() {
                        resolution.x                = 1280;
                        resolution.y                = 720;
                        fullscreen                  = false;
                        vsync                       = true;
                        csettings.antialiasingLevel = 4;
                        csettings.depthBits         = 24;
                        csettings.stencilBits       = 8;
                    }
            } graphics;
            
            static struct Game {
            public: std::string language;

                    Game() {
                        language = "en";
                    }
            } game;

        /// Method printing the current settings
            static void print();
        /// Method overwriting the current settings
            static void save ();
        /// Method loading the current settings
            static bool load ();
    };

}

#endif // SETTINGS_HPP
