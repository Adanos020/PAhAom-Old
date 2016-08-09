/**
 * @file src/program/Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Program.hpp"
#include "Settings.hpp"
#include "Resources.hpp"

#include "funcs/files.hpp"
#include "funcs/classes.hpp"

#include <SFML/System/String.hpp>

namespace rr {

    Program::Program() {
        if (  loadResources()
            ) runGame();
    }

    bool Program::loadResources() {
        return Settings ::load()
            && Resources::load();
    }

    void Program::runGame() {
        window_.setVerticalSyncEnabled(Settings::graphics.vsync);
        window_.setFramerateLimit     (144);
        window_.setKeyRepeatEnabled   (false);
        window_.create                (sf::VideoMode(Settings::graphics.resolution.x, Settings::graphics.resolution.y, 32), "PAhAom",
                                                     Settings::graphics.fullscreen ? (sf::Style::Fullscreen) : (sf::Style::Close), Settings::graphics.csettings);
        
        game_ = new Game();
        mainLoop();
    }

    void Program::handleEvents() {
        while (window_.pollEvent(event_)) {
            if (  event_.type == sf::Event::Closed
                ) window_.close();
            if (  event_.type == sf::Event::LostFocus
                ) game_->pause(true);

            game_->buttonEvents(window_, event_);
        }
    }

    void Program::update(sf::Clock& timer) {
        if (  game_->isStarted()
            ) game_->update(event_, timer.getElapsedTime());
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
