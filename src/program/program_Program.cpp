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
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

extern std::map<sf::String, sf::String> dictionary;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;
extern rr::Settings settings;
extern bool debug;

namespace rr {

    Program::Program() {
        if (loadResources())
            runGame();
    }

    Program::~Program() {
        delete game;
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
            puts(">Done.");
            return true;
        }
        puts("!Error loading the dictionary!");
        return false;
    }

    bool Program::loadResources() {
        return (font_Unifont.loadFromFile("data/font/unifont-8.0.01.ttf")
                && font_Pixel.loadFromFile("data/font/I-pixel-u-mod.ttf")
                && settings.load()
                && readDictionary());
    }

    void Program::runGame() {
        window.create(sf::VideoMode(settings.resolution.x, settings.resolution.y, 32), "PAhAom", (settings.fullscreen)?sf::Style::Fullscreen:sf::Style::Close, settings.csettings);
        window.setVerticalSyncEnabled(settings.vsync);
        view.setSize((sf::Vector2f)settings.resolution);
        window.setView(view);

        game = new Game(window);
        mainLoop();
    }

    void Program::mainLoop() {
        sf::Clock timer;
        while (window.isOpen()) {
            handleEvents();
            update(timer);
            draw();
        }
    }

    void Program::handleEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) view.setSize((sf::Vector2f)window.getSize());
            game->buttonEvents(window, view);
        }
    }

    void Program::update(sf::Clock& timer) {
        game->update(timer.getElapsedTime().asMilliseconds(), view);
        timer.restart();
    }

    void Program::draw() {
        window.clear();
        game->draw(window, view);
        window.display();
    }

}
