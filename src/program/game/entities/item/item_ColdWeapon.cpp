/**
 * @file src/program/game/item/item_ColdWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_ColdWeapon.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    ColdWeapon::ColdWeapon(Type type, int amount) {
        type_   = type;
        amount_ = amount;

        switch (type_) {
            case KNIFE: damageDealt_ = 5; break;

        }
    }

}
