/**
 * @file src/program/game/game_Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"

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

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& e, sf::View& v) {
        if (!started)
            mainMenu->buttonEvents(rw, e, this);
        if (pauseMenu->isOpen())
            pauseMenu->buttonEvents(rw, e, this);
        if (inventory->isOpen()) {
            inventory->buttonEvents(rw, e, this);
            hud      ->buttonEvents(rw, e);
        }
        if (attributes->isOpen())
            attributes->buttonEvents(rw, e, this);
    }

    void Game::controls(float timer) {
        if (started && !paused) {

#define keyPressed(key) sf::Keyboard::isKeyPressed(key)
#define key sf::Keyboard

            if (keyPressed(settings.keys.move_up))    player->move(timer, Player::UP);
            if (keyPressed(settings.keys.move_down))  player->move(timer, Player::DOWN);
            if (keyPressed(settings.keys.move_left))  player->move(timer, Player::LEFT);
            if (keyPressed(settings.keys.move_right)) player->move(timer, Player::RIGHT);

            if      (keyPressed(settings.keys.open_attributes)) {
                attributes->update(player);
                attributes->open();
                paused = true;
            }
            else if (keyPressed(settings.keys.open_inventory)) {
                inventory->open();
                paused = true;
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

            else if (keyPressed(key::Numpad1)) player->attrs.health    --;
            else if (keyPressed(key::Numpad2)) player->attrs.health    ++;
            else if (keyPressed(key::Numpad3)) player->attrs.mana      --;
            else if (keyPressed(key::Numpad4)) player->attrs.mana      ++;
            else if (keyPressed(key::Numpad5)) player->attrs.experience++;
            else if (keyPressed(key::Numpad6)) player->attrs.level     ++;

#undef keyPressed
#undef key

        }
    }

    void Game::update(float timer, sf::View& v) {
        controls(timer);
        player->update();
        hud->update(player);
        v.setCenter(player->getPosition());
    }

    void Game::start(bool b) {
        started = b;
    }

    void Game::pause(bool b) {
        paused = b;
        if (paused)
            pauseMenu->open();
        else {
            pauseMenu ->close();
            inventory ->close();
            attributes->close();
        }
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
