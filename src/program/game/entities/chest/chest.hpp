/**
 * @file src/program/game/entities/chest/chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef chest_hpp
#define chest_hpp

#include <SFML/Graphics.hpp>

#include "../entities.hpp"

namespace rr {

    class Item;

    class Chest : public Entity {
    private:
        sf::Sprite _body;
        Item*      _item;
    public:
        enum Type {
            REGULAR,
            SPECIAL
        } _type;
         Chest(Type t, Item*);
        ~Chest();

        void          setPosition(sf::Vector2i pos)  override { _body.setPosition((sf::Vector2f)pos*80.f); }
        void          draw       (sf::RenderWindow&) override;
        bool          intersects (Entity* e) const   override { return e->getBounds().intersects(getBounds()); }
        sf::FloatRect getBounds  ()          const   override { return _body.getGlobalBounds(); }

        Item*         getItem    ()          const { return _item; }
    };

}

#endif // chest_hpp
