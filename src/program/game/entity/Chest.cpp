/**
 * @file src/program/game/entity/Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Chest.hpp"

#include "../../Resources.hpp"

#include "../../funcs/items.hpp"
#include "../../funcs/files.hpp"

extern rr::Resources resources;

namespace rr {

    Chest::Chest(Type t, Item* i)
    :
      Entity( ),
      item_ (i),
      type_ (t) {

        initialize();
    }

    Chest::Chest(Chest const& chest)
    :
      Entity(           ),
      body_ (chest.body_),
      item_ (chest.item_),
      type_ (chest.type_) {}

    Chest::~Chest() {
        delete item_;
    }

    void Chest::initialize() {
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
        body_.setTexture    (resources.texture.objects);
        body_.setScale      (sf::Vector2f(5.f, 5.f));
    }

    Entity* Chest::create() const {
        return new Chest(REGULAR, getRandomItem());
    }

    void Chest::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

    std::ifstream& Chest::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;
        item_ = getRandomItem();

        initialize();
        setPosition(position);

        return file;
    }

    std::ofstream& Chest::operator>>(std::ofstream& file) {
            file << 0                             << ' '
                 << (int)body_.getPosition().x/80 << ' '
                 << (int)body_.getPosition().y/80 << ' '
                 << type_                         << ' ';

        return file;
    }

}
