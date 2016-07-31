/**
 * @file src/program/game/entities/npc/NPC.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_HPP
#define NPC_HPP

#include "../Entity.hpp"
#include "../../../../../lib/AnimatedSprite.hpp"
#include "../../../gui/ALL.hpp"

namespace rr {

    class NPC : public Entity {
    protected: sf::AnimatedSprite body_;
               sf::Animation*     currentAnimation_;
               
               sf::String         attitude_;
    
    public:    virtual ~NPC() {}
       
               virtual void          update          (sf::Time timeStep) = 0;
               virtual void          handleDamage    (int damage)        = 0;
       
               virtual void          draw            (sf::RenderWindow& rw) override { rw.draw(body_); }
               virtual void          setPosition     (sf::Vector2i pos)     override { body_.setPosition((sf::Vector2f)pos*80.f); }
               virtual void          setRealPosition (sf::Vector2f pos)     override { body_.setPosition(pos); }
       
               virtual bool          intersects      (Entity* e) const      override { return e->getBounds().intersects(getBounds()); }
               virtual sf::FloatRect getBounds       ()          const      override { return body_.getGlobalBounds(); }
               virtual sf::Vector2i  getPosition     ()          const      override { return (sf::Vector2i)body_.getPosition()/80; }
               virtual sf::Vector2f  getRealPosition ()          const      override { return body_.getPosition(); }

               sf::String            getAttitude     ()          const      	     { return attitude_; }
    };

}

#endif // NPC_HPP

