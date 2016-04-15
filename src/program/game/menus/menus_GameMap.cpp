/**
 * @file src/program/game/menus/menus_GameMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

extern rr::Dictionary dictionary;
extern rr::Settings settings;
extern rr::Resources resources;

namespace rr {

    GameMap::GameMap(sf::RenderWindow& rw) {
        shadow.setSize((sf::Vector2f)rw.getSize());
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        wGmap = new Window(dictionary.gui.window.game_map, sf::Vector2f(725, 470), sf::Vector2f(rw.getSize().x/2-362.5, rw.getSize().y/2-225));
            wGmap->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
            component(wGmap, Button, 0)->setPosition(sf::Vector2f(wGmap->getPosition().x+wGmap->getSize().x-component(wGmap, Button, 0)->getSize().x-15, rw.getSize().y/2+225-component(wGmap, Button, 0)->getSize().y-5));

#undef component

    }

    GameMap::~GameMap() {
        delete wGmap;
    }

    void GameMap::open() {
        wGmap->setVisible(true);
    }

    void GameMap::close() {
        wGmap->setVisible(false);
    }

    void GameMap::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (wGmap->isVisible()) {
            if (component(wGmap, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void GameMap::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        wGmap->draw(rw);
    }

    bool GameMap::isOpen() {
        return wGmap->isVisible();
    }

}

