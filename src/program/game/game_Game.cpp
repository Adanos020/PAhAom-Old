/**
 * @file src/program/game/game_Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "game.hpp"
#include "../program.hpp"
#include "../funcs/keys.hpp"

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

extern rr::Settings settings;
extern rr::Subject  subject;
extern sf::Color    itemColors[9];
extern int          spellSymbols[11];

namespace rr {

    Game::Game()
        : mainMenu_      (new MainMenu      ()),
          pauseMenu_     (new PauseMenu     ()),
          attributes_    (new Attributes    ()),
          inventory_     (new Inventory     ()),
          quests_        (new Quests        ()),
          gameMap_       (new GameMap       ()),
          bookOfSpells_  (new BookOfSpells  ()),
          hud_           (new HUD           ()),
          messageManager_(new MessageManager()),
          player_        (new Player        ()),
          started_       (false),
          paused_        (false),
          levelNumber_   (0) {

        gameView_.setSize((sf::Vector2f)settings.graphics.resolution);
        mapView_ .setSize(6160.f, 3440.f);
        mapView_ .setCenter(mapView_.getSize()/2.f);
        mapView_ .setViewport(sf::FloatRect(0.115f, 0.1275f, 0.77f, 0.745f));

        subject.addObserver(inventory_);
        subject.addObserver(messageManager_);
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
        levels_.clear();
    }

    void Game::randomizeItems() {
        /* colors */ {
            int pot[9];
            for (int i=0; i<9; i++) {
                hell: int x = rand()%9;
                for (int j=0; j<i; j++) {
                    if (pot[j] == x)
                        goto hell;
                }
                pot[i] = x;
                switch (x) {
                    case 0: itemColors[i] = sf::Color::Red          ; break;
                    case 1: itemColors[i] = sf::Color::Blue         ; break;
                    case 2: itemColors[i] = sf::Color(32, 32, 0)    ; break;
                    case 3: itemColors[i] = sf::Color::Green        ; break;
                    case 4: itemColors[i] = sf::Color::Cyan         ; break;
                    case 5: itemColors[i] = sf::Color(255, 172, 172); break;
                    case 6: itemColors[i] = sf::Color::Magenta      ; break;
                    case 7: itemColors[i] = sf::Color::Yellow       ; break;
                    case 8: itemColors[i] = sf::Color::White        ; break;
                }
            }
        }
        /* Rune symbols */ {
            for (int i=0; i<11; i++) {
                topkek: int x = rand()%11;
                for (int j=0; j<i; j++) {
                    if (spellSymbols[j] == x)
                        goto topkek;
                }
                spellSymbols[i] = x;
            }
        }
    }

    void Game::switchLevel(int index) {
        if (index > (int)levelNumber_) {
            if (levelNumber_ < levels_.size()-1)
                levelNumber_++;
            else
                levelNumber_ = 0;
            player_->setPosition(levels_[levelNumber_]->getStartingPoint());
        }
        else if (index < (int)levelNumber_) {
            if (levelNumber_ > 0)
                levelNumber_--;
            else
                levelNumber_ = levels_.size()-1;
            player_->setPosition(levels_[levelNumber_]->getEndingPoint());
        }
        messageManager_->addMessage(Message("Welcome to level "+std::to_string(levelNumber_+1)+"!", sf::Color::Green));
    }

    bool Game::loadNewGame() {
        reset();
        for (int i=0; i<30; i++) {
            levels_.push_back(new Level(i));
            levels_.back()->generateWorld();
            subject.addObserver(levels_.back());

            levelFOV_.push_back(new FOV(levels_[i]->masks_, levels_[i]->tilesAsInts_));
        }
        player_->setPosition(levels_[0]->getStartingPoint());
        start(true);
        pause(false);
        return true;
    }

    void Game::save() {
        std::ofstream file("data/savedgame/save.pah", std::ios::binary);
        file.write((char*)this, sizeof(*this));
    }

    bool Game::load() {
        std::ifstream file("data/savedgame/save.pah", std::ios::binary);
        return file.read((char*)this, sizeof(*this)).good();
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!started_) {
            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            mainMenu_->draw(rw);
            rw.setView(gameView_);
        } else {
            rw.setView(gameView_);
            rw.draw(*levels_[levelNumber_]);
            levels_[levelNumber_]->drawObjects(rw);
            player_->draw(rw);

            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            hud_           ->draw(rw);
            messageManager_->draw(rw);
            inventory_     ->draw(rw);
            pauseMenu_     ->draw(rw);
            attributes_    ->draw(rw);
            quests_        ->draw(rw);
            gameMap_       ->draw(rw);
            bookOfSpells_  ->draw(rw);

            if (gameMap_   ->isOpen()) {
                rw.setView(mapView_);
                rw.draw(*levels_[levelNumber_]);
                levels_[levelNumber_]->drawObjects(rw);
                player_->draw(rw);
            }
        }
    }

    void Game::update(sf::Event& event, float timer) {
        controls(event);

        player_        ->update(timer);
        hud_           ->update(player_, levelNumber_+1);
        messageManager_->update(timer);

        gameView_.setCenter(sf::Vector2f(player_->getBounds().left+16, player_->getBounds().top+16));

        if (!paused_) {
            for (auto entity : levels_[levelNumber_]->getEntities()) {
                if (instanceof<Door, Entity>(entity)) {
                    if (player_->intersects(entity)
                        ) ((Door*)entity)->setOpen(true);
                    else
                        ((Door*)entity)->setOpen(false);
                }
                else if (instanceof<NPC, Entity>(entity)
                         ) ((NPC*)entity)->update(timer);
            }
        }

        for (int i=0; i<77*43; i++) {
            levels_[levelNumber_]->getMasks()[i].see(false);
        }
        levelFOV_[levelNumber_]->compute((sf::Vector2u)player_->getPosition(), player_->getSightRange());

        for (int i=0; i<77; i++) {
            for (int j=0; j<43; j++) {
                if (levels_[levelNumber_]->getMasks()[i + j*77].isSeen()) {
                    bool light[] = { false, false, false, false };

                    if (levels_[levelNumber_]->getMasks()[i-1 + (j-1)*77].isSeen()
                        ) light[0] = true;
                    if (levels_[levelNumber_]->getMasks()[i+1 + (j-1)*77].isSeen()
                        ) light[1] = true;
                    if (levels_[levelNumber_]->getMasks()[i+1 + (j+1)*77].isSeen()
                        ) light[2] = true;
                    if (levels_[levelNumber_]->getMasks()[i-1 + (j+1)*77].isSeen()
                        ) light[3] = true;

                    if (levels_[levelNumber_]->getMasks()[i-1 + ( j )*77].isSeen()
                        ) { light[0] = true; light[3] = true; }
                    if (levels_[levelNumber_]->getMasks()[i+1 + ( j )*77].isSeen()
                        ) { light[1] = true; light[2] = true; }
                    if (levels_[levelNumber_]->getMasks()[ i  + (j-1)*77].isSeen()
                        ) { light[0] = true; light[1] = true; }
                    if (levels_[levelNumber_]->getMasks()[ i  + (j+1)*77].isSeen()
                        ) { light[3] = true; light[2] = true; }

                    if (!levels_[levelNumber_]->getMasks()[i-1 + ( j )*77].isSeen()
                        ) { light[0] = false; light[3] = false; }
                    if (!levels_[levelNumber_]->getMasks()[i+1 + ( j )*77].isSeen()
                        ) { light[1] = false; light[2] = false; }
                    if (!levels_[levelNumber_]->getMasks()[ i  + (j-1)*77].isSeen()
                        ) { light[0] = false; light[1] = false; }
                    if (!levels_[levelNumber_]->getMasks()[ i  + (j+1)*77].isSeen()
                        ) { light[3] = false; light[2] = false; }

                    if (!levels_[levelNumber_]->getMasks()[i-1 + (j-1)*77].isSeen()
                        ) light[0] = false;
                    if (!levels_[levelNumber_]->getMasks()[i+1 + (j-1)*77].isSeen()
                        ) light[1] = false;
                    if (!levels_[levelNumber_]->getMasks()[i+1 + (j+1)*77].isSeen()
                        ) light[2] = false;
                    if (!levels_[levelNumber_]->getMasks()[i-1 + (j+1)*77].isSeen()
                        ) light[3] = false;

                    levels_[levelNumber_]->getMasks()[i + j*77].setFadeOut(light, sf::Color(0, 0, 0, 160));
                }
            }
        }
    }

    void Game::controls(sf::Event& event) {
        if (started_ && !paused_) {
            if (isKeyPressed(settings.keys.move_up))    player_->move(levels_[levelNumber_]->getTiles(), Player::UP);
            if (isKeyPressed(settings.keys.move_down))  player_->move(levels_[levelNumber_]->getTiles(), Player::DOWN);
            if (isKeyPressed(settings.keys.move_left))  player_->move(levels_[levelNumber_]->getTiles(), Player::LEFT);
            if (isKeyPressed(settings.keys.move_right)) player_->move(levels_[levelNumber_]->getTiles(), Player::RIGHT);

            /*     if (isKeyPressed(sf::Keyboard::Numpad1)) player_->attrs_.health    --;
            else if (isKeyPressed(sf::Keyboard::Numpad2)) player_->attrs_.health    ++;
            else if (isKeyPressed(sf::Keyboard::Numpad3)) player_->attrs_.mana      --;
            else if (isKeyPressed(sf::Keyboard::Numpad4)) player_->attrs_.mana      ++;
            else if (isKeyPressed(sf::Keyboard::Numpad5)) player_->attrs_.experience++;
            else if (isKeyPressed(sf::Keyboard::Numpad6)) player_->attrs_.level     ++;*/
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& event) {
        if (       !started_       ) mainMenu_    ->buttonEvents(rw, event, this);
        if (pauseMenu_   ->isOpen()) pauseMenu_   ->buttonEvents(rw, event, this);
        if (inventory_   ->isOpen()) inventory_   ->buttonEvents(rw, event, this);
        if (attributes_  ->isOpen()) attributes_  ->buttonEvents(rw, event, this);
        if (quests_      ->isOpen()) quests_      ->buttonEvents(rw, event, this);
        if (gameMap_     ->isOpen()) gameMap_     ->buttonEvents(rw, event, this);
        if (bookOfSpells_->isOpen()) bookOfSpells_->buttonEvents(rw, event, this);

        if (started_) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
                switchLevel(levelNumber_+1);
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
                switchLevel(levelNumber_-1);

            if (wasKeyPressed(event, sf::Keyboard::Escape))
                pause(!isPaused());
            if (!paused_) {
                if (wasKeyPressed(event, settings.keys.open_attributes)) {
                    attributes_->update(player_);
                    attributes_->open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, settings.keys.open_inventory)) {
                    inventory_->open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, settings.keys.open_map)) {
                    gameMap_->open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, settings.keys.open_quests)) {
                    quests_->open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, settings.keys.open_bookOfSpells)) {
                    bookOfSpells_->open();
                    paused_ = true;
                }

                else if (wasKeyPressed(event, settings.keys.attack)) {

                }
                else if (wasKeyPressed(event, settings.keys.interact)) {

#define entities levels_[levelNumber_]->getEntities()

                    for (unsigned i=0; i<entities.size(); i++) {
                        if (player_->getPosition() == entities[i]->getPosition()) {
                            if (instanceof<Item, Entity>(entities[i])) {
                                if (inventory_->addItem((Item*)entities[i])) {
                                    subject.notify(Observer::ITEM_PICKED, entities[i]);
                                    levels_[levelNumber_]->removeEntity(i);
                                    i = 0;
                                }
                                else
                                    std::cout << "Your backpack is too full to take " << ((Item*)entities[i])->getAmount() << "x " << ((Item*)entities[i])->getName().toAnsiString() << "!\n";
                            }
                            else if (instanceof<Chest, Entity>(entities[i])) {
                                // TODO - MAKE THIS SHIT NOT CRASH THE FUCKING GAME
                                /*
                                levels_[levelNumber_]->addEntity(entities[i]->getItem(), entities[i]->getPosition());
                                levels_[levelNumber_]->removeEntity(i);
                                i = 0;
                                */
                            }
                            else if (instanceof<Stairs, Entity>(entities[i])) {
                                if (((Stairs*)entities[i])->isUpwards() != 0) {
                                    switchLevel(levelNumber_+1);
                                    break;
                                }
                                else {
                                    switchLevel(levelNumber_-1);
                                    break;
                                }
                            }
                        }
                    }

#undef entities

                }

                if      (wasKeyPressed(event, settings.keys.useslot_1)) {}
                else if (wasKeyPressed(event, settings.keys.useslot_2)) {}
                else if (wasKeyPressed(event, settings.keys.useslot_3)) {}
                else if (wasKeyPressed(event, settings.keys.useslot_4)) {}
                else if (wasKeyPressed(event, settings.keys.useslot_5)) {}
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
            pauseMenu_   ->close();
            inventory_   ->close();
            attributes_  ->close();
            quests_      ->close();
            gameMap_     ->close();
            bookOfSpells_->close();
        }
    }

    void Game::reset() {
        randomizeItems();
        levels_.clear();
        levelFOV_.clear();
        inventory_->clear();
        player_->reset();
        levelNumber_ = 0;
    }

}
