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

    Chest::Chest(sf::Vector2f position, Type t, Item* i) {
        item = i;
        type = t;

        int tu, tv;
        if (type == REGULAR) {
            tu = (rand()%3+15)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%3+15)/(resources.texture.objects.getSize().y/16);
        }
        else if (type == SPECIAL) {
            tu = (rand()%2+18)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%2+18)/(resources.texture.objects.getSize().y/16);
        }

        body.setTextureRect(sf::IntRect(tu*16, tv*16, 16, 16));
        body.setTexture(resources.texture.objects);
        body.setScale(sf::Vector2f(5.f, 5.f));
        body.setPosition(position);
    }

    Chest::~Chest() {
        //delete item;
    }

    void Chest::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
    }

    void Chest::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }

}
