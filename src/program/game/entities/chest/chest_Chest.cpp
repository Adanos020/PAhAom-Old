/**
 * @file src/program/game/entities/chest/chest_Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "chest.hpp"
#include "../../../program.hpp"
#include "../../../funcs/items.hpp"
#include "../../../funcs/files.hpp"

extern rr::Resources resources;

namespace rr {

    Chest::Chest(Type t, Item* i)
    : Entity( ),
      item_ (i),
      type_ (t) {

        initialize();
    }

    Chest::Chest(Chest const& chest)
    : Entity(           ),
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
        int type, itemType;
        Item* item;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
            readFile <int> (file, itemType);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        switch (itemType) {
            case 2: item = new Book      (Book::CRAFTING                ); *item << file; break;
            case 3: item = new Coin      (Coin::BRONZE, Coin::SMALL     ); *item << file; break;
            case 4: item = new ColdWeapon(ColdWeapon::KNIFE             ); *item << file; break;
            case 5: /* ERROR 404 */                                                       break;
            case 6: item = new Potion    (Potion::HEALING, Potion::SMALL); *item << file; break;
            case 7: /* ERROR 404 */                                                       break;
            case 8: item = new Rune      (Rune::HEAL                    ); *item << file; break;
        }

        initialize();
        setPosition(position);

        return file;
    }

    std::ofstream& Chest::operator>>(std::ofstream& file) {
            file << 0                             << ' '
                 << (int)body_.getPosition().x/80 << ' '
                 << (int)body_.getPosition().y/80 << ' '
                 << type_                         << ' ';
            *item_ >> file;

        return file;
    }

}
