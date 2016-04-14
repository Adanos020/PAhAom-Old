/**
 * @file src/program/game/game_HUD.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    HUD::HUD(sf::RenderWindow& rw) {
        bHP = new Bar(Bar::HORIZONTAL, 150, sf::Color::Red, sf::Vector2f(15, rw.getSize().y-20));
        bMP = new Bar(Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(rw.getSize().x-165, rw.getSize().y-20));
        bXP = new Bar(Bar::HORIZONTAL, rw.getSize().x-400, sf::Color(128, 128, 255), sf::Vector2f(rw.getSize().x/2-(rw.getSize().x-400)/2, rw.getSize().y-20));
        for (int i=0; i<5; i++) {
            sCarryOn[i] = new Slot(sf::Vector2f(75, 75), sf::Vector2f(rw.getSize().x-80, rw.getSize().y/2-250+i*90));
        }
        tXPlevel = new Text(sf::Vector2f(0, 0), L"", resources.font.Pixel, 40, sf::Color::Yellow);
        tXPlevel->setPosition(sf::Vector2f(bXP->getPosition().x+bXP->getSize().x/2-tXPlevel->getSize().x/2, bXP->getPosition().y-tXPlevel->getSize().y));
    }

    HUD::~HUD() {
        delete bHP;
        delete bMP;
        delete bXP;
        for (auto x : sCarryOn)
            delete x;
        delete tXPlevel;
    }

    void HUD::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        for (auto x : sCarryOn) {
            if (x->isPressed(rw, e)) {}
        }
    }

    void HUD::update(Player* p) {
        bHP->setSize(sf::Vector2f(p->getAttributes().health/p->getAttributes().maxHealth, 1));
        bMP->setSize(sf::Vector2f(p->getAttributes().mana/p->getAttributes().maxMana, 1));
        bXP->setSize(sf::Vector2f((float)p->getAttributes().experience/(float)p->getAttributes().nextLevel, 1));

        tXPlevel->setString(std::to_wstring((int)p->getAttributes().level));
        tXPlevel->setPosition(sf::Vector2f(bXP->getPosition().x+bXP->getSize().x/2-tXPlevel->getSize().x/2, bXP->getPosition().y-tXPlevel->getSize().y));
    }

    void HUD::draw(sf::RenderWindow& rw) {
        bHP->draw(rw);
        bMP->draw(rw);
        bXP->draw(rw);
        for (auto x : sCarryOn)
            x->draw(rw);
        tXPlevel->draw(rw);
    }

}
