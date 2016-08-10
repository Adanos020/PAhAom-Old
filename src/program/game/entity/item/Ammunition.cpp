/**
 * @file src/program/game/item/Ammunition.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Ammunition.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr {

    Ammunition::Ammunition(Type type, int amount, sf::Vector2u position) :
      type_(type)
    {
        amount_ = amount;

        initialize();
        setGridPosition(position);
    }

    Ammunition::Ammunition(Ammunition const& copy) :
      type_(copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void Ammunition::initialize() {
        disposable_ = true;
        stackable_  = true;
        cursed_     = false;
        ID_         = type_ + 26;
        iconIndex_  = type_ + 55;

        setIcon(body_, iconIndex_);
    }

    sf::String Ammunition::getName() const {
        switch (type_) {
            case ARROW   : return Resources::dictionary["item.ammunition.name.arrow"   ];
            case BOLT    : return Resources::dictionary["item.ammunition.name.bolt"    ];
            case ROCKS   : return Resources::dictionary["item.ammunition.name.rocks"   ];
            case SHURIKEN: return Resources::dictionary["item.ammunition.name.shuriken"];
        }

        return "";
    }

    sf::String Ammunition::getDescription() const {
        switch (type_) {
            case ARROW   : return Resources::dictionary["item.ammunition.description.arrow"   ];
            case BOLT    : return Resources::dictionary["item.ammunition.description.bolt"    ];
            case ROCKS   : return Resources::dictionary["item.ammunition.description.rocks"   ];
            case SHURIKEN: return Resources::dictionary["item.ammunition.description.shuriken"];
        }

        return "";
    }

    std::ifstream& Ammunition::operator<<(std::ifstream& file) {
        sf::Vector2u position;
        int type;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);
            readFile <  int   > (file, amount_);
            readFile <  int   > (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();

        setGridPosition(position);
        
        return file;
    }

    std::ofstream& Ammunition::operator>>(std::ofstream& file) {
        file << 0                                  << ' '
             << (unsigned) body_[0].position.x/80u << ' '
             << (unsigned) body_[0].position.y/80u << ' '
             << amount_                            << ' '
             << type_;

        return file;
    }

}
