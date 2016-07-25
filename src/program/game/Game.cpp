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

extern rr::Settings  settings;
extern rr::Resources resources;
extern rr::Subject   subject;
extern sf::Color     itemColors  [ 9];
extern int           spellSymbols[11];

namespace rr {

    Game::Game() 
    :
      currentLevel_  (nullptr               ),
      messageManager_(new MessageManager  ()),
      player_        (new Player          ()),
      mainMenu_      (new MainMenu        ()),
      pauseMenu_     (new PauseMenu       ()),
      attributes_    (new Attributes      ()),
      inventory_     (new Inventory(player_)),
      journal_       (new Journal          ()),
      bookOfSpells_  (new BookOfSpells    ()),
      hud_           (new HUD             ()),
      started_       (false                 ),
      paused_        (false                 ),
      levelNumber_   (0                     ) {

        gameView_.setSize  ((sf::Vector2f)settings.graphics.resolution);

        mapView_ .setSize  (6160.f, 3440.f);
        mapView_ .setCenter(mapView_.getSize()/2.f);

        subject.addObserver(inventory_);
        subject.addObserver(messageManager_);
    }

    Game::~Game() {
        delete mainMenu_;
        delete pauseMenu_;
        delete attributes_;
        delete inventory_;
        delete journal_;
        delete hud_;
        delete player_;
        delete currentLevel_;
    }

