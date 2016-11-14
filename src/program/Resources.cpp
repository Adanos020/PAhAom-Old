/**
 * @file src/program/Resources.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>
#include <fstream>

#include "Resources.hpp"
#include "../Program.hpp"

#include "funcs/strings.hpp"

namespace rr
{

    Resources::Font                  Resources::font;
    Resources::Texture               Resources::texture;
    //Resources::Sound                 Resources::sound;
    std::map<sf::String, sf::String> Resources::dictionary;

    bool Resources::load()
    {
        return loadDict()
            && font   .Unifont       .loadFromFile("data/font/unifont-8.0.01.ttf")
            && font   .Pixel         .loadFromFile("data/font/I-pixel-u-mod.ttf")
            && font   .FinalFantasy  .loadFromFile("data/font/final_fantasy_36_font.ttf")
            && texture.gui           .loadFromFile("data/graphics/gui.png")
            && texture.player        .loadFromFile("data/graphics/player.png")
            && texture.items         .loadFromFile("data/graphics/items.png")
            && texture.tileset       .loadFromFile("data/graphics/tileset.png")
            && texture.objects       .loadFromFile("data/graphics/objects.png")
            && texture.npc           .loadFromFile("data/graphics/npc.png")
            && texture.npc_bully     .loadFromFile("data/graphics/npc_bully.png")
            && texture.npc_csbow     .loadFromFile("data/graphics/npc_csbow.png")
            && texture.npc_rogue     .loadFromFile("data/graphics/npc_rogue.png")
            && texture.book_of_spells.loadFromFile("data/graphics/book_of_spells.png");
    }

    bool Resources::loadDict()
    {
        std::ifstream idict;
        idict.open("data/lang/"+Settings::game.language+".lang");

        std::cout << "lang: " << Settings::game.language << '\n';

        if (idict.good())
        {
            puts(">Loading the dictionary...");
            while (!idict.eof())
            {
                std::string word;
                std::string translation;

                std::getline(idict, word);
                if (word[0] != ';' && word != "")
                {
                    std::getline(idict, translation);
                    dictionary[word] = utf8ToUtf32(translation);
                }
            }
            idict.close();
            puts(">Done.");
            return true;
        }
        puts("!Error loading the dictionary!");
        return false;
    }

}
