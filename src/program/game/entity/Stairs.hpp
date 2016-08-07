/**
 * @file src/program/game/entity/Stairs.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_STAIRS_HPP
#define ENTITY_STAIRS_HPP

#include "Entity.hpp"

namespace rr {

    class Stairs : public Entity {
    private: sf::Sprite   body_;
             sf::Vector2u position_;
             bool         upwards_;
             
             virtual void           initialize     ()                       override;
             virtual void           draw           (sf::RenderTarget&,
                                                    sf::RenderStates) const override;
    
    public:  Stairs(bool upwards = true);
             Stairs(Stairs const&);
         
             bool                   isUpwards      ()                 const          { return upwards_; }
         
             virtual Entity*        clone          ()                 const override { return new Stairs(*this); }

             virtual void           setGridPosition(sf::Vector2u pos)       override { body_.setPosition((sf::Vector2f)pos*80.f); }
             virtual void           setPosition    (sf::Vector2f pos)       override { body_.setPosition(pos); }
             virtual bool           collides       (Entity* e)        const override { return e->getBounds().intersects(getBounds()); }
             virtual sf::Vector2u   getGridPosition()                 const override { return (sf::Vector2u)body_.getPosition()/80u; }
             virtual sf::Vector2f   getPosition    ()                 const override { return body_.getPosition(); }
             virtual sf::FloatRect  getBounds      ()                 const override { return body_.getGlobalBounds(); }
         
             virtual std::ifstream& operator<<     (std::ifstream&)         override;
             virtual std::ofstream& operator>>     (std::ofstream&)         override;
    };

}

#endif // ENTITY_STAIRS_HPP
