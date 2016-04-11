/**
 * @file src/program/Settings.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program.hpp"
#include "funcs/files.hpp"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

namespace rr {

    void Settings::print() {
        std::cout << "+========PARAMETER========|===========VALUE===========+\n";
        std::cout << "+-------------------Game settings---------------------+\n";
        std::cout << "|lang                     |" << language                    << std::setw(29-language.size())                                    << "|\n";
        std::cout << "+-----------------Graphical settings------------------+\n";
        std::cout << "|width                    |" << resolution.x                << std::setw(29-std::to_string(resolution.x)               .size()) << "|\n";
        std::cout << "|height                   |" << resolution.y                << std::setw(29-std::to_string(resolution.y)               .size()) << "|\n";
        std::cout << "|fullscreen               |" << fullscreen                  << std::setw(29-std::to_string(fullscreen)                 .size()) << "|\n";
        std::cout << "|vsync                    |" << vsync                       << std::setw(29-std::to_string(vsync)                      .size()) << "|\n";
        std::cout << "|antialiasing             |" << csettings.antialiasingLevel << std::setw(29-std::to_string(csettings.antialiasingLevel).size()) << "|\n";
        std::cout << "|depthbits                |" << csettings.depthBits         << std::setw(29-std::to_string(csettings.depthBits)        .size()) << "|\n";
        std::cout << "|stencilbits              |" << csettings.stencilBits       << std::setw(29-std::to_string(csettings.stencilBits)      .size()) << "|\n";
        std::cout << "+----------------------Controls-----------------------+\n";
        std::cout << "|move_up                  |" << keys.move_up                << std::setw(29-std::to_string(keys.move_up)               .size()) << "|\n";
        std::cout << "|move_down                |" << keys.move_down              << std::setw(29-std::to_string(keys.move_down)             .size()) << "|\n";
        std::cout << "|move_left                |" << keys.move_left              << std::setw(29-std::to_string(keys.move_left)             .size()) << "|\n";
        std::cout << "|move_right               |" << keys.move_right             << std::setw(29-std::to_string(keys.move_right)            .size()) << "|\n";
        std::cout << "|interact                 |" << keys.interact               << std::setw(29-std::to_string(keys.interact)              .size()) << "|\n";
        std::cout << "|attack                   |" << keys.attack                 << std::setw(29-std::to_string(keys.attack)                .size()) << "|\n";
        std::cout << "|pickup                   |" << keys.pickup                 << std::setw(29-std::to_string(keys.pickup)                .size()) << "|\n";
        std::cout << "|open_inventory           |" << keys.open_inventory         << std::setw(29-std::to_string(keys.open_inventory)        .size()) << "|\n";
        std::cout << "|open_attributes          |" << keys.open_attributes        << std::setw(29-std::to_string(keys.open_attributes)       .size()) << "|\n";
        std::cout << "|open_quests              |" << keys.open_quests            << std::setw(29-std::to_string(keys.open_quests)           .size()) << "|\n";
        std::cout << "|open_map                 |" << keys.open_map               << std::setw(29-std::to_string(keys.open_map)              .size()) << "|\n";
        std::cout << "|useslot_1                |" << keys.useslot_1              << std::setw(29-std::to_string(keys.useslot_1)             .size()) << "|\n";
        std::cout << "|useslot_2                |" << keys.useslot_2              << std::setw(29-std::to_string(keys.useslot_2)             .size()) << "|\n";
        std::cout << "|useslot_3                |" << keys.useslot_3              << std::setw(29-std::to_string(keys.useslot_3)             .size()) << "|\n";
        std::cout << "|useslot_4                |" << keys.useslot_4              << std::setw(29-std::to_string(keys.useslot_4)             .size()) << "|\n";
        std::cout << "|useslot_5                |" << keys.useslot_5              << std::setw(29-std::to_string(keys.useslot_5)             .size()) << "|\n";
        std::cout << "+-----------------------------------------------------+\n";
    }

    void Settings::save() {
        puts(">Saving the settings...");

        std::ofstream oconfig("config.cfg");
        oconfig.clear();

        oconfig << ";---------------;\n";
        oconfig << ";-game settings-;\n";
        oconfig << "lang:\t\t"         + language                                   +"\n";
        oconfig << ";---------------;\n";
        oconfig << ";video  settings;\n";
        oconfig << ";----screen-----;\n";
        oconfig << "width:\t\t"        + std::to_string(resolution.x)               +"\n";
        oconfig << "height:\t\t"       + std::to_string(resolution.y)               +"\n";
        oconfig << "fullscreen:\t"     + std::to_string(fullscreen)                 +"\n";
        oconfig << "vsync:\t\t"        + std::to_string(vsync)                      +"\n";
        oconfig << ";---graphics----;\n";
        oconfig << "antialiasing:\t"   + std::to_string(csettings.antialiasingLevel)+"\n";
        oconfig << "depthbits:\t"      + std::to_string(csettings.depthBits)        +"\n";
        oconfig << "stencilbits:\t"    + std::to_string(csettings.stencilBits)      +"\n";
        oconfig << ";---------------;\n";
        oconfig << ";--key binding--;\n";
        oconfig << ";---movement----;\n";
        oconfig << "move_up:\t"        + std::to_string(keys.move_up)               +"\n";
        oconfig << "move_down:\t"      + std::to_string(keys.move_down)             +"\n";
        oconfig << "move_left:\t"      + std::to_string(keys.move_left)             +"\n";
        oconfig << "move_right:\t"     + std::to_string(keys.move_right)            +"\n";
        oconfig << ";----actions----;\n";
        oconfig << "interact:\t"       + std::to_string(keys.interact)              +"\n";
        oconfig << "attack:\t\t"       + std::to_string(keys.attack)                +"\n";
        oconfig << "pickup:\t\t"       + std::to_string(keys.pickup)                +"\n";
        oconfig << ";---open menus--;\n";
        oconfig << "open_inventory:\t" + std::to_string(keys.open_inventory)        +"\n";
        oconfig << "open_attributes: " + std::to_string(keys.open_attributes)       +"\n";
        oconfig << "open_quests:\t"    + std::to_string(keys.open_quests)           +"\n";
        oconfig << "open_map:\t"       + std::to_string(keys.open_map)              +"\n";
        oconfig << ";---use slots---;\n";
        oconfig << "useslot_1:\t"      + std::to_string(keys.useslot_1)             +"\n";
        oconfig << "useslot_2:\t"      + std::to_string(keys.useslot_2)             +"\n";
        oconfig << "useslot_3:\t"      + std::to_string(keys.useslot_3)             +"\n";
        oconfig << "useslot_4:\t"      + std::to_string(keys.useslot_4)             +"\n";
        oconfig << "useslot_5:\t"      + std::to_string(keys.useslot_5)             +"\n";
        oconfig << ";---------------;\n";

        oconfig.close();
    }

    bool Settings::load() {
        try {
            std::ifstream iconfig("config.cfg");
            if (!iconfig.good())
                throw "File not found";
            puts(">Loading a config file...");

            while (!iconfig.eof()) {
                std::string param;
                int keyCode;
                iconfig >> param;

                if (param[0] == ';' || param == "") {
                    std::getline(iconfig, param);
                    continue;
                } else {
                    if      (param == "lang:")              iconfig >> language;
                    else if (param == "width:")             readFile(iconfig, resolution.x);
                    else if (param == "height:")            readFile(iconfig, resolution.y);
                    else if (param == "fullscreen:")        readFile(iconfig, fullscreen);
                    else if (param == "vsync:")             readFile(iconfig, vsync);
                    else if (param == "antialiasing:")      readFile(iconfig, csettings.antialiasingLevel);
                    else if (param == "depthbits:")         readFile(iconfig, csettings.depthBits);
                    else if (param == "stencilbits:")       readFile(iconfig, csettings.stencilBits);
                    else if (param == "move_up:")         { readFile(iconfig, keyCode); keys.move_up         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_down:")       { readFile(iconfig, keyCode); keys.move_down       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_left:")       { readFile(iconfig, keyCode); keys.move_left       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_right:")      { readFile(iconfig, keyCode); keys.move_right      = (sf::Keyboard::Key)keyCode; }
                    else if (param == "interact:")        { readFile(iconfig, keyCode); keys.interact        = (sf::Keyboard::Key)keyCode; }
                    else if (param == "attack:")          { readFile(iconfig, keyCode); keys.attack          = (sf::Keyboard::Key)keyCode; }
                    else if (param == "pickup:")          { readFile(iconfig, keyCode); keys.pickup          = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_inventory:")  { readFile(iconfig, keyCode); keys.open_inventory  = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_attributes:") { readFile(iconfig, keyCode); keys.open_attributes = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_quests:")     { readFile(iconfig, keyCode); keys.open_quests     = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_map:")        { readFile(iconfig, keyCode); keys.open_map        = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_1:")       { readFile(iconfig, keyCode); keys.useslot_1       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_2:")       { readFile(iconfig, keyCode); keys.useslot_2       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_3:")       { readFile(iconfig, keyCode); keys.useslot_3       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_4:")       { readFile(iconfig, keyCode); keys.useslot_4       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_5:")       { readFile(iconfig, keyCode); keys.useslot_5       = (sf::Keyboard::Key)keyCode; }
                    else                                  throw "Wrong parameter";
                }
            }
            iconfig.close();
            print();
            puts(">Done.");
        } catch (...) {
            puts("!Error loading config.cfg!");
            puts(">Creating a new config file...");

            resolution.x                = 1280;
            resolution.y                = 720;
            fullscreen                  = false;
            vsync                       = true;
            language                    = "en";
            csettings.antialiasingLevel = 4;
            csettings.depthBits         = 24;
            csettings.stencilBits       = 8;
            keys.move_up                = sf::Keyboard::W;
            keys.move_down              = sf::Keyboard::S;
            keys.move_left              = sf::Keyboard::A;
            keys.move_right             = sf::Keyboard::D;
            keys.interact               = sf::Keyboard::E;
            keys.attack                 = sf::Keyboard::Space;
            keys.pickup                 = sf::Keyboard::Q;
            keys.open_inventory         = sf::Keyboard::Tab;
            keys.open_attributes        = sf::Keyboard::B;
            keys.open_quests            = sf::Keyboard::N;
            keys.open_map               = sf::Keyboard::M;
            keys.useslot_1              = sf::Keyboard::Num1;
            keys.useslot_2              = sf::Keyboard::Num2;
            keys.useslot_3              = sf::Keyboard::Num3;
            keys.useslot_4              = sf::Keyboard::Num4;
            keys.useslot_5              = sf::Keyboard::Num5;

            print();
            save ();
        }
        return true;
    }

}
