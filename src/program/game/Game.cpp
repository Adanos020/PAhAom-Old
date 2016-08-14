/**
 * @file src/program/game/Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Game.hpp"

#include "../Settings.hpp"
#include "../Resources.hpp"

#include "../observer/Observer.hpp"

#include "../funcs/keys.hpp"
#include "../funcs/files.hpp"

extern rr::Subject subject;
extern sf::Color   itemColors  [ 9];
extern int         spellSymbols[12];

namespace rr {

    Game::Game() :
      currentLevel_  (nullptr            ),
      inventory_     (Inventory(&player_)),
      started_       (false              ),
      paused_        (false              ),
      mapOpen_       (false              ),
      lost_          (false              ),
      levelNumber_   (0                  )
    {
        gameView_.setSize  ((sf::Vector2f) Settings::graphics.resolution);

        mapView_ .setSize  (6160.f, 3440.f);
        mapView_ .setCenter(mapView_.getSize()/2.f);

        subject.addObserver(&inventory_);
        subject.addObserver(&messageManager_);
    }

    Game::~Game() {
        delete currentLevel_;
    }

    void Game::randomizeItems() {
        /* colors */ {
            int pot[9];
            for (int i=0; i<9; ++i) {
                hell: pot[i] = rand()%9;
                for (int j=0; j<i; ++j) {
                    if (  pot[j] == pot[i]
                        ) goto hell;
                }
                switch (pot[i]) {
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
            for (int i=0; i<12; ++i) {
                topkek: spellSymbols[i] = rand()%12;
                for (int j=0; j<i; ++j) {
                    if (  spellSymbols[j] == spellSymbols[i]
                        ) goto topkek;
                }
            }
        }
    }

    void Game::switchLevel(int index) {
        {   std::ofstream file("save/level"+std::to_string(levelNumber_)+".pah");
            file.clear();
            *currentLevel_ >> file;
            file.close();   }

        bool ascending = false;
        if (index > (int)levelNumber_) {
            if (  levelNumber_ < 29
                ) levelNumber_++;
            else return;
            ascending = true;
        }
        else if (index < (int)levelNumber_) {
            if (  levelNumber_ > 0
                ) levelNumber_--;
            else return;
        }

        subject.removeObserver(currentLevel_);
        delete currentLevel_;

        currentLevel_ = new Level(levelNumber_);
        currentLevel_->generateWorld();
        subject.addObserver(currentLevel_);

        std::ifstream file("save/level"+std::to_string(levelNumber_)+".pah");
        *currentLevel_ << file;
        file.close();

        player_.setGridPosition((ascending) ? currentLevel_->getStartingPoint() : currentLevel_->getEndingPoint());

        currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());

        messageManager_.addMessage(Message(Resources::dictionary["message.welcome_to_level"]
                                          +" "
                                          +std::to_string(levelNumber_+1)
                                          +((Settings::game.language=="fc") ? "" : "!"), sf::Color::Green));

        save();
    }

    bool Game::loadNewGame() {
        reset();

        seed_ = time(0);
        srand(seed_);
        randomizeItems();

        std::ofstream file;

        for (int i=29; i>=0; --i) {
            currentLevel_ = new Level(i);
            currentLevel_->generateWorld();
            
            file.open("save/level"+std::to_string(i)+".pah");
            if (!file.good()) {
                system("mkdir save");
                file.open("save/level"+std::to_string(i)+".pah");
            }

            file.clear();
            *currentLevel_ >> file;
            file.close();

            if (  i!=0
                ) delete currentLevel_;
        }
        subject.addObserver(currentLevel_);

        player_.setGridPosition(currentLevel_->getStartingPoint());

        start(true);
        pause(false);

        currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());

        inventory_.addItem(new ColdWeapon(ColdWeapon::KNIFE));
        inventory_.addItem(new Food(Food::BAGUETTE));
        inventory_.addItem(new Potion(Potion::HEALING));

        return true;
    }

    bool Game::load() {
        reset();

        std::ifstream file("save/save.pah");

        if ( !file.good()
            ) return false;

        try {
            readFile <unsigned> (file, seed_       );
            readFile <unsigned> (file, levelNumber_);

            for (int i=0; i<9; ++i) {
                readFile <bool> (file, Potion::identified_[i]);
            }
            for (int i=0; i<12; ++i) {
                readFile <bool> (file, Rune  ::identified_[i]);
            }

            readEntity(file, &player_);

            srand(seed_);
            randomizeItems();

            inventory_ << file;
            if (file.fail()) {
                std::string wtf;
                file.close();
                file.clear();
                file.sync ();
                int pos = file.tellg();
                file >> wtf;
                throw std::invalid_argument("Wrong data in inventory: " + wtf + ", position: " + std::to_string(pos));
            }

            file.close();

            currentLevel_ = new Level(levelNumber_);
            
            file.open("save/level"+std::to_string(levelNumber_)+".pah");
            *currentLevel_ << file;
            file.close();

            subject.addObserver(currentLevel_);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        start(true);
        pause(false);

        currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());

        return true;
    }

    void Game::save() {
        std::ofstream file("save/save.pah");
        file.clear();
        
        file        << seed_        << '\n' 
                    << levelNumber_ << '\n';
        
        for (int i=0; i<9; ++i) {
            file << Potion::identified_[i] << ' ';
        }
        for (int i=0; i<12; ++i) {
            file << Rune  ::identified_[i] << ' ';
        }
        file << '\n';

        player_    >> file         << '\n';
        inventory_ >> file;

        file.close();

        file.open("save/level"+std::to_string(levelNumber_)+".pah");
        file.clear();

        *currentLevel_ >> file << ' ';

        file.close();
    }

    void Game::lose() {
        lost_ = true;

#if defined (__WINDOWS__) || defined (__TOS_WIN__) || defined (__WIN32__) || defined (_WIN64) || defined (_WIN32)
        system("del save/*pah");
#else
        system("rm -rf save/*.pah");
#endif
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!started_) {
            rw.setView(sf::View((sf::Vector2f) rw.getSize()/2.f, (sf::Vector2f) rw.getSize()));
            rw.draw(mainMenu_);
            rw.setView((mapOpen_) ? mapView_ : gameView_);
        }
        else {
            rw.setView((mapOpen_) ? mapView_ : gameView_);
            rw.draw(*currentLevel_);
            rw.draw(player_);

            rw.setView(sf::View((sf::Vector2f) rw.getSize()/2.f, (sf::Vector2f) rw.getSize()));

            messageManager_.draw(rw);

            rw.draw(hud_);
            rw.draw(attributes_);
            rw.draw(bookOfSpells_);
            rw.draw(deathScreen_);
            rw.draw(inventory_);
            rw.draw(journal_);
            rw.draw(pauseMenu_);
        }
    }

    void Game::update(sf::Event& event, sf::Time time) {
        controls(event);

        player_        .update(time);
        hud_           .update(&player_, levelNumber_+1, time);
        messageManager_.update(time);
        deathScreen_   .update(time);

        // the player dies
        if (!lost_ && player_.getAttributes().health == 0) {
            subject.notify(Observer::PLAYER_DIES, nullptr);
            
            paused_ = true;
            lose();
            
            deathScreen_.open();
        }

        gameView_.setCenter(sf::Vector2f(player_.getBounds().left+40, player_.getBounds().top+40));

        if (started_ && !paused_) {
            currentLevel_->update(this, time);
        }
    }

    void Game::controls(sf::Event& event) {
        if ((!mapOpen_ || Settings::game.debugMode) && started_ && !paused_) {
            bool canUpdateFOV = !player_.isMoving();
            if (isKeyPressed(Settings::keys.move_up)) {
                player_.move(currentLevel_->getTiles(), Player::UP);
                if (canUpdateFOV && player_.isMoving()) {
                    currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());
                    currentLevel_->makeOrdersToNPCs(&player_);
                }
            }
            if (isKeyPressed(Settings::keys.move_down)) {
                player_.move(currentLevel_->getTiles(), Player::DOWN);
                if (canUpdateFOV && player_.isMoving()) {
                    currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());
                    currentLevel_->makeOrdersToNPCs(&player_);
                }
            }
            if (isKeyPressed(Settings::keys.move_left)) {
                player_.move(currentLevel_->getTiles(), Player::LEFT);
                if (canUpdateFOV && player_.isMoving()) {
                    currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());
                    currentLevel_->makeOrdersToNPCs(&player_);
                }
            }
            if (isKeyPressed(Settings::keys.move_right)) {
                player_.move(currentLevel_->getTiles(), Player::RIGHT);
                if (canUpdateFOV && player_.isMoving()) {
                    currentLevel_->calculateFOV(player_.getGridPosition(), player_.getSightRange());
                    currentLevel_->makeOrdersToNPCs(&player_);
                }
            }
            
            if (  Settings::game.debugMode
                ) player_.cheat();
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& event) {
        if (      !started_       ) mainMenu_    .buttonEvents(rw, event, this);
        if (attributes_  .isOpen()) attributes_  .buttonEvents(rw, event, this);
        if (bookOfSpells_.isOpen()) bookOfSpells_.buttonEvents(rw, event, this);
        if (deathScreen_ .isOpen()) deathScreen_ .buttonEvents(rw, event, this);
        if (inventory_   .isOpen()) inventory_   .buttonEvents(rw, event, this);
        if (journal_     .isOpen()) journal_     .buttonEvents(rw, event, this);
        if (pauseMenu_   .isOpen()) pauseMenu_   .buttonEvents(rw, event, this);

        if (started_) {
            if (Settings::game.debugMode) {
                if      (  event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add
                         ) switchLevel(levelNumber_+1);
                else if (  event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract
                         ) switchLevel(levelNumber_-1);
            }

            if (  wasKeyPressed(event, sf::Keyboard::Escape)
                ) pause(!isPaused());
            if (!paused_) {
                if (wasKeyPressed(event, Settings::keys.open_attributes)) {
                    attributes_.update(&player_);
                    attributes_.open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_inventory)) {
                    inventory_.open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_map)) {
                    mapOpen_ = !mapOpen_;
                }
                else if (wasKeyPressed(event, Settings::keys.open_journal)) {
                    journal_.open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_bookOfSpells) && inventory_.contains(new Book(Book::SPELLS_BOOK, 0))) {
                    bookOfSpells_.open();
                    paused_ = true;
                }

                else if (wasKeyPressed(event, Settings::keys.attack)) {
                    currentLevel_->playerAttack(&player_);
                }
                else if (wasKeyPressed(event, Settings::keys.interact)) {
                    currentLevel_->playerInteract(this);
                }

                if      (wasKeyPressed(event, Settings::keys.useslot_1)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_2)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_3)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_4)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_5)) {}
            }
        }
    }

    void Game::start(bool b) {
        started_ = b;
    }

    void Game::pause(bool b) {
        paused_ = b;
        if (  paused_
            ) pauseMenu_.open();
        else {
            pauseMenu_   .close();
            inventory_   .close();
            attributes_  .close();
            journal_     .close();
            bookOfSpells_.close();
        }
    }

    void Game::reset() {
        if (currentLevel_ != nullptr) {
            delete currentLevel_;
            currentLevel_ = nullptr;
        }

        for (int i=0; i<9; ++i) {
            Potion::identified_[i] = false;
        }
        for (int i=0; i<12; ++i) {
            Rune  ::identified_[i] = false;
        }

        inventory_  .clear();
        player_     .reset();
        deathScreen_.reset();

        subject.clear();
        subject.addObserver(&inventory_);
        subject.addObserver(&messageManager_);

        levelNumber_ = 0;

        mapOpen_ = false;
        lost_    = false;
    }

}
