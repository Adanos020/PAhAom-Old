/**
 * @file src/program/game/game_Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"
#include "../program.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

extern rr::Settings settings;
extern sf::Color    potionColors[9];

namespace rr {

    Game::Game() {
        mainMenu_   = new MainMenu();
        pauseMenu_  = new PauseMenu();
        attributes_ = new Attributes();
        inventory_  = new Inventory();
        quests_     = new Quests();
        gameMap_    = new GameMap();
        hud_        = new HUD();
        player_     = new Player();

        gameView_.setSize((sf::Vector2f)settings.graphics.resolution);
        mapView_ .setSize(6160.f, 3440.f);
        mapView_ .setCenter(mapView_.getSize()/2.f);
        mapView_ .setViewport(sf::FloatRect(0.115f, 0.1275f, 0.77f, 0.745f));

        paused_      = false;
        started_     = false;
        levelNumber_ = 0;
    }

    Game::~Game() {
        delete mainMenu_;
        delete pauseMenu_;
        delete attributes_;
        delete inventory_;
        delete quests_;
        delete gameMap_;
        delete hud_;
        delete player_;
    }

    void Game::controls() {
        if (started_ && !paused_) {

#define keyPressed(key) sf::Keyboard::isKeyPressed(key)
#define key sf::Keyboard

            if (keyPressed(settings.keys.move_up))    player_->move(level_[levelNumber_]->getTiles(), Player::UP);
            if (keyPressed(settings.keys.move_down))  player_->move(level_[levelNumber_]->getTiles(), Player::DOWN);
            if (keyPressed(settings.keys.move_left))  player_->move(level_[levelNumber_]->getTiles(), Player::LEFT);
            if (keyPressed(settings.keys.move_right)) player_->move(level_[levelNumber_]->getTiles(), Player::RIGHT);

            if      (keyPressed(settings.keys.open_attributes)) {
                attributes_->update(player_);
                attributes_->open();
                paused_ = true;
            }
            else if (keyPressed(settings.keys.open_inventory)) {
                inventory_->open();
                paused_ = true;
            }
            else if (keyPressed(settings.keys.open_map)) {
                gameMap_->open();
                paused_ = true;
            }
            else if (keyPressed(settings.keys.open_quests)) {
                quests_->open();
                paused_ = true;
            }

            else if (keyPressed(settings.keys.attack)) {

            }
            else if (keyPressed(settings.keys.interact)) {

#define entities level_[levelNumber_]->getEntities()

                for (unsigned i=0; i<entities.size(); i++) {
                    if (player_->intersects(entities[i])) {
                        if (instanceof<Item, Entity>(entities[i]) && inventory_->addItem((Item*)entities[i])) {
                            level_[levelNumber_]->removeEntity(i);
                            i = 0;
                        }
                        else if (instanceof<Chest, Entity>(entities[i])) {

                        }
                    }
                }

#undef entities

            }

            if      (keyPressed(settings.keys.useslot_1)) {}
            else if (keyPressed(settings.keys.useslot_2)) {}
            else if (keyPressed(settings.keys.useslot_3)) {}
            else if (keyPressed(settings.keys.useslot_4)) {}
            else if (keyPressed(settings.keys.useslot_5)) {}

            else if (keyPressed(key::Numpad1)) player_->attrs_.health    --;
            else if (keyPressed(key::Numpad2)) player_->attrs_.health    ++;
            else if (keyPressed(key::Numpad3)) player_->attrs_.mana      --;
            else if (keyPressed(key::Numpad4)) player_->attrs_.mana      ++;
            else if (keyPressed(key::Numpad5)) player_->attrs_.experience++;
            else if (keyPressed(key::Numpad6)) player_->attrs_.level     ++;

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
                case 0: potionColors[i] = sf::Color::Red          ; break;
                case 1: potionColors[i] = sf::Color::Blue         ; break;
                case 2: potionColors[i] = sf::Color(32, 32, 0)    ; break;
                case 3: potionColors[i] = sf::Color::Green        ; break;
                case 4: potionColors[i] = sf::Color::Cyan         ; break;
                case 5: potionColors[i] = sf::Color(255, 172, 172); break;
                case 6: potionColors[i] = sf::Color::Magenta      ; break;
                case 7: potionColors[i] = sf::Color::Yellow       ; break;
                case 8: potionColors[i] = sf::Color::White        ; break;
                }
            }
        }
    }

    bool Game::load() {
        for (int i=0; i<25; i++) {
            level_.push_back(new Level());
            if (!level_.back()->loadFromFile("data/savedgame/"))
                return false;
        }
        return true;
    }

    bool Game::loadNewGame() {
        randomizeItems();
        for (int i=0; i<25; i++) {
            level_.push_back(new Level());
            level_.back()->generateWorld();
        }
        player_->setPosition(level_[0]->getStartingPoint());
        start(true);
        pause(false);
        return true;
    }

    void Game::save() {
        // there's nothing to save yet
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!started_) {
            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            mainMenu_->draw(rw);
            rw.setView(gameView_);
        } else {
            rw.setView(gameView_);
            rw.draw(*level_[levelNumber_]);
            level_[levelNumber_]->drawObjects(rw);
            player_->draw(rw);

            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            hud_->draw(rw);
            if (pauseMenu_ ->isOpen())
                pauseMenu_ ->draw(rw);
            if (attributes_->isOpen())
                attributes_->draw(rw);
            if (inventory_ ->isOpen())
                inventory_ ->draw(rw);
            if (quests_    ->isOpen())
                quests_    ->draw(rw);
            if (gameMap_   ->isOpen()) {
                gameMap_   ->draw(rw);
                rw.setView(mapView_);
                rw.draw(*level_[levelNumber_]);
                level_[levelNumber_]->drawObjects(rw);
                player_->draw(rw);
            }
        }
    }

    void Game::update(float timer) {
        controls();

        player_->update(timer);
        hud_   ->update(player_);

        gameView_.setCenter(sf::Vector2f(player_->getBounds().left+16, player_->getBounds().top+16));

        for (auto x : level_[levelNumber_]->getEntities()) {
            if (instanceof<Door, Entity>(x)) {
                if (player_->intersects(x))
                    x->setOpen(true);
                else
                    x->setOpen(false);
            }
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        if (!started_)
            mainMenu_ ->buttonEvents(rw, e, this);
        if (pauseMenu_->isOpen())
            pauseMenu_->buttonEvents(rw, e, this);
        if (inventory_->isOpen()) {
            inventory_->buttonEvents(rw, e, this);
            hud_      ->buttonEvents(rw, e);
        }
        if (attributes_->isOpen())
            attributes_->buttonEvents(rw, e, this);
        if (quests_    ->isOpen())
            quests_    ->buttonEvents(rw, e, this);
        if (gameMap_   ->isOpen())
            gameMap_   ->buttonEvents(rw, e, this);

        if (started_) {
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Add) {
                if (levelNumber_<level_.size()-1)
                    levelNumber_++;
                else
                    levelNumber_ = 0;
                player_->setPosition(level_[levelNumber_]->getStartingPoint());
            }
            else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Subtract) {
                if (levelNumber_>0)
                    levelNumber_--;
                else
                    levelNumber_ = level_.size()-1;
                player_->setPosition(level_[levelNumber_]->getEndingPoint());
            }
        }
    }

    void Game::start(bool b) {
        started_ = b;
    }

    void Game::pause(bool b) {
        paused_ = b;
        if (paused_)
            pauseMenu_->open();
        else {
            pauseMenu_ ->close();
            inventory_ ->close();
            attributes_->close();
            quests_    ->close();
            gameMap_   ->close();
        }
    }

    bool Game::isStarted() {
        return started_;
    }

    bool Game::isPaused() {
        return paused_;
    }

}
