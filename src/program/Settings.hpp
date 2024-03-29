/**
 * @file src/program/Settings.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <SFML/Graphics.hpp>

namespace rr
{

/// Structure for the game settings
    struct Settings
    {
    public: static struct Keys
            {
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

                    ////////////////////////////////////////////////////////////////////////
                    /// \brief Regular constructor.
                    ////////////////////////////////////////////////////////////////////////
                    Keys()
                    {
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
                    }
            } keys;

            static struct Sound
            {
            public: float music_volume;
                    float effects_volume;
                    bool  music_muted;
                    bool  effects_muted;

                    ////////////////////////////////////////////////////////////////////////
                    /// \brief Regular constructor.
                    ////////////////////////////////////////////////////////////////////////
                    Sound()
                    {
                        music_volume   = 50.f;
                        effects_volume = 50.f;
                        music_muted    = false;
                        effects_muted  = false;
                    }
            } sound;
            
            static struct Graphics
            {
            public: sf::ContextSettings csettings;
                    sf::Vector2u        resolution;
                    bool                vsync;
                    bool                fullscreen;

                    ////////////////////////////////////////////////////////////////////////
                    /// \brief Regular constructor.
                    ////////////////////////////////////////////////////////////////////////
                    Graphics()
                    {
                        resolution.x                = 1280;
                        resolution.y                = 720;
                        fullscreen                  = false;
                        vsync                       = true;
                        csettings.antialiasingLevel = 4;
                        csettings.depthBits         = 24;
                        csettings.stencilBits       = 8;
                    }
            } graphics;
            
            static struct Game
            {
            public: std::string language;
                    bool        debugMode;

                    ////////////////////////////////////////////////////////////////////////
                    /// \brief Regular constructor.
                    ////////////////////////////////////////////////////////////////////////
                    Game()
                    {
                        language  = "en";
                        debugMode = false;
                    }
            } game;

            ////////////////////////////////////////////////////////////////////////
            /// \brief Method printing the current settings.
            ////////////////////////////////////////////////////////////////////////
            static void print();

            ////////////////////////////////////////////////////////////////////////
            /// \brief Method overwriting the current settings.
            ////////////////////////////////////////////////////////////////////////
            static void save();

            ////////////////////////////////////////////////////////////////////////
            /// \brief Method loading the current settings.
            ////////////////////////////////////////////////////////////////////////
            static bool load();
    };

}
