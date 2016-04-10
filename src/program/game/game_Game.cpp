/**
 * @file src/program/game/Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "game.hpp"

#include <iostream>

extern rr::Settings settings;

namespace rr {

    Game::Game(sf::RenderWindow& rw) {
        mainMenu   = new MainMenu(rw);
        pauseMenu  = new PauseMenu(rw);
        attributes = new Attributes(rw);
        inventory  = new Inventory(rw);
        hud        = new HUD(rw);
        player     = new Player(sf::Vector2f(0, 0));

        potions.push_back(new Potion(Potion::Effect::HEALING, Potion::Size::BIG, 1, sf::Vector2f(200, 200)));
        potions.push_back(new Potion(Potion::Effect::DEXTERITY, Potion::Size::MEDIUM, 1, sf::Vector2f(400, 200)));
        potions.push_back(new Potion(Potion::Effect::POISON, Potion::Size::SMALL, 1, sf::Vector2f(600, 200)));

        paused = false;
        started = false;
    }

    Game::~Game() {
        delete mainMenu;
        delete pauseMenu;
        delete hud;
        delete player;
    }

    void Game::draw(sf::RenderWindow& rw, sf::View& v) {
        if (!started) {
            rw.setView(rw.getDefaultView());
            mainMenu->draw(rw);
            rw.setView(v);
        } else {
            for (auto x : potions)
                x->draw(rw);
            player->draw(rw);

            rw.setView(rw.getDefaultView());
            hud->draw(rw);
            if (pauseMenu ->isOpen())
                pauseMenu ->draw(rw);
            if (attributes->isOpen())
                attributes->draw(rw);
            if (inventory ->isOpen())
                inventory ->draw(rw);
            rw.setView(v);
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::View& v) {
        if (!started) mainMenu->buttonEvents(rw, this);
        if (pauseMenu->isOpen())
            pauseMenu->buttonEvents(rw, this);
        if (inventory->isOpen()) {
            inventory->buttonEvents(rw, this);
            hud      ->buttonEvents(rw);
        }
        if (attributes->isOpen())
            attributes->buttonEvents(rw, this);
    }

    void Game::controls(float timer) {
        if (started && !paused) {
#define keyPressed(key) sf::Keyboard::isKeyPressed(key)
#define key sf::Keyboard
            if (keyPressed(key::Escape)) {
                pauseMenu->open();
                pause(true);
            }

            if (keyPressed(settings.keys.move_up))    player->go(timer, Player::UP);
            if (keyPressed(settings.keys.move_down))  player->go(timer, Player::DOWN);
            if (keyPressed(settings.keys.move_left))  player->go(timer, Player::LEFT);
            if (keyPressed(settings.keys.move_right)) player->go(timer, Player::RIGHT);

            if      (keyPressed(settings.keys.open_attributes)) {
                attributes->update(player);
                attributes->open();
                pause(true);
            }
            else if (keyPressed(settings.keys.open_inventory)) {
                inventory->open();
                pause(true);
            }
            else if (keyPressed(settings.keys.open_map)) {

            }
            else if (keyPressed(settings.keys.open_quests)) {

            }

            if      (keyPressed(settings.keys.useslot_1)) {}
            else if (keyPressed(settings.keys.useslot_2)) {}
            else if (keyPressed(settings.keys.useslot_3)) {}
            else if (keyPressed(settings.keys.useslot_4)) {}
            else if (keyPressed(settings.keys.useslot_5)) {}

            else if (keyPressed(key::Numpad1)) player->stats. hp--;
            else if (keyPressed(key::Numpad2)) player->stats. hp++;
            else if (keyPressed(key::Numpad3)) player->stats. mp--;
            else if (keyPressed(key::Numpad4)) player->stats. mp++;
            else if (keyPressed(key::Numpad5)) player->stats.exp++;
            else if (keyPressed(key::Numpad6)) player->stats.lvl++;
#undef keyPressed
#undef key
        }
    }

    void Game::update(float timer, sf::View& v) {
        v.setCenter(player->getPosition());
        hud->update(player);
        player->update();
        controls(timer);
    }

    void Game::start(bool b) {
        started = b;
    }

    void Game::pause(bool b) {
        paused = b;
    }

    void Game::save() {
        // there's nothing to save yet
    }

    bool Game::load() {
        // there's nothing to load yet, so we can just lie that the load is succeeded
        return true;
    }

    bool Game::loadNewGame() {
        // there's nothing to load yet, so we can just lie that the load is succeeded
        return true;
    }

    bool Game::isStarted() {
        return started;
    }

    bool Game::isPaused() {
        return paused;
    }

}
