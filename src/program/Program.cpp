/**
 * @file src/program/Program.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Program.hpp"
#include "Settings.hpp"
#include "Resources.hpp"

#include "funcs/files.hpp"
#include "funcs/classes.hpp"

#include <SFML/System/String.hpp>

namespace rr
{

    sf::String Program::m_version("pre-alpha 0.7");

    Program::Program()
    {

    }

    Program::~Program()
    {
        delete m_game;
    }

    bool
    Program::loadResources()
    {
        return Settings ::load()
            && Resources::load();
    }

    void
    Program::runGame()
    {
        m_window.setVerticalSyncEnabled(Settings::graphics.vsync);
        m_window.setKeyRepeatEnabled(false);
        m_window.create(sf::VideoMode(Settings::graphics.resolution.x, Settings::graphics.resolution.y, 32), "PAhAom",
                        Settings::graphics.fullscreen ? sf::Style::Fullscreen
                                                      : sf::Style::Close, Settings::graphics.csettings);

        m_game = new Game();
        mainLoop();
    }

    void
    Program::handleEvents()
    {
        while (m_window.pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
                m_window.close();
            if (m_event.type == sf::Event::LostFocus && !m_game->isPaused())
                m_game->pause(true);

            m_game->buttonEvents(m_window, m_event);
        }
    }

    void
    Program::draw()
    {
        m_window.clear();
        m_game->draw(m_window);
        m_window.display();
    }

    void
    Program::update(sf::Clock& timer)
    {
        if (m_game->isStarted())
            m_game->update(m_event, timer);
    }

    void
    Program::mainLoop()
    {
        sf::Clock timer;
        while (m_window.isOpen())
        {
            update       (timer);
            timer.restart();
            
            draw         ();
            handleEvents ();
        }
    }

}
