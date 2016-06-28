/**
 * @file src/program/game/entities/chest/chest_Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "chest.hpp"
#include "../../../program.hpp"
#include "../../../funcs/items.hpp"

extern rr::Resources resources;

namespace rr {

    Chest::Chest(Type t, Item* i)
        : Entity(),
          item_ (i),
          type_ (t) {

        int tu, tv;
        if (type_ == SPECIAL) {
            tu = (rand()%2+18)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%2+18)/(resources.texture.objects.getSize().y/16);
        }
        else {
            tu = (rand()%3+15)%(resources.texture.objects.getSize().x/16);
            tv = (rand()%3+15)/(resources.texture.objects.getSize().y/16);
        }

        body_.setTextureRect(sf::IntRect(tu*16, tv*16, 16, 16));
        body_.setTexture(resources.texture.objects);
        body_.setScale(sf::Vector2f(5.f, 5.f));
    }

    Chest::Chest(Chest const& chest)
        : Entity(),
          body_ (chest.body_),
          item_ (chest.item_),
          type_ (chest.type_) {}

    Chest::~Chest() {
        delete item_;
    }

    Entity* Chest::create() const {
         return new Chest(REGULAR, getItemFromID(1, 1));
    }

    void Chest::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

}
