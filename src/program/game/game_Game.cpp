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
        _mainMenu   = new MainMenu();
        _pauseMenu  = new PauseMenu();
        _attributes = new Attributes();
        _inventory  = new Inventory();
        _quests     = new Quests();
        _gameMap    = new GameMap();
        _hud        = new HUD();
        _player     = new Player();

        _gameView.setSize((sf::Vector2f)settings.graphics.resolution);
        _mapView .setSize(6160.f, 3440.f);
        _mapView .setCenter(_mapView.getSize()/2.f);
        _mapView .setViewport(sf::FloatRect(0.115f, 0.1275f, 0.77f, 0.745f));

        _paused      = false;
        _started     = false;
        _levelNumber = 0;
    }

    Game::~Game() {
        delete _mainMenu;
        delete _pauseMenu;
        delete _attributes;
        delete _inventory;
        delete _quests;
        delete _gameMap;
        delete _hud;
        delete _player;
    }

    void Game::controls() {
        if (_started && !_paused) {

#define keyPressed(key) sf::Keyboard::isKeyPressed(key)
#define key sf::Keyboard

            if (keyPressed(settings.keys.move_up))    _player->move(_level[_levelNumber]->getTiles(), Player::UP);
            if (keyPressed(settings.keys.move_down))  _player->move(_level[_levelNumber]->getTiles(), Player::DOWN);
            if (keyPressed(settings.keys.move_left))  _player->move(_level[_levelNumber]->getTiles(), Player::LEFT);
            if (keyPressed(settings.keys.move_right)) _player->move(_level[_levelNumber]->getTiles(), Player::RIGHT);

            if      (keyPressed(settings.keys.open_attributes)) {
                _attributes->update(_player);
                _attributes->open();
                _paused = true;
            }
            else if (keyPressed(settings.keys.open_inventory)) {
                _inventory->open();
                _paused = true;
            }
            else if (keyPressed(settings.keys.open_map)) {
                _gameMap->open();
                _paused = true;
            }
            else if (keyPressed(settings.keys.open_quests)) {
                _quests->open();
                _paused = true;
            }

            else if (keyPressed(settings.keys.attack)) {

            }
            else if (keyPressed(settings.keys.interact)) {

            }

            if      (keyPressed(settings.keys.useslot_1)) {}
            else if (keyPressed(settings.keys.useslot_2)) {}
            else if (keyPressed(settings.keys.useslot_3)) {}
            else if (keyPressed(settings.keys.useslot_4)) {}
            else if (keyPressed(settings.keys.useslot_5)) {}

            else if (keyPressed(key::Numpad1)) _player->_attrs.health    --;
            else if (keyPressed(key::Numpad2)) _player->_attrs.health    ++;
            else if (keyPressed(key::Numpad3)) _player->_attrs.mana      --;
            else if (keyPressed(key::Numpad4)) _player->_attrs.mana      ++;
            else if (keyPressed(key::Numpad5)) _player->_attrs.experience++;
            else if (keyPressed(key::Numpad6)) _player->_attrs.level     ++;

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
                case 0: potionColors[i] = sf::Color::Red;           break;
                case 1: potionColors[i] = sf::Color::Blue;          break;
                case 2: potionColors[i] = sf::Color(32, 32, 0);     break;
                case 3: potionColors[i] = sf::Color::Green;         break;
                case 4: potionColors[i] = sf::Color(128, 128, 128); break;
                case 5: potionColors[i] = sf::Color(255, 172, 172); break;
                case 6: potionColors[i] = sf::Color::Magenta;       break;
                case 7: potionColors[i] = sf::Color::Yellow;        break;
                case 8: potionColors[i] = sf::Color::White;         break;
                }
            }
        }
    }

    bool Game::load() {
        for (int i=0; i<25; i++) {
            _level.push_back(new Level());
            if (!_level.back()->loadFromFile("data/savedgame/"))
                return false;
        }
        return true;
    }

    bool Game::loadNewGame() {
        randomizeItems();
        for (int i=0; i<25; i++) {
            _level.push_back(new Level());
            _level.back()->generateWorld();
        }
        _player->setPosition(_level[0]->getStartingPoint());
        start(true);
        pause(false);
        return true;
    }

    void Game::save() {
        // there's nothing to save yet
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!_started) {
            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            _mainMenu->draw(rw);
            rw.setView(_gameView);
        } else {
            rw.setView(_gameView);
            rw.draw(*_level[_levelNumber]);
            _level[_levelNumber]->drawObjects(rw);
            _player->draw(rw);

            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            _hud->draw(rw);
            if (_pauseMenu ->isOpen())
                _pauseMenu ->draw(rw);
            if (_attributes->isOpen())
                _attributes->draw(rw);
            if (_inventory ->isOpen())
                _inventory ->draw(rw);
            if (_quests    ->isOpen())
                _quests    ->draw(rw);
            if (_gameMap   ->isOpen()) {
                _gameMap   ->draw(rw);
                rw.setView(_mapView);
                rw.draw(*_level[_levelNumber]);
                _level[_levelNumber]->drawObjects(rw);
                _player->draw(rw);
            }
        }
    }

    void Game::update(float timer) {
        controls();

        _player->update(timer);
        _hud   ->update(_player);

        _gameView.setCenter(sf::Vector2f(_player->getBounds().left+16, _player->getBounds().top+16));
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        if (!_started)
            _mainMenu ->buttonEvents(rw, e, this);
        if (_pauseMenu->isOpen())
            _pauseMenu->buttonEvents(rw, e, this);
        if (_inventory->isOpen()) {
            _inventory->buttonEvents(rw, e, this);
            _hud      ->buttonEvents(rw, e);
        }
        if (_attributes->isOpen())
            _attributes->buttonEvents(rw, e, this);
        if (_quests    ->isOpen())
            _quests    ->buttonEvents(rw, e, this);
        if (_gameMap   ->isOpen())
            _gameMap   ->buttonEvents(rw, e, this);

        if (_started) {
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Add) {
                if (_levelNumber<_level.size()-1)
                    _levelNumber++;
                else
                    _levelNumber = 0;
                _player->setPosition(_level[_levelNumber]->getStartingPoint());
            }
            else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Subtract) {
                if (_levelNumber>0)
                    _levelNumber--;
                else
                    _levelNumber = _level.size()-1;
                _player->setPosition(_level[_levelNumber]->getEndingPoint());
            }
        }
    }

    void Game::start(bool b) {
        _started = b;
    }

    void Game::pause(bool b) {
        _paused = b;
        if (_paused)
            _pauseMenu->open();
        else {
            _pauseMenu ->close();
            _inventory ->close();
            _attributes->close();
            _quests    ->close();
            _gameMap   ->close();
        }
    }

    bool Game::isStarted() {
        return _started;
    }

    bool Game::isPaused() {
        return _paused;
    }

}
