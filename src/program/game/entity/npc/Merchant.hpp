/**
 * @file src/program/game/entity/npc/Merchant.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_MERCHANT_HPP
#define NPC_MERCHANT_HPP

#include "NPC.hpp"

namespace rr {

    class Merchant : public NPC {
    private: sf::Animation standingStill_;
    
             virtual void           initialize()                  override;
    
    public:  enum Type {
                 POTION_SELLER,
                 BOOK_SELLER,
                 WEAPON_SELLER,
                 ARMOR_SELLER,
                 ARTIFACT_SELLER
             } type_;

             Merchant(Type = POTION_SELLER);
             Merchant(Merchant const&);
/*
             virtual Entity*        clone       () const            override { return new Merchant(*this); }
*/
             virtual void           talk        ();
             virtual void           update      (sf::Time timeStep) override;
             virtual void           handleDamage(int damage)        override;
         
             virtual std::ifstream& operator<<  (std::ifstream&)    override;
             virtual std::ofstream& operator>>  (std::ofstream&)    override;
    };

}

#endif // NPC_MERCHANT_HPP
