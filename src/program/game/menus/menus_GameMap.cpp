/**
 * @file src/program/game/menus/menus_GameMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    GameMap::GameMap() {
        shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        wGmap = new Window(resources.dictionary["gui.window.game_map"], sf::Vector2f(settings.graphics.resolution.x*0.77f, settings.graphics.resolution.y*0.745f+77),
                                                                        sf::Vector2f(settings.graphics.resolution.x/8, settings.graphics.resolution.y/8-25));
            wGmap->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
            component(wGmap, Button, 0)->setPosition(sf::Vector2f(wGmap->getPosition().x+wGmap->getSize().x/2-component(wGmap, Button, 0)->getSize().x/2,
                                                                  wGmap->getPosition().y+wGmap->getSize().y  -component(wGmap, Button, 0)->getSize().y-5));

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

