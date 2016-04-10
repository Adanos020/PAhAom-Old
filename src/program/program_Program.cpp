/**
 * @file src/program/Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program.hpp"
#include "funcs/files.hpp"
#include "funcs/funcs.hpp"

#include <SFML/System/String.hpp>

extern rr::Dictionary dictionary;
extern rr::Resources  resources;
extern rr::Settings   settings;

namespace rr {

    Program::Program() {
        if (loadResources())
            runGame();
    }

    Program::~Program() {
        delete game;
    }

    bool Program::loadResources() {
        return (resources .load()
             && settings  .load()
             && dictionary.load());
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
