/**
 * @file src/program/game/entity/Shadow.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_SHADOW_HPP
#define ENTITY_SHADOW_HPP

#include "Entity.hpp"

#include "../../funcs/images.hpp"

namespace rr {

    class Shadow : public Entity {
    private: sf::VertexArray body_;
             sf::Vector2i    position_;
         
             bool            seen_;
             bool            discovered_;
             bool            flipped_;
         
             virtual void           initialize     ()                      override;
    
    public:  Shadow();
             Shadow(Shadow const&);
            ~Shadow() {}
     
             void                   see            (bool seen);
             bool                   isSeen         ()                               { return seen_; }
             bool                   isDiscovered   ()                               { return discovered_; }
             void                   setFadeOut     (sf::Color[]);
     
             virtual Entity*        clone          ()          const       override { return new Shadow(*this); }
             virtual Entity*        create         ()          const       override { return new Shadow(); }
     
             virtual void           draw           (sf::RenderWindow&)     override;
             virtual void           setPosition    (sf::Vector2i position) override { setRealPosition((sf::Vector2f)position*80.f); }
             virtual void           setRealPosition(sf::Vector2f position) override { position_ = (sf::Vector2i)position/80; rr::setPosition(body_, position); }
     
             virtual bool           intersects     (Entity* e) const       override { return e->getBounds().intersects(getBounds()); }
             virtual sf::FloatRect  getBounds      ()          const       override { return sf::FloatRect(body_[0].position, body_[3].position-body_[0].position); }
             virtual sf::Vector2i   getPosition    ()          const       override { return position_; }
             virtual sf::Vector2f   getRealPosition()          const       override { return body_[0].position; }
     
             virtual std::ifstream& operator<<     (std::ifstream&)        override;
             virtual std::ofstream& operator>>     (std::ofstream&)        override;
    };

}

#endif // ENTITY_SHADOW_HPP
