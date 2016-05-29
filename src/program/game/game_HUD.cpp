/**
 * @file src/program/game/game_HUD.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "game.hpp"
#include "../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    HUD::HUD()
        : bHP_         (new Bar(Bar::HORIZONTAL, 150, sf::Color::Red, sf::Vector2f(15, settings.graphics.resolution.y-20))),
          bMP_         (new Bar(Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(settings.graphics.resolution.x-165, settings.graphics.resolution.y-20))),
          bXP_         (new Bar(Bar::HORIZONTAL, settings.graphics.resolution.x-400, sf::Color(128, 128, 255), sf::Vector2f(settings.graphics.resolution.x/2-(settings.graphics.resolution.x-400)/2, settings.graphics.resolution.y-20))),
          tXPlevel_    (new Text(sf::Vector2f(0, 0), "", resources.font.Pixel, 40, sf::Color::Yellow)),
          tLevelNumber (new Text(sf::Vector2f(0, 0), "L0", resources.font.Pixel, 30, sf::Color::Green)) {

        tXPlevel_->setPosition(sf::Vector2f(bXP_->getPosition().x+bXP_->getSize().x/2-tXPlevel_->getSize().x/2, bXP_->getPosition().y-tXPlevel_->getSize().y));
        tLevelNumber->setPosition(sf::Vector2f(settings.graphics.resolution.x-tLevelNumber->getSize().x-10, 10));
    }

    HUD::~HUD() {
        delete bHP_;
        delete bMP_;
        delete bXP_;
        delete tXPlevel_;
    }

    void HUD::update(Player* p, int lvl) {
        bHP_->setSize(sf::Vector2f(p->getAttributes().health/p->getAttributes().maxHealth, 1));
        bMP_->setSize(sf::Vector2f(p->getAttributes().mana/p->getAttributes().maxMana, 1));
        bXP_->setSize(sf::Vector2f(p->getAttributes().experience/p->getAttributes().nextLevel, 1));

        tXPlevel_->setString(std::to_wstring((int)p->getAttributes().level));
        tXPlevel_->setPosition(sf::Vector2f(bXP_->getPosition().x+bXP_->getSize().x/2-tXPlevel_->getSize().x/2, bXP_->getPosition().y-tXPlevel_->getSize().y));

        tLevelNumber->setString("L"+std::to_string(lvl));
        tLevelNumber->setPosition(sf::Vector2f(settings.graphics.resolution.x-tLevelNumber->getSize().x-10, 10));
    }

    void HUD::draw(sf::RenderWindow& rw) {
        bHP_        ->draw(rw);
        bMP_        ->draw(rw);
        bXP_        ->draw(rw);
        tXPlevel_   ->draw(rw);
        tLevelNumber->draw(rw);
    }

}
