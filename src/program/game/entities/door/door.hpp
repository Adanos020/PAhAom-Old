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
        sf::Sprite _body;
        bool       _locked;
        bool       _open;
        bool       _withoutWindow;
    public:
         Door(bool lock);
        ~Door();

        void          setOpen    (bool);
        bool          isOpen     () const                     { return _open; }

        void          setPosition(sf::Vector2i pos)  override { _body.setPosition((sf::Vector2f)pos*80.f); }
        void          draw       (sf::RenderWindow&) override;
        bool          intersects (Entity* e) const   override { return e->getBounds().intersects(getBounds()); }
        sf::FloatRect getBounds  ()          const   override { return _body.getGlobalBounds(); }
    };

}
