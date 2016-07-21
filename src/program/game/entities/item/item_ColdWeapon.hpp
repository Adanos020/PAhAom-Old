/**
 * @file src/program/game/item/item_ColdWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_ColdWeapon_hpp
#define item_ColdWeapon_hpp

#include "item.hpp"

namespace rr {

    class ColdWeapon : public Equipable {
    private:
        float strengthRequired_;
        float damageDealt_;
        float speed_;
        float accuracy_;
        int   level_;

        virtual void           initialize    ()                  override;
    public:
        enum Type {
            HAMMER,
            DOUBLE_AXE,
            HALBERD,
            AXE,
            SERRATED_SWORD,
            LANCE,
            CLUB,
            SWORD,
            SPEAR,
            PIQUE,
            LONG_STICK,
            DAGGER,
            KNIFE
        } type_;

         ColdWeapon(Type, int amount = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
         ColdWeapon(ColdWeapon const&);
        ~ColdWeapon() {}

        virtual Entity*        clone              ()            const override { return new ColdWeapon(*this); }
        virtual Entity*        create             ()            const override { return new ColdWeapon(KNIFE); }

        virtual void           draw               (sf::RenderWindow&) override;

        virtual sf::String     getName            ()            const override;
        virtual sf::String     getDescription     ()            const override;
        
        virtual void           equip              (bool b)            override { equipped_ = b; }
        virtual void           reveal             ()                  override;

        void                   enhance            ();
        void                   enchant            ();

        float                  getStrengthRequired()            const          { return strengthRequired_; }
        float                  getDamageDelt      ()            const          { return damageDealt_; }
        float                  getSpeed           ()            const          { return speed_; }
        float                  getAccuracy        ()            const          { return accuracy_; }
        int                    getLevel           ()            const          { return level_; }

        virtual std::ifstream& operator<<    (std::ifstream&)    override;
        virtual std::ofstream& operator>>    (std::ofstream&)    override;
    };

}

#endif // item_ColdWeapon_hpp

