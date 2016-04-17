/**
 * @file src/program/Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "program.hpp"
#include "funcs/files.hpp"
#include "funcs/funcs.hpp"

#include <SFML/System/String.hpp>

extern rr::Resources resources;
extern rr::Settings  settings;

namespace rr {

    Program::Program() {
        if (loadResources())
            runGame();
    }

    Program::~Program() {
        delete game;
    }

    bool Program::loadResources() {
        return (settings .load()
             && resources.load());
    }

    void Program::runGame() {
        window.create(sf::VideoMode(settings.graphics.resolution.x, settings.graphics.resolution.y, 32), "PAhAom", settings.graphics.fullscreen?(sf::Style::Fullscreen):(sf::Style::Close), settings.graphics.csettings);
        window.setVerticalSyncEnabled(settings.graphics.vsync);
        window.setKeyRepeatEnabled(false);

        game = new Game(window);
        mainLoop();
    }

    void Program::handleEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            game->buttonEvents(window, event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && game->isStarted())
                game->pause(!game->isPaused());
        }
    }

    void Program::update(sf::Clock& timer) {
        game->update(timer.getElapsedTime().asMilliseconds());
        timer.restart();
    }

    void Program::draw() {
        window.clear();
        game->draw(window);
        window.display();
    }

    void Program::mainLoop() {
        sf::Clock timer;
        while (window.isOpen()) {
            handleEvents();
            update(timer);
            draw();
        }
    }

}
