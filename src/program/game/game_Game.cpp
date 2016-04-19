/**
 * @file src/program/game/game_Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

extern rr::Settings settings;
extern sf::Color    potionColors[9];

namespace rr {

    Game::Game() {
        gameView.setSize((sf::Vector2f)settings.graphics.resolution);
        mapView .setSize(3520*((float)settings.graphics.resolution.x/(float)settings.graphics.resolution.y), 3520);
        mapView .setCenter(mapView.getSize()/2.f);
        mapView .setViewport(sf::FloatRect(0.125f, 0.125f, 0.75f, 0.75f));

        mainMenu    = new MainMenu  ();
        pauseMenu   = new PauseMenu ();
        attributes  = new Attributes();
        inventory   = new Inventory ();
        quests      = new Quests    ();
        gameMap     = new GameMap   ();
        hud         = new HUD       ();
        player      = new Player    (sf::Vector2f(mapView.getCenter()));

        paused      = false;
        started     = false;
        levelNumber = 0;
    }

    Game::~Game() {
        delete mainMenu;
        delete pauseMenu;
        delete attributes;
        delete inventory;
        delete quests;
        delete gameMap;
        delete hud;
        delete player;
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
                gameMap->open();
                paused = true;
            }
            else if (keyPressed(settings.keys.open_quests)) {
                quests->open();
                paused = true;
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

    void Game::randomizeItems() {
    // potions
        {
            int pot[9];
            for (int i=0; i<9; i++) {
            hell:
                int x = rand()%9;
                for (int j=0; j<i; j++) {
                    if (pot[j] == x)
                        goto hell; // Literally, you fucking elitists
                }
                pot[i] = x;
                switch (x) {
                case 0:
                    potionColors[i] = sf::Color::Red;
                    break;
                case 1:
                    potionColors[i] = sf::Color::Blue;
                    break;
                case 2:
                    potionColors[i] = sf::Color(32, 32, 0);
                    break;
                case 3:
                    potionColors[i] = sf::Color::Green;
                    break;
                case 4:
                    potionColors[i] = sf::Color(128, 128, 128);
                    break;
                case 5:
                    potionColors[i] = sf::Color(255, 172, 172);
                    break;
                case 6:
                    potionColors[i] = sf::Color::Magenta;
                    break;
                case 7:
                    potionColors[i] = sf::Color::Black;
                    break;
                case 8:
                    potionColors[i] = sf::Color::White;
                    break;
                }
            }
        }
    }

    bool Game::load() {
        for (int l=0; l<25; l++) {
            level[l] = new Level();
            level[l]->loadFromFile("data/savedgame/");
        }
        return true;
    }

    bool Game::loadNewGame() {
        randomizeItems();
        for (int l=0; l<25; l++) {
            level[l] = new Level();
            level[l]->generateWorld();
        }
        start(true);
        pause(false);
        return true;
    }

    void Game::save() {
        // there's nothing to save yet
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!started) {
            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            mainMenu->draw(rw);
            rw.setView(gameView);
        } else {
            rw.setView(gameView);
            rw.draw(*level[levelNumber]);
            level[levelNumber]->drawObjects(rw);
            player->draw(rw);

            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            hud->draw(rw);
            if (pauseMenu ->isOpen())
                pauseMenu ->draw(rw);
            if (attributes->isOpen())
                attributes->draw(rw);
            if (inventory ->isOpen())
                inventory ->draw(rw);
            if (quests    ->isOpen())
                quests    ->draw(rw);
            if (gameMap   ->isOpen()) {
                gameMap   ->draw(rw);
                rw.setView(mapView);
                rw.draw(*level[levelNumber]);
                level[levelNumber]->drawObjects(rw);
                player->draw(rw);
            }
        }
    }

    void Game::update(float timer) {
        controls(timer);

        player->update();
        hud   ->update(player);

        gameView.setCenter(player->getPosition()+sf::Vector2f(16, 16));
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        if (!started)
            mainMenu ->buttonEvents(rw, e, this);
        if (pauseMenu->isOpen())
            pauseMenu->buttonEvents(rw, e, this);
        if (inventory->isOpen()) {
            inventory->buttonEvents(rw, e, this);
            hud      ->buttonEvents(rw, e);
        }
        if (attributes->isOpen())
            attributes->buttonEvents(rw, e, this);
        if (quests    ->isOpen())
            quests    ->buttonEvents(rw, e, this);
        if (gameMap   ->isOpen())
            gameMap   ->buttonEvents(rw, e, this);
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
            quests    ->close();
            gameMap   ->close();
        }
    }

    bool Game::isStarted() {
        return started;
    }

    bool Game::isPaused() {
        return paused;
    }

}
