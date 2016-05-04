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
        _bHP = new Bar(Bar::HORIZONTAL, 150, sf::Color::Red, sf::Vector2f(15, settings.graphics.resolution.y-20));
        _bMP = new Bar(Bar::HORIZONTAL, 150, sf::Color::Blue, sf::Vector2f(settings.graphics.resolution.x-165, settings.graphics.resolution.y-20));
        _bXP = new Bar(Bar::HORIZONTAL, settings.graphics.resolution.x-400, sf::Color(128, 128, 255), sf::Vector2f(settings.graphics.resolution.x/2-(settings.graphics.resolution.x-400)/2, settings.graphics.resolution.y-20));
        for (int i=0; i<5; i++) {
            _sCarryOn[i] = new Slot(sf::Vector2f(80, 80), sf::Vector2f(settings.graphics.resolution.x-90, settings.graphics.resolution.y/2-250+i*95));
        }
        _tXPlevel = new Text(sf::Vector2f(0, 0), L"", resources.font.Pixel, 40, sf::Color::Yellow);
        _tXPlevel->setPosition(sf::Vector2f(_bXP->getPosition().x+_bXP->getSize().x/2-_tXPlevel->getSize().x/2, _bXP->getPosition().y-_tXPlevel->getSize().y));
    }

    HUD::~HUD() {
        delete _bHP;
        delete _bMP;
        delete _bXP;
        for (auto x : _sCarryOn)
            delete x;
        delete _tXPlevel;
    }

    void HUD::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        for (auto x : _sCarryOn) {
            if (x->isPressed(rw, e)) {}
        }
    }

    void HUD::update(Player* p) {
        _bHP->setSize(sf::Vector2f(p->getAttributes().health/p->getAttributes().maxHealth, 1));
        _bMP->setSize(sf::Vector2f(p->getAttributes().mana/p->getAttributes().maxMana, 1));
        _bXP->setSize(sf::Vector2f(p->getAttributes().experience/p->getAttributes().nextLevel, 1));

        _tXPlevel->setString(std::to_wstring((int)p->getAttributes().level));
        _tXPlevel->setPosition(sf::Vector2f(_bXP->getPosition().x+_bXP->getSize().x/2-_tXPlevel->getSize().x/2, _bXP->getPosition().y-_tXPlevel->getSize().y));
    }

    void HUD::draw(sf::RenderWindow& rw) {
        _bHP->draw(rw);
        _bMP->draw(rw);
        _bXP->draw(rw);
        for (auto x : _sCarryOn)
            x->draw(rw);
        _tXPlevel->draw(rw);
    }

}
