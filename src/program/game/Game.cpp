#include "game.h"

namespace rr {

    Game::Game(sf::RenderWindow& rw) {
        mainMenu = new MainMenu(rw);
        pauseMenu = new PauseMenu(rw);
        hud = new HUD(rw);
        player = new Player((sf::Vector2f)(rw.getSize()/2u));

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
        if (!started) mainMenu->draw(rw, v);
        else {
            player->draw(rw);
            if (paused)
                pauseMenu->draw(rw, v);
            else
                hud->draw(rw, v);
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::View& v) {
        if (!started) mainMenu->buttonEvents(rw, this);
        if (paused) pauseMenu->buttonEvents(rw, this);
    }

    void Game::controls(float timer) {
        if (started && !paused) {
            #define keyPressed(key) sf::Keyboard::isKeyPressed(key)
            #define key sf::Keyboard
            if (keyPressed(key::Escape)) pause(true);

            if (keyPressed(key::Up)) player->go(timer, Player::up);
            if (keyPressed(key::Down)) player->go(timer, Player::down);
            if (keyPressed(key::Left)) player->go(timer, Player::left);
            if (keyPressed(key::Right)) player->go(timer, Player::right);

            if (keyPressed(key::Q)) player->stats.hp--;
            if (keyPressed(key::W)) player->stats.hp++;
            if (keyPressed(key::E)) player->stats.mp--;
            if (keyPressed(key::R)) player->stats.mp++;
            if (keyPressed(key::T)) player->stats.exp++;
            if (keyPressed(key::Y)) player->stats.lvl++;
            #undef keyPressed
            #undef key
        }
    }

    void Game::update(float timer) {
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

    }

    bool Game::load() {
        return true;
    }

    bool Game::loadNewGame() {
        return true;
    }

    bool Game::isStarted() {
        return started;
    }

    bool Game::isPaused() {
        return paused;
    }

}
