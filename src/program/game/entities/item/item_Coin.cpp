/**
 * @file src/program/game/item/item_Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Coin.hpp"
#include "../../../program.hpp"
#include "../../../funcs/images.hpp"

extern rr::Resources resources;

namespace rr {

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos)
    : Item() {
 
        amount_     = am;
        type_       = t;
        size_       = s;
        disposable_ = false;
        stackable_  = true;
        ID_         = 3*size_ + type_ + 1;
        iconIndex_  = type_ + (size_+2)*16 + 1;

        switch (type_) {
            case BRONZE: name_ = resources.dictionary["item.coin.bronze"]; break;
            case SILVER: name_ = resources.dictionary["item.coin.silver"]; break;
            case GOLDEN: name_ = resources.dictionary["item.coin.gold"  ]; break;
        }

        setIcon    (body_, iconIndex_);
        setPosition(pos);
    }

    Coin::Coin(Coin const& coin)
    : Item (          ),
      type_(coin.type_) {

        amount_     = coin.amount_;
        disposable_ = coin.disposable_;
        stackable_  = coin.stackable_;
        ID_         = coin.ID_;
        iconIndex_  = coin.iconIndex_;
        name_       = coin.name_;
        body_       = coin.body_;
    }

    void Coin::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

}
