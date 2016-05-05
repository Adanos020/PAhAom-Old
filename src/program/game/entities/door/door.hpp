/**
 * @file src/program/game/entities/door/door.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "../entities.hpp"

namespace rr {

    class Door : public Entity {
    private:
        sf::Sprite body_;
        bool       locked_;
        bool       open_;
        bool       withoutWindow_;
    public:
         Door(bool lock);
        ~Door();

        void          setOpen        (bool);
        bool          isOpen         ()          const            { return open_; }

        void          setPosition    (sf::Vector2i pos)  override { body_.setPosition((sf::Vector2f)pos*80.f); }
        void          setRealPosition(sf::Vector2f pos)  override { body_.setPosition(pos); }
        void          draw           (sf::RenderWindow&) override;
        bool          intersects     (Entity* e) const   override { return e->getBounds().intersects(getBounds()); }
        sf::FloatRect getBounds      ()          const   override { return body_.getGlobalBounds(); }

        virtual Item* getItem        ()          const   override { return nullptr; }
        virtual sf::Vector2i  getPosition    ()  const   override { return (sf::Vector2i)body_.getPosition()/80; }
        virtual sf::Vector2f  getRealPosition()  const   override { return body_.getPosition(); }
    };

}
