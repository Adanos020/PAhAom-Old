/**
 * @file src/program/program_Resources.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "program.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include "funcs/strings.hpp"

extern rr::Settings settings;

namespace rr {

    bool Resources::load() {
        return (font   .Unifont.loadFromFile("data/font/unifont-8.0.01.ttf")
             && font   .Pixel  .loadFromFile("data/font/I-pixel-u-mod.ttf")
             && texture.gui    .loadFromFile("data/graphics/gui.png")
             && texture.player .loadFromFile("data/graphics/player.png")
             && texture.items  .loadFromFile("data/graphics/items.png")
             && texture.tileset.loadFromFile("data/graphics/tileset.png")
             && texture.objects.loadFromFile("data/graphics/objects.png")
             && loadDict());
    }

    bool Resources::loadDict() {
        std::ifstream idict;
        idict.open("data/lang/"+settings.game.language+".lang");

        if (idict.good()) {
            puts(">Loading the dictionary...");
            std::cout << "=====WORD======" << std::setw(40) << "===TRANSLATION===\n";
            while (!idict.eof()) {
                std::string word;
                std::string translation;

                idict >> word;
                if (word[0] == ';' || word == "")
                    std::getline(idict, word);
                else {
                    idict.seekg(idict.tellg()+1l);
                    std::getline(idict, translation);
                    dictionary[word] = utf8ToUtf32(translation);
                    std::cout << word << std::setw(38-word.size()+translation.size()) << translation + "\n";
                }
            }
            idict.close();
            std::cout << ">Done.\n";
            return true;
        }
        std::cout << "!Error loading the dictionary!\n";
        return false;
    }

}
