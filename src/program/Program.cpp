#include "program.h"
#include "funcs/files.h"
#include "funcs/funcs.h"
#include <cstdio>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>

extern std::map<std::string, std::wstring> dictionary;
extern sf::Font pixelFont;
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
        window.create(sf::VideoMode(settings.resolution.x, settings.resolution.y, 32), "PAHAOM", (settings.fullscreen)?sf::Style::Fullscreen:sf::Style::Close, settings.csettings);
        window.setVerticalSyncEnabled(settings.vsync);
        view.setSize((sf::Vector2f)settings.resolution);
        window.setView(view);

        sf::Clock timer;
        game = new Game(window, settings);

        while (window.isOpen()) {
            game->controls(timer.getElapsedTime().asMilliseconds());
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
        std::wifstream idict;
        if (settings.language == "en")
            idict.open("data/lang/en.lang");
        else if (settings.language == "pl")
            idict.open("data/lang/pl.lang");
        else if (settings.language == "fc")
            idict.open("data/lang/fc.lang");

        puts(">Loading the dictionary...");
        if (idict.good()) {
            std::cout << "===WORD===" << std::setw(45) << "===TRANSLATION===\n";
            while (!idict.eof()) {
                std::wstring word;
                std::wstring translation;

                idict >> word;
                if (word[0]==';' || word==L"") {
                    std::getline(idict, word);
                    continue;
                }
                std::getline(idict, translation);
                translation.erase(0, 1);

                std::wcout << word << std::setw(38-word.size()+translation.size()) << translation + L"\n";

                dictionary[wtoa(word)] = translation;
            }
            idict.close();
            return true;
        }
        return false;
    }

    bool Program::loadResources() {
        if (pixelFont.loadFromFile("data/font/I-pixel-u-mod.ttf"))
            return true;
        return false;
    }

}
