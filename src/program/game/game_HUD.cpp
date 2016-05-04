/**
 * @file src/program/game/game_HUD.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"
#include "../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    HUD::HUD() {
        bHP_ = new Bar(Bar::HORIZONTAL, 150, sf::Color::Red, sf::Vector2f(15, settings.graphics.resolution.y-20));
        bMP_ = new Bar(Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(settings.graphics.resolution.x-165, settings.graphics.resolution.y-20));
        bXP_ = new Bar(Bar::HORIZONTAL, settings.graphics.resolution.x-400, sf::Color(128, 128, 255), sf::Vector2f(settings.graphics.resolution.x/2-(settings.graphics.resolution.x-400)/2, settings.graphics.resolution.y-20));
        for (int i=0; i<5; i++) {
            sCarryOn_[i] = new Slot(sf::Vector2f(80, 80), sf::Vector2f(settings.graphics.resolution.x-90, settings.graphics.resolution.y/2-250+i*95));
        }
        tXPlevel_ = new Text(sf::Vector2f(0, 0), L"", resources.font.Pixel, 40, sf::Color::Yellow);
        tXPlevel_->setPosition(sf::Vector2f(bXP_->getPosition().x+bXP_->getSize().x/2-tXPlevel_->getSize().x/2, bXP_->getPosition().y-tXPlevel_->getSize().y));
    }

    HUD::~HUD() {
        delete bHP_;
        delete bMP_;
        delete bXP_;
        for (auto x : sCarryOn_)
            delete x;
        delete tXPlevel_;
    }

    void HUD::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        for (auto x : sCarryOn_) {
            if (x->isPressed(rw, e)) {}
        }
    }

    void HUD::update(Player* p) {
        bHP_->setSize(sf::Vector2f(p->getAttributes().health/p->getAttributes().maxHealth, 1));
        bMP_->setSize(sf::Vector2f(p->getAttributes().mana/p->getAttributes().maxMana, 1));
        bXP_->setSize(sf::Vector2f(p->getAttributes().experience/p->getAttributes().nextLevel, 1));

        tXPlevel_->setString(std::to_wstring((int)p->getAttributes().level));
        tXPlevel_->setPosition(sf::Vector2f(bXP_->getPosition().x+bXP_->getSize().x/2-tXPlevel_->getSize().x/2, bXP_->getPosition().y-tXPlevel_->getSize().y));
    }

    void HUD::draw(sf::RenderWindow& rw) {
        bHP_->draw(rw);
        bMP_->draw(rw);
        bXP_->draw(rw);
        for (auto x : sCarryOn_)
            x->draw(rw);
        tXPlevel_->draw(rw);
    }

}
