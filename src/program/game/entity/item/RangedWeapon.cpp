/**
 * @file src/program/game/item/RangedWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "RangedWeapon.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

namespace rr {

    RangedWeapon::RangedWeapon(Type type, int amount, sf::Vector2i position) :
      type_(type)
    {
        level_      = 0;
        identified_ = false;
        amount_ = amount;

        initialize();
        setGridPosition(position);
    }

    RangedWeapon::RangedWeapon(RangedWeapon const& copy) :
      type_(copy.type_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void RangedWeapon::initialize() {
        disposable_ = false;
        stackable_  = false;
        cursed_     = chance(1, 4);
        ID_         = type_ + 23;
        iconIndex_  = type_ + 52;

        setIcon(body_, iconIndex_);
    }

    sf::String RangedWeapon::getName() const {
        switch (type_) {
            case BOW      : return Resources::dictionary["item.ranged_weapon.name.bow"      ];
            case CROSSBOW : return Resources::dictionary["item.ranged_weapon.name.crossbow" ];
            case SLINGSHOT: return Resources::dictionary["item.ranged_weapon.name.slingshot"];
        }

        return "";
    }

    sf::String RangedWeapon::getDescription() const {
        sf::String description = "";
        switch (type_) {
            case BOW      : description += Resources::dictionary["item.ranged_weapon.description.bow"      ]; break;
            case CROSSBOW : description += Resources::dictionary["item.ranged_weapon.description.crossbow" ]; break;
            case SLINGSHOT: description += Resources::dictionary["item.ranged_weapon.description.slingshot"]; break;
        }

        return description;
    }

    void RangedWeapon::enhance() {
        level_       ++;
        speed_       ++;
        accuracy_    ++;
        damageDealt_ += 5;
        requirement_ -= 3;
    }

    void RangedWeapon::enchant() {

    }

    std::ifstream& RangedWeapon::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int type;

        try {
            readFile <int > (file, position.x);
            readFile <int > (file, position.y);
            readFile <int > (file, amount_);
            readFile <bool> (file, identified_);
            readFile <bool> (file, equipped_);
            readFile <int > (file, level_);
            readFile <int > (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();

        speed_       += level_;
        accuracy_    += level_;
        damageDealt_ += level_*5;
        requirement_ -= level_*3;

        setGridPosition(position);

        return file;
    }

    std::ofstream& RangedWeapon::operator>>(std::ofstream& file) {
        file << 6                            << ' '
             << (int) body_[0].position.x/80 << ' '
             << (int) body_[0].position.y/80 << ' '
             << amount_                      << ' '
             << identified_                  << ' '
             << equipped_                    << ' '
             << level_                       << ' '
             << type_;

        return file;
    }

}
