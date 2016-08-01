/**
 * @file src/program/game/entity/npc/NPC.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_HPP
#define NPC_HPP

#include "../../../../../lib/AnimatedSprite.hpp"
#include "../../../gui/ALL.hpp"
#include "../../../Resources.hpp"

#include "../Entity.hpp"

namespace rr {

    class NPC : public Entity {
    protected: sf::AnimatedSprite body_;
               sf::Animation*     currentAnimation_;
               
               sf::String         attitude_;

               virtual void          draw            (sf::RenderTarget& target, sf::RenderStates states) const override {
                   states.texture = &Resources::texture.items;
                   target.draw(body_, states);
               }
    
    public:    virtual ~NPC() {}
       
               virtual void          update          (sf::Time timeStep) = 0;
               virtual void          handleDamage    (int damage)        = 0;
               virtual void          setGridPosition (sf::Vector2i pos) override { body_.setPosition((sf::Vector2f)pos*80.f); }
               virtual sf::Vector2i  getGridPosition ()          const  override { return (sf::Vector2i) body_.getPosition()/80; }
               virtual void          setPosition     (sf::Vector2f pos) override { body_.setPosition(pos); }
               virtual sf::Vector2f  getPosition     ()          const  override { return body_.getPosition(); }
               virtual bool          collides        (Entity* e) const  override { return e->getBounds().intersects(getBounds()); }
               virtual sf::FloatRect getBounds       ()          const  override { return body_.getGlobalBounds(); }

               sf::String            getAttitude     ()          const           { return attitude_; }
    };

}

#endif // NPC_HPP

