#include "game.h"

namespace rr {

    Game::Game(sf::RenderWindow& rw) {
        mainMenu = new MainMenu(rw);
        pauseMenu = new PauseMenu(rw);
        player = new Player(sf::Vector2f(10, 10));

        paused = started = false;
    }

    Game::~Game() {
        delete mainMenu;
        delete pauseMenu;
    }

    void Game::draw(sf::RenderWindow& rw, sf::View& v) {
        if (!started) mainMenu->draw(rw, v);
        else {
            player->draw(rw);
            if (paused) pauseMenu->draw(rw, v);
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::View& v) {
        if (!started) mainMenu->buttonEvents(rw, this);
        if (paused) pauseMenu->buttonEvents(rw, this);
    }

    void Game::controls(clock_t timer) {
        if (started && !paused) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) pause(true);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player->go((double)timer, Player::up);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player->go((double)timer, Player::down);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player->go((double)timer, Player::left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player->go((double)timer, Player::right);
        }
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
