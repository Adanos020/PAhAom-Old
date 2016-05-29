/**
 * @file src/program/game/menus/menus_GameMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    GameMap::GameMap() {
        shadow_.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        wGmap_ = new Window(resources.dictionary["gui.window.game_map"], sf::Vector2f(settings.graphics.resolution.x*0.77f , settings.graphics.resolution.y*0.745f+77),
                                                                         sf::Vector2f(settings.graphics.resolution.x*0.115f, settings.graphics.resolution.y*0.1275f-25));
            *wGmap_ += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
            component(wGmap_, Button, 0)->setPosition(sf::Vector2f(wGmap_->getPosition().x+wGmap_->getSize().x/2-component(wGmap_, Button, 0)->getSize().x/2,
                                                                   wGmap_->getPosition().y+wGmap_->getSize().y  -component(wGmap_, Button, 0)->getSize().y-5));

#undef component

    }

    GameMap::~GameMap() {
        delete wGmap_;
    }

    void GameMap::open() {
        wGmap_->setVisible(true);
    }

    void GameMap::close() {
        wGmap_->setVisible(false);
    }

    void GameMap::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wGmap_->isVisible()) {
            if (component(wGmap_, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void GameMap::draw(sf::RenderWindow& rw) {
        if (isOpen()) {
            rw.draw(shadow_);
            wGmap_->draw(rw);
        }
    }

    bool GameMap::isOpen() {
        return wGmap_->isVisible();
    }

}

