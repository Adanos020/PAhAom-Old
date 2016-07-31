/**
 * @file src/program/game/entity/npc/Bandit.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_BANDIT_HPP
#define NPC_BANDIT_HPP

#include "NPC.hpp"

#include "../Player.hpp"

namespace rr {

    class Bandit : public NPC {
    private: struct Attrs {
                 float health;
                 float maxHealth;
                 int   level;
                 float armor;
             } attrs_;

             sf::Animation standingLeft_;
             sf::Animation standingRight_;
             sf::Animation walkingLeft_;
             sf::Animation walkingRight_;
             sf::Animation attackingLeft_;
             sf::Animation attackingRight_;

             bool          asleep_;
             bool          walking_;
    
             virtual void           initialize()                   override;
    
    public:  enum Weapon {
                 CLUB,
                 CROSSBOW,
                 DAGGER
             } weapon_;
    
             Bandit(Weapon = CLUB, bool asleep = true);
             Bandit(Bandit const&);
         
             virtual Entity*        clone       () const             override { return new Bandit(*this); }

             virtual void           update      (sf::Time timeStep)  override;
             virtual void           handleDamage(int damage)         override;

             void                   attack      (NPC*);
             void                   attack      (Player*);
         
             virtual std::ifstream& operator<<  (std::ifstream&)     override;
             virtual std::ofstream& operator>>  (std::ofstream&)     override;
    };

}

#endif // NPC_BANDIT_HPP
