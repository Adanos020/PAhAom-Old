/**
 * @file src/program/Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../Game.hpp"

#include "../Settings.hpp"
#include "../Resources.hpp"

#include "../Observer.hpp"

#include "../funcs/keys.hpp"
#include "../funcs/files.hpp"

extern rr::Subject subject;
extern sf::Color   itemColors  [ 9];
extern int         spellSymbols[12];

namespace rr
{

    Game::Game() :
      m_currentLevel    (nullptr),
      m_hitMarkerManager(&m_player),
      m_conversation    (&m_player),
      m_inventory       (Inventory(&m_player)),
      m_started         (false),
      m_paused          (false),
      m_mapOpen         (false),
      m_lost            (false),
      m_levelNumber     (0)
    {
        m_gameView.setSize((sf::Vector2f) Settings::graphics.resolution);

        m_mapView.setSize  (6160.f, 3440.f);
        m_mapView.setCenter(m_mapView.getSize()/2.f);

        subject.addObserver(&m_journal);
        subject.addObserver(&m_inventory);
        subject.addObserver(&m_audioManager);
        subject.addObserver(&m_messageManager);
        subject.addObserver(&m_hitMarkerManager);

        m_audioManager.playMusic(AudioManager::MENU);
    }

    Game::~Game()
    {
        delete m_currentLevel;
    }

    void
    Game::randomizeItems()
    {
        /* colors */
        {
            int pot[9];
            for (int i = 0; i < 9; ++i)
            {
                hell: pot[i] = rand()%9;
                for (int j = 0; j < i; ++j)
                {
                    if (pot[j] == pot[i])
                        goto hell;
                }
                switch (pot[i])
                {
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
        /* Rune symbols */
        for (int i = 0; i < 12; ++i)
        {
            topkek: spellSymbols[i] = rand()%12;
            for (int j = 0; j < i; ++j)
            {
                if (spellSymbols[j] == spellSymbols[i])
                    goto topkek;
            }
        }
    }

    void
    Game::switchLevel(int index)
    {
        {
            std::ofstream file("save/level"+std::to_string(m_levelNumber)+".pah");
            file.clear();
            *m_currentLevel >> file;
            file.close();
        }

        bool ascending = false;
        if (index > (int) m_levelNumber)
        {
            if (m_levelNumber < 29)
                m_levelNumber++;
            else
                return;
            ascending = true;
        }
        else if (index < (int) m_levelNumber)
        {
            if (m_levelNumber > 0)
                m_levelNumber--;
            else
                return;
        }

        subject.removeObserver(m_currentLevel);
        delete m_currentLevel;

        m_currentLevel = new Level(m_levelNumber);
        subject.addObserver(m_currentLevel);
        m_player.setCurrentLevel(m_currentLevel);

        std::ifstream file("save/level"+std::to_string(m_levelNumber)+".pah");
        *m_currentLevel << file;
        file.close();

        m_player.setGridPosition((ascending) ? m_currentLevel->getStartingPoint() : m_currentLevel->getEndingPoint());

        m_currentLevel->calculateFOV(m_player.getGridPosition(), m_player.getSightRange());

        m_messageManager.addMessage(Message(Resources::dictionary["message.welcome_to_level"]
                                           +" "
                                           +std::to_string(m_levelNumber+1)
                                           +((Settings::game.language == "fc") ? "" : "!"), sf::Color::Green));

        save();
    }

    bool
    Game::loadNewGame()
    {
        reset();

        m_seed = time(0);
        srand(m_seed);
        randomizeItems();

        std::ofstream file;

        for (int i = 29; i >= 0; --i)
        {
            m_currentLevel = new Level(i);
            m_currentLevel->generateWorld();

            file.open("save/level"+std::to_string(i)+".pah");
            if (!file.good()) {
                system("mkdir save");
                file.open("save/level"+std::to_string(i)+".pah");
            }

            file.clear();
            *m_currentLevel >> file;
            file.close();

            if (i != 0)
                delete m_currentLevel;
        }
        subject.addObserver(m_currentLevel);

        m_player.setGridPosition(m_currentLevel->getStartingPoint());
        m_player.setCurrentLevel(m_currentLevel);

        start(true);
        pause(false);

        m_currentLevel->calculateFOV(m_player.getGridPosition(), m_player.getSightRange());

        m_inventory.addItem(new MeleeWeapon(MeleeWeapon::KNIFE));
        m_inventory.addItem(new Food(Food::BAGUETTE));
        m_inventory.addItem(new Potion(Potion::HEALING));

        //m_inventory.addItem(new Book(Book::SPELLS_BOOK));
        //m_inventory.addItem(new Coin(Coin::GOLDEN, Coin::SMALL, 3));
        m_inventory.addItem(new Ring(Ring::HEALTH));

        m_audioManager.playMusic(AudioManager::PRISON);

        return true;
    }

    bool
    Game::load()
    {
        reset();

        std::ifstream file("save/save.pah");

        if (!file.good())
            return false;

        try
        {
            readFile <unsigned> (file, m_seed       );
            readFile <unsigned> (file, m_levelNumber);

            srand(m_seed);
            randomizeItems();

            for (int i = 0; i < 9; ++i)
            {
                readFile <bool> (file, Potion::m_identified[i]);
                if (Potion::m_identified[i])
                    subject.notify(Observer::ITEM_DISCOVERED, new Potion((Potion::Type) i));
            }
            for (int i = 0; i < 12; ++i)
            {
                readFile <bool> (file, Rune::m_identified[i]);
                if (Rune::m_identified[i])
                    subject.notify(Observer::ITEM_DISCOVERED, new Rune((Rune::Type) i));
            }
            m_messageManager.clear();

            readEntity(file, &m_player);

            m_inventory << file;
            if (file.fail())
            {
                std::string wtf;
                file.close();
                file.clear();
                file.sync ();
                int pos = file.tellg();
                file >> wtf;
                throw std::invalid_argument("Wrong data in inventory: " + wtf + ", position: " + std::to_string(pos));
            }

            file.close();

            m_currentLevel = new Level(m_levelNumber);
            m_player.setCurrentLevel(m_currentLevel);

            file.open("save/level"+std::to_string(m_levelNumber)+".pah");
            *m_currentLevel << file;
            file.close();

            subject.addObserver(m_currentLevel);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        start(true);
        pause(false);

        m_currentLevel->calculateFOV(m_player.getGridPosition(), m_player.getSightRange());

        m_audioManager.playMusic(AudioManager::PRISON);

        return true;
    }

    void
    Game::save()
    {
        std::ofstream file("save/save.pah");
        file.clear();

        file << m_seed        << '\n'
             << m_levelNumber << '\n';

        for (int i = 0; i < 9; ++i)
        {
            file << Potion::m_identified[i] << ' ';
        }
        for (int i = 0; i < 12; ++i)
        {
            file << Rune  ::m_identified[i] << ' ';
        }
        file << '\n';

        m_player    >> file << '\n';
        m_inventory >> file;

        file.close();

        file.open("save/level"+std::to_string(m_levelNumber)+".pah");
        file.clear();

        *m_currentLevel >> file << ' ';

        file.close();
    }

    void
    Game::lose()
    {
        m_lost = true;

#ifdef __gnu_linux__
        system("rm -rf save/*.pah");
#else
        system("del save/*.pah");
#endif

    }

    void
    Game::draw(sf::RenderWindow& rw)
    {
        if (!m_started)
        {
            rw.setView(sf::View((sf::Vector2f) rw.getSize()/2.f, (sf::Vector2f) rw.getSize()));
            rw.draw(m_mainMenu);
            rw.setView((m_mapOpen) ? m_mapView : m_gameView);
        }
        else
        {
            rw.setView((m_mapOpen) ? m_mapView : m_gameView);
            rw.draw(*m_currentLevel);
            rw.draw(m_player);
            m_hitMarkerManager.draw(rw);

            rw.setView(sf::View((sf::Vector2f) rw.getSize()/2.f, (sf::Vector2f) rw.getSize()));

            m_messageManager.draw(rw);

            if (!m_conversation.isOpen())
            {
                rw.draw(m_hud);
                rw.draw(m_inventory);
            }
            rw.draw(m_attributes);
            rw.draw(m_bookOfSpells);
            rw.draw(m_conversation);
            rw.draw(m_deathScreen);
            rw.draw(m_journal);
            rw.draw(m_pauseMenu);
        }
    }

    void
    Game::update(sf::Event& event, sf::Time& time)
    {
        controls(event);

        m_player          .update(time);
        m_messageManager  .update(time);
        m_hitMarkerManager.update(time);
        m_deathScreen     .update(time);

        // the player dies
        if (!m_lost && m_player.getAttributes().health == 0)
        {
            subject.notify(Observer::PLAYER_DIES, nullptr);

            m_paused = true;
            lose();

            m_deathScreen.open();
        }

        m_gameView.setCenter(sf::Vector2f(m_player.getBounds().left+40, m_player.getBounds().top+40));

        if (m_started && !m_paused)
            m_currentLevel->update(this, time);

        m_hud.update(&m_player, m_levelNumber+1, time);
    }

    void
    Game::controls(sf::Event& event)
    {
        if ((!m_mapOpen || Settings::game.debugMode) && m_started && !m_paused)
        {
            bool canUpdateFOV = !m_player.isMoving();
            m_player.handleInput(event);

            if (canUpdateFOV && m_player.isMoving())
            {
                m_currentLevel->closeDoors();
                m_currentLevel->calculateFOV(m_player.getGridPosition(), m_player.getSightRange());
                m_currentLevel->makeOrdersToNPCs(&m_player);
            }

            if (Settings::game.debugMode)
                m_player.cheat();
        }
    }

    void
    Game::buttonEvents(sf::RenderWindow& rw, sf::Event& event)
    {
        if (m_started)
        {
            if (Settings::game.debugMode)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
                    switchLevel(m_levelNumber+1);
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
                    switchLevel(m_levelNumber-1);
            }

            if (wasKeyPressed(event, sf::Keyboard::Escape) && !m_conversation.isOpen())
                pause(!isPaused());

            if (!m_paused)
            {
                if (wasKeyPressed(event, Settings::keys.open_attributes))
                {
                    m_attributes.update(&m_player);
                    m_attributes.open();
                    if (!Settings::game.debugMode)
                        m_paused = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_inventory))
                {
                    m_inventory.open();
                    m_paused = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_map))
                {
                    m_mapOpen = !m_mapOpen;

                    if (!Settings::game.debugMode)
                        m_paused = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_journal))
                {
                    m_journal.open();
                    m_paused = true;
                }
                else if (wasKeyPressed(event, Settings::keys.open_bookOfSpells)
                    && m_inventory.contains(new Book(Book::SPELLS_BOOK, 0)))
                {
                    m_bookOfSpells.open();
                    m_paused = true;
                }

                else if (wasKeyPressed(event, Settings::keys.attack))
                {
                    m_currentLevel->playerAttack(&m_player);
                }
                else if (wasKeyPressed(event, Settings::keys.interact))
                {
                    m_currentLevel->playerInteract(this);
                }

                if      (wasKeyPressed(event, Settings::keys.useslot_1)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_2)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_3)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_4)) {}
                else if (wasKeyPressed(event, Settings::keys.useslot_5)) {}
            }
        }

        if (      !m_started       ) m_mainMenu    .buttonEvents(rw, event, this);
        if (m_attributes  .isOpen()) m_attributes  .buttonEvents(rw, event, this);
        if (m_bookOfSpells.isOpen()) m_bookOfSpells.buttonEvents(rw, event, this);
        if (m_conversation.isOpen()) m_conversation.buttonEvents(rw, event, this);
        if (m_deathScreen .isOpen()) m_deathScreen .buttonEvents(rw, event, this);
        if (m_inventory   .isOpen()) m_inventory   .buttonEvents(rw, event, this);
        if (m_journal     .isOpen()) m_journal     .buttonEvents(rw, event, this);
        if (m_pauseMenu   .isOpen()) m_pauseMenu   .buttonEvents(rw, event, this);
    }

    void
    Game::start(bool b)
    {
        m_started = b;

        if (!m_started)
            m_audioManager.playMusic(AudioManager::MENU);
    }

    void
    Game::pause(bool b)
    {
        m_paused = b;
        if (m_paused && !m_conversation.isOpen())
            m_pauseMenu.open();
        else
        {
            m_pauseMenu   .close();
            m_inventory   .close();
            m_attributes  .close();
            m_journal     .close();
            m_bookOfSpells.close();

            if (!Settings::game.debugMode)
                m_mapOpen = false;
        }
    }

    void
    Game::reset()
    {
        if (m_currentLevel != nullptr)
        {
            delete m_currentLevel;
            m_currentLevel = nullptr;
        }

        for (int i = 0; i < 9; ++i)
        {
            Potion::m_identified[i] = false;
        }
        for (int i = 0; i < 12; ++i)
        {
            Rune  ::m_identified[i] = false;
        }

        m_inventory  .clear();
        m_player     .reset();
        m_deathScreen.reset();

        subject.clear();
        subject.addObserver(&m_journal);
        subject.addObserver(&m_inventory);
        subject.addObserver(&m_audioManager);
        subject.addObserver(&m_messageManager);
        subject.addObserver(&m_hitMarkerManager);

        m_levelNumber = 0;

        m_mapOpen = false;
        m_lost    = false;
    }

}
