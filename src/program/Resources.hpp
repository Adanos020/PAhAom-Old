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

/// Structure for the resources
    struct Resources {
    public: static struct Font {
            public: sf::Font Unifont;
                    sf::Font Pixel;
            } font;
        
            static struct Texture {
            public: sf::Texture gui;
                    sf::Texture player;
                    sf::Texture items;
                    sf::Texture tileset;
                    sf::Texture objects;
                    sf::Texture npc;
                    sf::Texture enemies;
            } texture;

            static struct Music {
            public: sf::Music menu;
                    sf::Music level;
                    sf::Music boss;
            } music;

            static std::map<sf::String, sf::String> dictionary;

        /// Separate method loading the dictionary
            static bool loadDict();
        /// Method loading the resources
            static bool load    ();
    };

}

#endif // RESOURCES_HPP
