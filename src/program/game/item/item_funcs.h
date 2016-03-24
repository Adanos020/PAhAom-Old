#ifndef item_funcs_h
#define item_funcs_h

#include "item.h"

namespace rr {

    Item* getItemFromID(double ID, int amount, sf::Vector2f pos) {
        /*unknown ID?*/
        return new Potion(ID, "Unknown ID", 0, amount, 0, pos);
    }

}

#endif // item_funcs_h
