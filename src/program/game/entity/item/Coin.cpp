/**
 * @file src/program/game/item/Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Coin.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr {

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos) :
      Item()
    {
        amount_ = am;
        type_   = t;
        size_   = s;

        initialize();
        setGridPosition(pos);
    }

    Coin::Coin(Coin const& coin) :
      Item (          ),
      type_(coin.type_)
    {
        amount_     = coin.amount_;
        disposable_ = coin.disposable_;
        stackable_  = coin.stackable_;
        ID_         = coin.ID_;
        iconIndex_  = coin.iconIndex_;
        body_       = coin.body_;
    }

    void Coin::initialize() {
        disposable_ = false;
        stackable_  = true;
        cursed_     = false;
        ID_         = 3*size_ + type_ + 1;
        iconIndex_  = type_ + (size_+2)*16 + 1;

        setIcon(body_, iconIndex_);
    }
    
    sf::String Coin::getName() const {
        switch (type_) {
            case BRONZE: return Resources::dictionary["item.coin.bronze"];
            case SILVER: return Resources::dictionary["item.coin.silver"];
            case GOLDEN: return Resources::dictionary["item.coin.gold"  ];
        }
        return "";
    }

    sf::String Coin::getDescription() const {
        return "";
    }

    std::ifstream& Coin::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type, size;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, amount_);
            readFile <int> (file, type);
            readFile <int> (file, size);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;
        size_ = (Size) size;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Coin::operator>>(std::ofstream& file) {
        file << 3                           << ' '
             << (int)body_[0].position.x/80 << ' '
             << (int)body_[0].position.y/80 << ' '
             << amount_                     << ' '
             << type_                       << ' '
             << size_;

        return file;
    }

}
