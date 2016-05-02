/**
 * @file src/program/game/entities/door/door.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "../entities.hpp"

namespace rr {

    class Door : public Entity {
    private:
        sf::Sprite body;
        bool locked;
        bool open;
    public:
         Door(bool lock);
        ~Door();

        void          setOpen    (bool);
        bool          isOpen     ()                           { return open; }

        void          setPosition(sf::Vector2f pos)  override { body.setPosition(pos); }
        void          draw       (sf::RenderWindow&) override;
        bool          intersects (Entity* e) const   override { return e->getBounds().intersects(this->getBounds()); }
        sf::FloatRect getBounds  ()          const   override { return body.getGlobalBounds(); }
    };

}
