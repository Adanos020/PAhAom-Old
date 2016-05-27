/**
 * @file src/program/game/entities/stairs/stairs.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef stairs_hpp
#define stairs_hpp

#include "../entities.hpp"

namespace rr {

    class Stairs : public Entity {
    private:
        sf::Sprite   body_;
        sf::Vector2i position_;
        bool         upwards_;
    public:
         Stairs(bool upwards);
        ~Stairs() {}

        bool                  isUpwards      ()          const                { return upwards_; }

        virtual void          draw           (sf::RenderWindow&)     override;
        virtual void          setPosition    (sf::Vector2i position) override { setRealPosition((sf::Vector2f)position*80.f); }
        virtual void          setRealPosition(sf::Vector2f position) override { position_ = (sf::Vector2i)position/80; body_.setPosition(position); }

        virtual bool          intersects     (Entity* e) const       override { return e->getBounds().intersects(getBounds()); }
        virtual sf::FloatRect getBounds      ()          const       override { return body_.getGlobalBounds(); }
        virtual sf::Vector2i  getPosition    ()          const       override { return position_; }
        virtual sf::Vector2f  getRealPosition()          const       override { return body_.getPosition(); }

    };

}

#endif // stairs_hpp
