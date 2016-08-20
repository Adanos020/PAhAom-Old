/**
 * @file src/program/Resources.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace rr {

    struct Resources {
    public: static struct Font {
            public: sf::Font Unifont;
                    sf::Font Pixel;
                    sf::Font FinalFantasy;
            } font;
        
            static struct Texture {
            public: sf::Texture gui;
                    sf::Texture player;
                    sf::Texture items;
                    sf::Texture tileset;
                    sf::Texture objects;
                    sf::Texture npc;
                    sf::Texture enemies;
                    sf::Texture book_of_spells;
            } texture;

            static struct Music {
            public: sf::Music menu;
                    sf::Music level;
                    sf::Music boss;
            } music;

            static std::map<sf::String, sf::String> dictionary;

            ////////////////////////////////////////////////////////////////////////
            /// \brief Separate method loading the dictionary.
            ////////////////////////////////////////////////////////////////////////
            static bool loadDict();

            ////////////////////////////////////////////////////////////////////////
            /// \brief Method loading the resources.
            ////////////////////////////////////////////////////////////////////////
            static bool load    ();
    };

}

#endif // RESOURCES_HPP
