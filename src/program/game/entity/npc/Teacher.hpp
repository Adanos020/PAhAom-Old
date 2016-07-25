/**
 * @file src/program/game/entities/npc/Teacher.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_TEACHER_HPP
#define NPC_TEACHER_HPP

#include "NPC.hpp"

namespace rr {

    class Teacher : public NPC {
    private: virtual void           initialize()                   override;
    
    public:  enum Type {
                 SWORDSMAN,
                 SHARPSHOOTER,
                 CARPENTER,
                 MAGE,
                 KUNG_FU_MASTER
             } type_;
         
             Teacher(Type);
             Teacher(Teacher const&);
            ~Teacher() {}
         
             virtual Entity*        clone     () const             override { return new Teacher(*this); }
             virtual Entity*        create    () const             override { return new Teacher(SWORDSMAN); }
         
             virtual void           talk      ()                   override;
             virtual void           update    (sf::Time timeStep)  override;
         
             virtual std::ifstream& operator<<(std::ifstream&)     override;
             virtual std::ofstream& operator>>(std::ofstream&)     override;
    };

}

#endif
