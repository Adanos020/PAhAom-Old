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
        float speed_;
        float accuracy_;
        int   level_;
    public:
        enum Type {
            KNIFE,
            DAGGER,
            SWORD,
            SERRATED_SWORD,
            MACE,
            AXE,
            DOUBLE_AXE,
            SPEAR,
            HALBERD,
            LANCE,
            PIQUE,
            HAMMER
        } type_;

         ColdWeapon(Type, int amount, sf::Vector2i pos);
        ~ColdWeapon() {}

        virtual void draw  (sf::RenderWindow&) override;

        void  enhance      ();
        void  enchant      ();

        float getStrength  () const { return strengthRequired_; }
        float getDamageDelt() const { return damageDealt_; }
        float getSpeed     () const { return speed_; }
        float getAccuracy  () const { return accuracy_; }
        int   getLevel     () const { return level_; }
    };

}

#endif // item_ColdWeapon_hpp

