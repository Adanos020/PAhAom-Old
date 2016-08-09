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

namespace rr {

    Chest::Chest(Type t) :
      item_ (getRandomItem()),
      type_ (t              )
    {
        initialize();
    }

    Chest::Chest(Chest const& copy) :
      body_(copy.body_),
      item_(copy.item_),
      type_(copy.type_) {}

    Chest::~Chest() {
        delete item_;
    }

    void Chest::initialize() {
        int tu, tv;
        if (type_ == SPECIAL) {
            tu = (rand()%2+18)%(Resources::texture.objects.getSize().x/16);
            tv = (rand()%2+18)/(Resources::texture.objects.getSize().y/16);
        }
        else {
            tu = (rand()%3+15)%(Resources::texture.objects.getSize().x/16);
            tv = (rand()%3+15)/(Resources::texture.objects.getSize().y/16);
        }

        body_.setTextureRect(sf::IntRect(tu*16, tv*16, 16, 16));
        body_.setTexture    (Resources::texture.objects);
        body_.setScale      (sf::Vector2f(5.f, 5.f));
    }

    void Chest::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &Resources::texture.objects;
        target.draw(body_, states);
    }

    std::ifstream& Chest::operator<<(std::ifstream& file) {
        sf::Vector2u position;
        int type;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);
            readFile <   int  > (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;
        item_ = getRandomItem();

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Chest::operator>>(std::ofstream& file) {
            file << 0                                    << ' '
                 << (unsigned) body_.getPosition().x/80u << ' '
                 << (unsigned) body_.getPosition().y/80u << ' '
                 << type_                                << ' ';

        return file;
    }

}
