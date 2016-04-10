/**
 * @file src/program/Settings.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program.h"
#include "funcs/files.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

namespace rr {

    void Settings::print() {
        std::cout << "===PARAMETER===" << std::setw(40) << "======VALUE======\n";
        std::cout << "--------------------Game settings----------------------\n";
        std::cout << "lang"            << std::setw(33+language                                   .size()) << language                    << '\n';
        std::cout << "------------------Graphical settings-------------------\n";
        std::cout << "width"           << std::setw(32+std::to_string(resolution.x)               .size()) << resolution.x                << '\n';
        std::cout << "height"          << std::setw(31+std::to_string(resolution.y)               .size()) << resolution.y                << '\n';
        std::cout << "fullscreen"      << std::setw(27+std::to_string(fullscreen)                 .size()) << fullscreen                  << '\n';
        std::cout << "vsync"           << std::setw(32+std::to_string(vsync)                      .size()) << vsync                       << '\n';
        std::cout << "antialiasing"    << std::setw(25+std::to_string(csettings.antialiasingLevel).size()) << csettings.antialiasingLevel << '\n';
        std::cout << "depthbits"       << std::setw(28+std::to_string(csettings.depthBits)        .size()) << csettings.depthBits         << '\n';
        std::cout << "stencilbits"     << std::setw(26+std::to_string(csettings.stencilBits)      .size()) << csettings.stencilBits       << '\n';
        std::cout << "-----------------------Controls------------------------\n";
        std::cout << "move_up"         << std::setw(30+std::to_string(keys.move_up)               .size()) << keys.move_up                << '\n';
        std::cout << "move_down"       << std::setw(28+std::to_string(keys.move_down)             .size()) << keys.move_down              << '\n';
        std::cout << "move_left"       << std::setw(28+std::to_string(keys.move_left)             .size()) << keys.move_left              << '\n';
        std::cout << "move_right"      << std::setw(27+std::to_string(keys.move_left)             .size()) << keys.move_right             << '\n';
        std::cout << "interact"        << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.interact               << '\n';
        std::cout << "attack"          << std::setw(32+std::to_string(keys.move_left)             .size()) << keys.attack                 << '\n';
        std::cout << "pickup"          << std::setw(32+std::to_string(keys.move_left)             .size()) << keys.pickup                 << '\n';
        std::cout << "open_inventory"  << std::setw(24+std::to_string(keys.move_left)             .size()) << keys.open_inventory         << '\n';
        std::cout << "open_attributes" << std::setw(22+std::to_string(keys.move_left)             .size()) << keys.open_attributes        << '\n';
        std::cout << "open_quests"     << std::setw(27+std::to_string(keys.move_left)             .size()) << keys.open_quests            << '\n';
        std::cout << "open_map"        << std::setw(30+std::to_string(keys.move_left)             .size()) << keys.open_map               << '\n';
        std::cout << "useslot_1"       << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.useslot_1              << '\n';
        std::cout << "useslot_2"       << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.useslot_2              << '\n';
        std::cout << "useslot_3"       << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.useslot_3              << '\n';
        std::cout << "useslot_4"       << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.useslot_4              << '\n';
        std::cout << "useslot_5"       << std::setw(29+std::to_string(keys.move_left)             .size()) << keys.useslot_5              << '\n';
        std::cout << "-------------------------------------------------------\n";
    }

    void Settings::save() {
        puts(">Saving the settings...");

        std::ofstream oconfig("config.cfg");
        oconfig.clear();

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
        oconfig << ";system settings;\n";
        oconfig << "lang:\t\t"         + language                                   +"\n";
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
                    if      (param == "width:")             readFile(iconfig, resolution.x);
                    else if (param == "height:")            readFile(iconfig, resolution.y);
                    else if (param == "fullscreen:")        readFile(iconfig, fullscreen);
                    else if (param == "vsync:")             readFile(iconfig, vsync);
                    else if (param == "lang:")              iconfig >> language;
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
