/**
 * @file src/program/game/entity/Door.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_DOOR_HPP
#define ENTITY_DOOR_HPP

#include "Entity.hpp"

namespace rr {

    class Door : public Entity {
    private: sf::Sprite body_;
             bool       locked_;
             bool       open_;
             bool       withoutWindow_;
             
             virtual void           initialize     ()                       override;
             virtual void           draw           (sf::RenderTarget&,
                                                    sf::RenderStates) const override;
    
    public:  Door(bool lock = false);
             Door(Door const&);
         
             void                   setOpen        (bool);
             bool                   isOpen         ()                 const          { return open_; }
             bool                   isLocked       ()                 const          { return locked_; }
             bool                   isWithoutWindow()                 const          { return withoutWindow_; }
         
             virtual Entity*        clone          ()                 const override { return new Door(*this); }

             virtual void           setGridPosition(sf::Vector2i pos)       override { body_.setPosition((sf::Vector2f)pos*80.f); }
             virtual void           setPosition    (sf::Vector2f pos)       override { body_.setPosition(pos); }
             virtual bool           collides       (Entity* e)        const override { return e->getBounds().intersects(getBounds()); }
             virtual sf::Vector2i   getGridPosition()                 const override { return (sf::Vector2i)body_.getPosition()/80; }
             virtual sf::Vector2f   getPosition    ()                 const override { return body_.getPosition(); }
             virtual sf::FloatRect  getBounds      ()                 const override { return body_.getGlobalBounds(); }
         
             virtual std::ifstream& operator<<     (std::ifstream&)         override;
             virtual std::ofstream& operator>>     (std::ofstream&)         override;
    };

}

#endif // ENTITY_DOOR_HPP
