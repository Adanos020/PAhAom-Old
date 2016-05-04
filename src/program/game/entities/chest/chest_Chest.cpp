/**
 * @file src/program/game/entities/chest/chest_Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "chest.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Chest::Chest(Type t, Item* i) {
        _item = i;
        _type = t;

        int tu, tv;
        if (_type == REGULAR) {
            tu = (rand()%3+15)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%3+15)/(resources.texture.objects.getSize().y/16);
        }
        else if (_type == SPECIAL) {
            tu = (rand()%2+18)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%2+18)/(resources.texture.objects.getSize().y/16);
        }

        _body.setTextureRect(sf::IntRect(tu*16, tv*16, 16, 16));
        _body.setTexture(resources.texture.objects);
        _body.setScale(sf::Vector2f(5.f, 5.f));
    }

    Chest::~Chest() {
        delete _item;
    }
    void Chest::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
    }

}
