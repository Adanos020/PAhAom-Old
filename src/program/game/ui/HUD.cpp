/**
 * @file src/program/game/HUD.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "../Game.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    HUD::HUD() :
      bHP_         (Bar (Bar::HORIZONTAL, 150, sf::Color::Red , sf::Vector2f(15, Settings::graphics.resolution.y-20))),
      bMP_         (Bar (Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(    Settings::graphics.resolution.x-165,
                                                                                 Settings::graphics.resolution.y-20))),

      bXP_         (Bar (Bar::HORIZONTAL, Settings::graphics.resolution.x-400, sf::Color(128, 128, 255),
                             sf::Vector2f(Settings::graphics.resolution.x/2 - (Settings::graphics.resolution.x-400)/2,
                                          Settings::graphics.resolution.y-20)                                       )),

      tXPlevel_    (Text(sf::Vector2f(0, 0), ""  , Resources::font.Pixel  , 40, sf::Color::Yellow                   )),
      tLevelNumber_(Text(sf::Vector2f(0, 0), "L0", Resources::font.Pixel  , 30, sf::Color::Green                    )),
      tFPS_        (Text(sf::Vector2f(0, 0), "0" , Resources::font.Unifont, 20, sf::Color::Yellow                   ))
    {
        tXPlevel_.setPosition(sf::Vector2f(bXP_.getPosition().x + bXP_.getSize().x/2 - tXPlevel_.getSize().x/2,
                                           bXP_.getPosition().y - tXPlevel_.getSize().y));
        tLevelNumber_.setPosition(sf::Vector2f(Settings::graphics.resolution.x - tLevelNumber_.getSize().x-10, 10));
        tFPS_.setPosition(sf::Vector2f(5, 5));

        tXPlevel_    .setOutlineColor(sf::Color::Black);
        tLevelNumber_.setOutlineColor(sf::Color::Black);
        tFPS_        .setOutlineColor(sf::Color::Black);

        tXPlevel_    .setOutlineThickness(1.f);
        tLevelNumber_.setOutlineThickness(1.f);
        tFPS_        .setOutlineThickness(1.f);
    }

    void
    HUD::update(Player* p, int lvl, sf::Clock& timer)
    {
        if (  p->getBuffs().poison > 0
            ) bHP_.setFillColor(sf::Color(0x80, 0xff, 0x80));
        else
        {
            if      (  p->getBuffs().hunger >= 500 && p->getBuffs().hunger < 1000
                     ) bHP_.setFillColor(sf::Color(0xff, 0x40, 0x40));
            else if (  p->getBuffs().hunger >= 1000
                     ) bHP_.setFillColor(sf::Color(0xff, 0xaa, 0xaa));
            else       bHP_.setFillColor(sf::Color::Red);
        }

        bHP_.setValue(sf::Vector2f(p->getAttributes().health     / p->getAttributes().maxHealth, 1));
        bMP_.setValue(sf::Vector2f(p->getAttributes().mana       / p->getAttributes().maxMana  , 1));
        bXP_.setValue(sf::Vector2f(p->getAttributes().experience / p->getAttributes().nextLevel, 1));

        tXPlevel_.setString  (std::to_wstring((int) p->getAttributes().level));
        tXPlevel_.setPosition(sf::Vector2f(bXP_.getPosition().x + bXP_.getSize().x/2 - tXPlevel_.getSize().x/2,
                                           bXP_.getPosition().y                      - tXPlevel_.getSize().y));

        tLevelNumber_.setString  ("L"+std::to_string(lvl));
        tLevelNumber_.setPosition(sf::Vector2f(Settings::graphics.resolution.x - tLevelNumber_.getSize().x-10, 10));

        char buf[64];
        snprintf(buf, 64, "%.1f", 1.f/timer.getElapsedTime().asSeconds());
        tFPS_.setString("FPS: "+sf::String(buf));
    }

    void
    HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(bHP_         , states);
        target.draw(bMP_         , states);
        target.draw(bXP_         , states);
        target.draw(tXPlevel_    , states);
        target.draw(tLevelNumber_, states);
        
        if (  Settings::game.debugMode
            ) target.draw(tFPS_        , states);
    }

}
