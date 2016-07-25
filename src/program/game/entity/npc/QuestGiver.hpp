/**
 * @file src/program/game/entities/npc/QuestGiver.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_QUESTGIVER_HPP
#define NPC_QUESTGIVER_HPP

#include "NPC.hpp"

namespace rr {

    class QuestGiver : public NPC {
    private: virtual void           initialize()                  override;
    
    public:  enum Type {
                 NONE_YET
             } type_;
         
             QuestGiver(Type);
             QuestGiver(QuestGiver const&);
            ~QuestGiver() {}
         
             virtual Entity*        clone     () const            override { return new QuestGiver(*this); }
             virtual Entity*        create    () const            override { return new QuestGiver(NONE_YET); }
         
             virtual void           talk      ()                  override;
             virtual void           update    (sf::Time timeStep) override;
         
             virtual std::ifstream& operator<<(std::ifstream&)    override;
             virtual std::ofstream& operator>>(std::ofstream&)    override;
    };

}

#endif
