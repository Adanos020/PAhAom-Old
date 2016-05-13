/**
 * @file src/program/game/item/item_ColdWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_ColdWeapon_hpp
#define item_ColdWeapon_hpp

#include "item.hpp"

namespace rr {

    class ColdWeapon : public Item {
    private:
        float strengthRequired_;
        float damageDealt_;
        int   level_;
    public:
        enum Type {
            KNIFE,
            DAGGER,
            SWORD,
            MACE,
            AXE,
            SPEAR,
            HALBERD,
            LANCE,
            HAMMER,
            RUNIC_SWORD,
            SERRATED_SWORD
        } type_;

         ColdWeapon(Type, int amount);
        ~ColdWeapon();

        virtual void draw  (sf::RenderWindow&) override;

        void  enhance      ();
        void  enchant      ();

        float getStrength  () const;
        float getDamageDelt() const;
        int   getLevel     () const;
    };

}

#endif // item_ColdWeapon_hpp

