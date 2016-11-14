/**
 * @file src/program/Resources.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace rr
{

    struct Resources
    {
    public: static struct Font
            {
            public: sf::Font Unifont;
                    sf::Font Pixel;
                    sf::Font FinalFantasy;
            } font;
        
            static struct Texture
            {
            public: sf::Texture gui;
                    sf::Texture player;
                    sf::Texture items;
                    sf::Texture tileset;
                    sf::Texture objects;
                    sf::Texture npc;
                    sf::Texture npc_bully;
                    sf::Texture npc_csbow;
                    sf::Texture npc_rogue;
                    sf::Texture book_of_spells;
            } texture;
/*
            static struct Sound
            {
            public:
            } sound;
*/
            static std::map<sf::String, sf::String> dictionary;

            ////////////////////////////////////////////////////////////////////////
            /// \brief Separate method loading the dictionary.
            ////////////////////////////////////////////////////////////////////////
            static bool loadDict();

            ////////////////////////////////////////////////////////////////////////
            /// \brief Method loading the resources.
            ////////////////////////////////////////////////////////////////////////
            static bool load();
    };

}
