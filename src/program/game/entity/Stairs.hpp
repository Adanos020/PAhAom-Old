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
             sf::Vector2i position_;
             bool         upwards_;
             
             virtual void           initialize     ()                      override;
    
    public:  Stairs(bool upwards = true);
             Stairs(Stairs const&);
         
             bool                   isUpwards      ()          const                { return upwards_; }
         
             virtual Entity*        clone          ()          const       override { return new Stairs(*this); }
         
             virtual void           draw           (sf::RenderWindow&)     override;
             virtual void           setPosition    (sf::Vector2i position) override { position_ = position; setRealPosition((sf::Vector2f)position*80.f); }
             virtual void           setRealPosition(sf::Vector2f position) override { position_ = (sf::Vector2i)position/80; body_.setPosition(position); }
         
             virtual bool           intersects     (Entity* e) const       override { return e->getBounds().intersects(getBounds()); }
             virtual sf::FloatRect  getBounds      ()          const       override { return body_.getGlobalBounds(); }
             virtual sf::Vector2i   getPosition    ()          const       override { return position_; }
             virtual sf::Vector2f   getRealPosition()          const       override { return body_.getPosition(); }
         
             virtual std::ifstream& operator<<     (std::ifstream&)        override;
             virtual std::ofstream& operator>>     (std::ofstream&)        override;
    };

}

#endif // ENTITY_STAIRS_HPP
