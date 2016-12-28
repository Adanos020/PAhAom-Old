/**
 * @file src/program/game/HUD.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../../Game.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    HUD::HUD()
    {
        reset();
    }

    void
    HUD::reset()
    {
        m_bHP = Bar(Bar::HORIZONTAL, 150, sf::Color::Red, sf::Vector2f(15, Settings::graphics.resolution.y - 20));
        m_bMP = Bar(Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(Settings::graphics.resolution.x - 165,
                                                                        Settings::graphics.resolution.y - 20));

        m_bXP = Bar(Bar::HORIZONTAL, Settings::graphics.resolution.x - 400, sf::Color(128, 128, 255),
                    sf::Vector2f(Settings::graphics.resolution.x / 2 - (Settings::graphics.resolution.x - 400) / 2,
                                 Settings::graphics.resolution.y - 20));

        m_tXPlevel     = Text(sf::Vector2f(0, 0), ""  , Resources::font.Pixel  , 40, sf::Color::Yellow);
        m_tLevelNumber = Text(sf::Vector2f(0, 0), "L0", Resources::font.Pixel  , 30, sf::Color::Green);
        m_tFPS         = Text(sf::Vector2f(0, 0), "0" , Resources::font.Unifont, 20, sf::Color::Yellow);

        m_tXPlevel    .setPosition(sf::Vector2f(m_bXP.getPosition().x + m_bXP.getSize().x/2 - m_tXPlevel.getSize().x/2,
                                                m_bXP.getPosition().y - m_tXPlevel.getSize().y));
        m_tLevelNumber.setPosition(sf::Vector2f(Settings::graphics.resolution.x - m_tLevelNumber.getSize().x-10, 10));
        m_tFPS        .setPosition(sf::Vector2f(5, 5));

        m_tXPlevel    .setOutlineColor(sf::Color::Black);
        m_tLevelNumber.setOutlineColor(sf::Color::Black);
        m_tFPS        .setOutlineColor(sf::Color::Black);

        m_tXPlevel    .setOutlineThickness(1.f);
        m_tLevelNumber.setOutlineThickness(1.f);
        m_tFPS        .setOutlineThickness(1.f);
    }

    void
    HUD::update(Player* p, int lvl, sf::Time& time)
    {
        if (p->getBuffs().poison > 0)
        {
            m_bHP.setFillColor(sf::Color(0x80, 0xff, 0x80));
        }
        else
        {
            if (p->getBuffs().hunger >= 500 && p->getBuffs().hunger < 1000)
            {
                m_bHP.setFillColor(sf::Color(0xff, 0x40, 0x40));
            }
            else if (p->getBuffs().hunger >= 1000)
            {
                m_bHP.setFillColor(sf::Color(0xff, 0xaa, 0xaa));
            }
            else
            {
                m_bHP.setFillColor(sf::Color::Red);
            }
        }

        m_bHP.setValue(sf::Vector2f(p->getAttributes().health     / p->getAttributes().maxHealth, 1));
        m_bMP.setValue(sf::Vector2f(p->getAttributes().mana       / p->getAttributes().maxMana  , 1));
        m_bXP.setValue(sf::Vector2f(p->getAttributes().experience / p->getAttributes().nextLevel, 1));

        m_tXPlevel.setString(std::to_wstring((int) p->getAttributes().level));
        m_tXPlevel.setPosition(sf::Vector2f(m_bXP.getPosition().x + m_bXP.getSize().x/2 - m_tXPlevel.getSize().x/2,
                                            m_bXP.getPosition().y - m_tXPlevel.getSize().y));

        m_tLevelNumber.setString("L"+std::to_string(lvl));
        m_tLevelNumber.setPosition(sf::Vector2f(Settings::graphics.resolution.x - m_tLevelNumber.getSize().x - 10, 10));

        char buf[10];
        snprintf(buf, 10, "%.1f", 1.f/time.asSeconds());
        m_tFPS.setString("FPS: "+sf::String(buf));
    }

    void
    HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_bHP, states);
        target.draw(m_bMP, states);
        target.draw(m_bXP, states);
        target.draw(m_tXPlevel, states);
        target.draw(m_tLevelNumber, states);
        
        if (Settings::game.debugMode)
        {
            target.draw(m_tFPS, states);
        }
    }

}
