/**
 * @file src/program/game/menus/menus_GameMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    GameMap::GameMap() {
        _shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        _shadow.setPosition(sf::Vector2f(0, 0));
        _shadow.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        _wGmap = new Window(resources.dictionary["gui.window.game_map"], sf::Vector2f(settings.graphics.resolution.x*0.77f , settings.graphics.resolution.y*0.745f+77),
                                                                         sf::Vector2f(settings.graphics.resolution.x*0.115f, settings.graphics.resolution.y*0.1275f-25));
            *_wGmap += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
            component(_wGmap, Button, 0)->setPosition(sf::Vector2f(_wGmap->getPosition().x+_wGmap->getSize().x/2-component(_wGmap, Button, 0)->getSize().x/2,
                                                                   _wGmap->getPosition().y+_wGmap->getSize().y  -component(_wGmap, Button, 0)->getSize().y-5));

#undef component

    }

    GameMap::~GameMap() {
        delete _wGmap;
    }

    void GameMap::open() {
        _wGmap->setVisible(true);
    }

    void GameMap::close() {
        _wGmap->setVisible(false);
    }

    void GameMap::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)

        if (_wGmap->isVisible()) {
            if (component(_wGmap, Button, 0)->isPressed(rw, e)) {
                g->pause(false);
            }
        }

#undef component

    }

    void GameMap::draw(sf::RenderWindow& rw) {
        rw.draw(_shadow);
        _wGmap->draw(rw);
    }

    bool GameMap::isOpen() {
        return _wGmap->isVisible();
    }

}

