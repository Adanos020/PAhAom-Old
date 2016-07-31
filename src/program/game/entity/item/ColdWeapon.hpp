/**
 * @file src/program/game/item/ColdWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_COLDWEAPON_HPP
#define ITEM_COLDWEAPON_HPP

#include "Item.hpp"

namespace rr {

    class ColdWeapon : public Equipable {
    private: float strengthRequired_;
             float damageDealt_;
             float speed_;
             float accuracy_;
             int   level_;
             bool  identified_;
         
             virtual void           initialize    ()                  override;
    
    public:  enum Type {
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
         
             ColdWeapon(Type = HAMMER, int amount = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
             ColdWeapon(ColdWeapon const&);
         
             virtual Entity*        clone              ()            const override { return new ColdWeapon(*this); }
         
             virtual void           draw               (sf::RenderWindow&) override;
         
             virtual sf::String     getName            ()            const override;
             virtual sf::String     getDescription     ()            const override;
         
             virtual void           equip              (bool b)            override { equipped_ = b; }
             virtual bool           isEquipped         ()            const override { return equipped_; }
         
             virtual void           reveal             ()                  override;
             virtual bool           isDiscovered       ()            const override { return identified_; }
         
             void                   enhance            ();
             void                   enchant            ();
         
             float                  getStrengthRequired()            const          { return strengthRequired_; }
             float                  getDamageDealt     ()            const          { return damageDealt_; }
             float                  getSpeed           ()            const          { return speed_; }
             float                  getAccuracy        ()            const          { return accuracy_; }
             int                    getLevel           ()            const          { return level_; }
         
             virtual std::ifstream& operator<<    (std::ifstream&)    override;
             virtual std::ofstream& operator>>    (std::ofstream&)    override;
    };

}

#endif // ITEM_COLDWEAPON_HPP
