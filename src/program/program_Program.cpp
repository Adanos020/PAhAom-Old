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
        delete _game;
    }

    bool Program::loadResources() {
        return (settings .load()
             && resources.load());
    }

    void Program::runGame() {
        _window.create(sf::VideoMode(settings.graphics.resolution.x, settings.graphics.resolution.y, 32), "PAhAom", settings.graphics.fullscreen?(sf::Style::Fullscreen):(sf::Style::Close), settings.graphics.csettings);
        _window.setVerticalSyncEnabled(settings.graphics.vsync);
        _window.setKeyRepeatEnabled(false);

        _game = new Game();
        mainLoop();
    }

    void Program::handleEvents() {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window.close();

            _game->buttonEvents(_window, _event);
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape && _game->isStarted())
                _game->pause(!_game->isPaused());
        }
    }

    void Program::update(sf::Clock& timer) {
        if (_game->isStarted()) {
            _game->update(timer.getElapsedTime().asMilliseconds());
        }
        timer.restart();
    }

    void Program::draw() {
        _window.clear();
        _game->draw(_window);
        _window.display();
    }

    void Program::mainLoop() {
        sf::Clock timer;
        while (_window.isOpen()) {
            handleEvents();
            update(timer);
            draw();
        }
    }

}
