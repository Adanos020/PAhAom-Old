#include "program.h"
#include "funcs/files.h"
#include "funcs/funcs.h"
#include <cstdio>
#include <ctime>
#include <string>
#include <iostream>

namespace rr {

    std::map<std::string, std::wstring> dictionary;

    Program::Program() {
        if (readConfig() && readDictionary()) runGame();
    }

    Program::~Program() {
        delete game;
    }

    void Program::runGame() {
        window.create(sf::VideoMode(resolution.x, resolution.y, 32), "PAHAOM", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        window.setVerticalSyncEnabled(vsync);
        view.setSize((sf::Vector2f)resolution);
        window.setView(view);

        sf::Clock timer;
        game = new Game(window);

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
    }

    bool Program::readConfig() {
        std::ifstream iconfig;
        try {
            iconfig.open("config.cfg");
            if (!iconfig.good()) throw "File not found";
            puts("Loading a config file...");

            while (!iconfig.eof()) {
                std::string param;
                iconfig >> param;

                if (param[0] == ';') {
                    std::getline(iconfig, param);
                    continue;
                }
                else if (param == "") continue;
                else if (param == "width:") readFile(iconfig, resolution.x);
                else if (param == "height:") readFile(iconfig, resolution.y);
                else if (param == "fullscreen:") readFile(iconfig, fullscreen);
                else if (param == "vsync:") readFile(iconfig, vsync);
                else if (param == "lang:") iconfig >> language;
                else throw "Wrong parameter";
            }
        } catch (...) {
            puts("Error loading config.cfg!");

            iconfig.clear();
            iconfig.sync();

            puts("Creating a new config file...");
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
            oconfig << ";--------------;";

            oconfig.close();
            readConfig();
        }
        iconfig.close();
        return true;
    }

    bool Program::readDictionary() {
        std::wifstream idict;
        if (language == "en")
            idict.open("data/lang/en.lang");
        else if (language == "pl")
            idict.open("data/lang/pl.lang");
        else if (language == "fc")
            idict.open("data/lang/fc.lang");

        if (idict.good()) {
            while (!idict.eof()) {
                std::wstring word;
                std::wstring translation;

                idict >> word;
                std::getline(idict, translation);
                translation.erase(0, 1);

                std::wcout << L"word: \"" + word + L"\"\n";
                std::wcout << L"translation: \"" + translation + L"\"\n";

                dictionary[wtoa(word)] = translation;
            }
            idict.close();
            return true;
        }
        return false;
    }

}
