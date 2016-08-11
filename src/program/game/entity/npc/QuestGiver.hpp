/**
 * @file src/program/game/entity/npc/QuestGiver.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_QUESTGIVER_HPP
#define NPC_QUESTGIVER_HPP

#include "NPC.hpp"

namespace rr {

    class QuestGiver : public NPC {
    private: sf::Animation standingStill_;
    
             virtual void           initialize()                  override;
    
    public:  enum Type {
                 NONE_YET
             } type_;
         
             QuestGiver(Type = NONE_YET);
             QuestGiver(QuestGiver const&);
/*
             virtual Entity*        clone       () const            override { return new QuestGiver(*this); }
*/
             virtual void           talk        ();
             virtual void           update      (sf::Time timeStep) override;
             virtual void           handleDamage(int damage)        override;
         
             virtual std::ifstream& operator<<  (std::ifstream&)    override;
             virtual std::ofstream& operator>>  (std::ofstream&)    override;
    };

}

#endif // NPC_QUESTGIVER_HPP