    void Game::randomizeItems() {
        /* colors */ {
            int pot[9];
            for (int i=0; i<9; i++) {
                hell: int x = rand()%9;
                for (int j=0; j<i; j++) {
                    if (  pot[j] == x
                        ) goto hell;
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
            for (int i=0; i<12; i++) {
                topkek: int x = rand()%12;
                for (int j=0; j<i; j++) {
                    if (  spellSymbols[j] == x
                        ) goto topkek;
                }
                spellSymbols[i] = x;
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

        player_->setPosition((ascending) ? currentLevel_->getStartingPoint() : currentLevel_->getEndingPoint());

        messageManager_->addMessage(Message(resources.dictionary["message.welcome_to_level"]+" "+std::to_string(levelNumber_+1)+((settings.game.language=="fc") ? "" : "!"), sf::Color::Green));
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
            if ( !file.good()
                ) return false;

            file.clear();
            *currentLevel_ >> file;
            file.close();

            if (  i!=0
                ) delete currentLevel_;
        }
        subject.addObserver(currentLevel_);

        player_->setPosition(currentLevel_->getStartingPoint());

        start(true);
        pause(false);

        return true;
    }

    bool Game::load() {
        std::ifstream file("save/save.pah");

        if ( !file.good()
            ) return false;

        reset();

        try {
            readFile <unsigned> (file, seed_       );
            readFile <unsigned> (file, levelNumber_);

            for (int i=0; i<9; ++i) {
                readFile <bool> (file, Potion::identified_[i]);
            }
            for (int i=0; i<12; ++i) {
                readFile <bool> (file, Rune  ::identified_[i]);
            }

            readEntity          (file, player_);

            srand(seed_);
            randomizeItems();

            *inventory_ << file;
            if (file.fail()) {
                std::string wtf;
                file.close();
                file.clear();
                file.sync ();
                file >> wtf;
                throw std::invalid_argument("Wrong data: " + wtf);
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

        *player_    >> file         << '\n';
        *inventory_ >> file;

        file.close();

        file.open("save/level"+std::to_string(levelNumber_)+".pah");
        file.clear();

        *currentLevel_ >> file << ' ';

        file.close();
    }

    void Game::draw(sf::RenderWindow& rw) {
        if (!started_) {
            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            mainMenu_->draw(rw);
            rw.setView((mapOpen_) ? mapView_ : gameView_);
        }
        else {
            rw.setView((mapOpen_) ? mapView_ : gameView_);
            rw.draw(*currentLevel_);
            currentLevel_->drawObjects(rw);
            player_->draw(rw);

            rw.setView(sf::View((sf::Vector2f)rw.getSize()/2.f, (sf::Vector2f)rw.getSize()));
            hud_           ->draw(rw);
            messageManager_->draw(rw);
            inventory_     ->draw(rw);
            pauseMenu_     ->draw(rw);
            attributes_    ->draw(rw);
            journal_       ->draw(rw);
            bookOfSpells_  ->draw(rw);
        }
    }

    void Game::update(sf::Event& event, sf::Time time) {
        controls(event);

        player_        ->update(time);
        hud_           ->update(player_, levelNumber_+1);
        messageManager_->update(time);

        gameView_.setCenter(sf::Vector2f(player_->getBounds().left+16, player_->getBounds().top+16));

        if (!paused_) {
            for (auto entity : currentLevel_->getEntities()) {
                if (instanceof<Door, Entity>(entity)) {
                    if (  player_->intersects(entity)
                        ) ((Door*)entity)->setOpen(true);
                    else  ((Door*)entity)->setOpen(false);
                }
                else if (  instanceof<NPC, Entity>(entity)
                         ) ((NPC*)entity)->update(time);
            }
        }

        for (int i=0; i<77*43; i++) {
            currentLevel_->getShadows()[i].see(false);
        }
        currentLevel_->calculateFOV((sf::Vector2u)player_->getPosition(), player_->getSightRange());
    }

    void Game::controls(sf::Event& event) {
        if (started_ && !paused_) {
            if (isKeyPressed(settings.keys.move_up))    player_->move(currentLevel_->getTiles(), Player::UP);
            if (isKeyPressed(settings.keys.move_down))  player_->move(currentLevel_->getTiles(), Player::DOWN);
            if (isKeyPressed(settings.keys.move_left))  player_->move(currentLevel_->getTiles(), Player::LEFT);
            if (isKeyPressed(settings.keys.move_right)) player_->move(currentLevel_->getTiles(), Player::RIGHT);
#if 0
                 if (isKeyPressed(sf::Keyboard::Numpad1)) player_->attrs_.health    --;
            else if (isKeyPressed(sf::Keyboard::Numpad2)) player_->attrs_.health    ++;
            else if (isKeyPressed(sf::Keyboard::Numpad3)) player_->attrs_.mana      --;
            else if (isKeyPressed(sf::Keyboard::Numpad4)) player_->attrs_.mana      ++;
            else if (isKeyPressed(sf::Keyboard::Numpad5)) player_->attrs_.experience++;
            else if (isKeyPressed(sf::Keyboard::Numpad6)) player_->attrs_.level     ++;
#endif
        }
    }

    void Game::buttonEvents(sf::RenderWindow& rw, sf::Event& event) {
        if (       !started_       ) mainMenu_    ->buttonEvents(rw, event, this);
        if (pauseMenu_   ->isOpen()) pauseMenu_   ->buttonEvents(rw, event, this);
        if (inventory_   ->isOpen()) inventory_   ->buttonEvents(rw, event, this);
        if (attributes_  ->isOpen()) attributes_  ->buttonEvents(rw, event, this);
        if (journal_     ->isOpen()) journal_     ->buttonEvents(rw, event, this);
        if (bookOfSpells_->isOpen()) bookOfSpells_->buttonEvents(rw, event, this);

        if (started_) {
            if      (  event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add
                     ) switchLevel(levelNumber_+1);
            else if (  event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract
                     ) switchLevel(levelNumber_-1);

            if (  wasKeyPressed(event, sf::Keyboard::Escape)
                ) pause(!isPaused());
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
                    mapOpen_ = !mapOpen_;
                }
                else if (wasKeyPressed(event, settings.keys.open_journal)) {
                    journal_->open();
                    paused_ = true;
                }
                else if (wasKeyPressed(event, settings.keys.open_bookOfSpells) && inventory_->contains(new Book(Book::SPELLS_BOOK, 0))) {
                    bookOfSpells_->open();
                    paused_ = true;
                }

                else if (wasKeyPressed(event, settings.keys.attack)) {

                }
                else if (wasKeyPressed(event, settings.keys.interact)) {

#define entities currentLevel_->getEntities()
;
                    for (unsigned i=0; i<entities.size(); i++) {
                        if (player_->getPosition() == entities[i]->getPosition()) {
                            if (instanceof<Item, Entity>(entities[i])) {
                                if (inventory_->addItem((Item*)entities[i])) {
                                    subject.notify(Observer::ITEM_PICKED, entities[i]);
                                    currentLevel_->removeEntity(i);
                                    break;
                                }
                                else messageManager_->addMessage(Message(resources.dictionary["message.full_inventory"], sf::Color::Red));
                            }
                            else if (instanceof<Chest, Entity>(entities[i])) {
                                currentLevel_->replaceEntity(i, ((Chest*)entities[i])->getItem());
                            }
                            else if (instanceof<Stairs, Entity>(entities[i])) {
                                if (((Stairs*)entities[i])->isUpwards()) {
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
        if (  paused_
            ) pauseMenu_->open();
        else {
            pauseMenu_   ->close();
            inventory_   ->close();
            attributes_  ->close();
            journal_     ->close();
            bookOfSpells_->close();
        }
    }

    void Game::reset() {
        if (  currentLevel_ != nullptr
            ) delete currentLevel_;

        for (int i=0; i<9; ++i) {
            Potion::identified_[i] = false;
        }
        for (int i=0; i<12; ++i) {
            Rune  ::identified_[i] = false;
        }

        inventory_->clear();
        player_   ->reset();

        subject.clear();
        subject.addObserver(inventory_);
        subject.addObserver(messageManager_);

        levelNumber_ = 0;
        mapOpen_     = false;
    }

}
