/**
 * @file src/program/game/item/Food.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Food.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

namespace rr {

    Food::Food(Type type, int amount, sf::Vector2i position) :
      type_(type)
    {
        amount_ = amount;

        initialize();
        setGridPosition(position);
    }

    Food::Food(Food const& copy) :
      type_(copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void Food::initialize() {
        disposable_ = true;
        stackable_  = true;
        cursed_     = false;
        ID_         = type_ + 61;
        iconIndex_  = type_ + 80;

        setIcon(body_, iconIndex_);
    }

    sf::String Food::getName() const {
        switch (type_) {
            case MEAT     : return Resources::dictionary["item.food.name.meat"     ];
            case SANDVICH : return Resources::dictionary["item.food.name.sandvich" ];
            case APPLE    : return Resources::dictionary["item.food.name.apple"    ];
            case BEER     : return Resources::dictionary["item.food.name.beer"     ];
            case HOT_DOG  : return Resources::dictionary["item.food.name.hot_dog"  ];
            case HAMBURGER: return Resources::dictionary["item.food.name.hamburger"];
            case BAGUETTE : return Resources::dictionary["item.food.name.baguette" ];
         // case DUMPLING : return Resources::dictionary["item.food.name.dumpling" ];
        }
        return "";
    }

    sf::String Food::getDescription() const {
        switch (type_) {
            case MEAT     : return Resources::dictionary["item.food.description.meat"     ];
            case SANDVICH : return Resources::dictionary["item.food.description.sandvich" ];
            case APPLE    : return Resources::dictionary["item.food.description.apple"    ];
            case BEER     : return Resources::dictionary["item.food.description.beer"     ];
            case HOT_DOG  : return Resources::dictionary["item.food.description.hot_dog"  ];
            case HAMBURGER: return Resources::dictionary["item.food.description.hamburger"];
            case BAGUETTE : return Resources::dictionary["item.food.description.baguette" ];
         // case DUMPLING : return Resources::dictionary["item.food.description.dumpling" ];
        }
        return "";
    }

    std::ifstream& Food::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, amount_);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Food::operator>>(std::ofstream& file) {
        file << 4                            << ' '
             << (int) body_[0].position.x/80 << ' '
             << (int) body_[0].position.y/80 << ' '
             << amount_                      << ' '
             << type_;

        return file;
    }

}
