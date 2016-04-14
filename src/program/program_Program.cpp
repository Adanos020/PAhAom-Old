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
        view.setSize((sf::Vector2f)settings.graphics.resolution);

        window.create(sf::VideoMode(settings.graphics.resolution.x, settings.graphics.resolution.y, 32), "PAhAom", settings.graphics.fullscreen?(sf::Style::Fullscreen):(sf::Style::Close), settings.graphics.csettings);
        window.setVerticalSyncEnabled(settings.graphics.vsync);
        window.setView(view);
        window.setKeyRepeatEnabled(false);

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
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                view.setSize((sf::Vector2f)window.getSize());
            game->buttonEvents(window, view);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && game->isStarted())
                game->pause(!game->isPaused());
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
