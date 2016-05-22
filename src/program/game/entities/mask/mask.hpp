/**
 * @file src/program/game/entities/mask/mask.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef mask_hpp
#define mask_hpp

#include "../entities.hpp"

namespace rr {

    class Mask : public Entity {
    private:
        sf::RectangleShape body_;
        sf::Vector2i       position_;

        bool               seen_;
    public:
        Mask();

        void see   (bool seen);
        bool isSeen()          { return seen_; }

        virtual void          draw           (sf::RenderWindow&);
        virtual void          setPosition    (sf::Vector2i position) override { position_ = position; body_.setPosition(sf::Vector2f(position_.x*80, position_.y*80)); }
        virtual void          setRealPosition(sf::Vector2f position) override { body_.setPosition(position); }

        virtual bool          intersects     (Entity* e) const       override { return e->getBounds().intersects(getBounds()); }
        virtual sf::FloatRect getBounds      ()          const       override { return body_.getGlobalBounds(); }
        virtual sf::Vector2i  getPosition    ()          const       override { return position_; }
        virtual sf::Vector2f  getRealPosition()          const       override { return body_.getPosition(); }
    };

}

#endif // mask_hpp
