/**
 * @file src/program/program_Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "program.hpp"
#include "funcs/files.hpp"
#include "funcs/funcs.hpp"

#include <SFML/System/String.hpp>

extern rr::Resources resources;
extern rr::Settings  settings;

namespace rr {

    Program::Program(unsigned seed) {
        if (  loadResources()
            ) runGame(seed);
    }

    Program::~Program() {
        delete game_;
    }

    bool Program::loadResources() {
        return (settings .load()
             && resources.load());
    }

    void Program::runGame(unsigned seed) {
        window_.create                (sf::VideoMode(settings.graphics.resolution.x, settings.graphics.resolution.y, 32), "PAhAom",
                                                     settings.graphics.fullscreen ? (sf::Style::Fullscreen) : (sf::Style::Close), settings.graphics.csettings);
        window_.setVerticalSyncEnabled(settings.graphics.vsync);
        window_.setKeyRepeatEnabled   (false);

        game_ = new Game(seed);
        mainLoop();
    }

    void Program::handleEvents() {
        while (window_.pollEvent(event_)) {
            if (  event_.type == sf::Event::Closed
                ) window_.close();

            game_->buttonEvents(window_, event_);
        }
    }

    void Program::update(sf::Clock& timer) {
        if (game_->isStarted()) {
            game_->update(event_, timer.getElapsedTime());
        }
        timer.restart();
    }

    void Program::draw() {
        window_.clear  ();
        game_ ->draw   (window_);
        window_.display();
    }

    void Program::mainLoop() {
        sf::Clock timer;
        while (window_.isOpen()) {
            handleEvents();
            update      (timer);
            draw        ();
        }
    }

}
