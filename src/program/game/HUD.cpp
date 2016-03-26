#include "game.h"

extern rr::Settings settings;

namespace rr {

    HUD::HUD(sf::RenderWindow& rw) {
        bHP = new Bar(nullptr, "horizontal", 150, sf::Color::Red, sf::Vector2f(15, rw.getSize().y-20));
        bMP = new Bar(nullptr, "horizontal", 150, sf::Color::Blue, sf::Vector2f(rw.getSize().x-165, rw.getSize().y-20));
        bXP = new Bar(nullptr, "horizontal", rw.getSize().x-400, sf::Color(128, 128, 255), sf::Vector2f(rw.getSize().x/2-(rw.getSize().x-400)/2, rw.getSize().y-20));
        for (int i=0; i<5; i++)
            sCarryOn[i] = new Slot(nullptr, sf::Vector2f(75, 75), sf::Vector2f(rw.getSize().x-80, rw.getSize().y/2-250+i*90));
        tXPlevel = new Text(nullptr, L"24", sf::Vector2f(0, 0), 40, sf::Color::Yellow);
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

    void HUD::update() {

    }

    void HUD::buttonEvents(sf::RenderWindow& rw, Game* g) {

    }

    void HUD::draw(sf::RenderWindow& rw, sf::View& v) {
        rw.setView(rw.getDefaultView());
        bHP->draw(rw);
        bMP->draw(rw);
        bXP->draw(rw);
        for (auto x : sCarryOn)
            x->draw(rw);
        tXPlevel->draw(rw);
        rw.setView(v);
    }

}
