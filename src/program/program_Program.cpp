/**
 * @file src/program/Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program.h"
#include "funcs/files.h"
#include "funcs/funcs.h"

#include <SFML/System/String.hpp>

#include <cstdio>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>
#include <codecvt>

extern std::map<sf::String, sf::String> dictionary;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;
extern rr::Settings settings;

namespace rr {

    Program::Program() {
        if (readConfig() && readDictionary() && loadResources())
            runGame();
    }

    Program::~Program() {
        delete game;
    }

    void Program::runGame() {
        window.create(sf::VideoMode(settings.resolution.x, settings.resolution.y, 32), "PAhAom", (settings.fullscreen)?sf::Style::Fullscreen:sf::Style::Close, settings.csettings);
        window.setVerticalSyncEnabled(settings.vsync);
        view.setSize((sf::Vector2f)settings.resolution);
        window.setView(view);

        sf::Clock timer;
        game = new Game(window);

        while (window.isOpen()) {
            game->update(timer.getElapsedTime().asMilliseconds(), view);
            timer.restart();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (event.type == sf::Event::Resized) view.setSize((sf::Vector2f)window.getSize());
                game->buttonEvents(window, view);
            }

            window.clear();
            game->draw(window, view);
            window.display();
        }
        settings.save();
    }

    bool Program::readConfig() {
        std::ifstream iconfig;
        try {
            iconfig.open("config.cfg");
            if (!iconfig.good()) throw "File not found";
            puts(">Loading a config file...");

            while (!iconfig.eof()) {
                std::string param;
                iconfig >> param;

                if (param[0] == ';' || param == "") {
                    std::getline(iconfig, param);
                    continue;
                } else {
                    if (param == "width:") {
                        readFile(iconfig, settings.resolution.x);
                    }
                    else if (param == "height:") {
                        readFile(iconfig, settings.resolution.y);
                    }
                    else if (param == "fullscreen:") {
                        readFile(iconfig, settings.fullscreen);
                    }
                    else if (param == "vsync:") {
                        readFile(iconfig, settings.vsync);
                    }
                    else if (param == "lang:") {
                        iconfig >> settings.language;
                    }
                    else if (param == "antialiasing:") {
                        iconfig >> settings.csettings.antialiasingLevel;

                    }
                    else if (param == "depthbits:") {
                        iconfig >> settings.csettings.depthBits;
                    }
                    else if (param == "stencilbits:") {
                        iconfig >> settings.csettings.stencilBits;
                    }
                    else
                        throw "Wrong parameter";
                }
            }
            settings.print();
            puts(">Done.");
        } catch (...) {
            puts("!Error loading config.cfg!");

            iconfig.clear();
            iconfig.sync();

            puts(">Creating a new config file...");
            std::ofstream oconfig("config.cfg");
            oconfig.clear();
            oconfig << ";--------------;\n";
            oconfig << ";video settings;\n";
            oconfig << ";----screen----;\n";
            oconfig << "width:\t\t1280\n";
            oconfig << "height:\t\t720\n";
            oconfig << "fullscreen:\t0\n";
            oconfig << "vsync:\t\t1\n";
            oconfig << "lang:\t\ten\n";
            oconfig << ";---graphics---;\n";
            oconfig << "antialiasing:\t4\n";
            oconfig << "depthbits:\t24\n";
            oconfig << "stencilbits:\t8\n";
            oconfig << ";--------------;";

            oconfig.close();
            readConfig();
        }
        iconfig.close();
        return true;
    }

    bool Program::readDictionary() {
        std::ifstream idict;
        idict.open("data/lang/"+settings.language+".lang");

        if (idict.good()) {
            puts(">Loading the dictionary...");
            std::cout << "=====WORD======" << std::setw(40) << "===TRANSLATION===\n";
            while (!idict.eof()) {
                std::string word;
                std::string translation;

                idict >> word;
                if (word[0]==';' || word=="")
                    std::getline(idict, word);
                else {
                    idict.seekg(idict.tellg()+1l);
                    std::getline(idict, translation);
                    dictionary[word] = utf8ToUtf32(translation);

                    std::cout << word << std::setw(38-word.size()+translation.size()) << translation + "\n";
                }
            }
            idict.close();
            puts(">Done.");
            return true;
        }
        puts("!Error loading the dictionary!");
        return false;
    }

    bool Program::loadResources() {
        return (font_Unifont.loadFromFile("data/font/unifont-8.0.01.ttf")
             && font_Pixel.loadFromFile("data/font/I-pixel-u-mod.ttf"));
    }

}
