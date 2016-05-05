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
        sf::Sprite body_;
        Item*      item_;
    public:
        enum Type {
            REGULAR,
            SPECIAL
        } type_;
         Chest(Type t, Item*);
        ~Chest();

        void          setPosition    (sf::Vector2i pos)  override { body_.setPosition((sf::Vector2f)pos*80.f); }
        void          setRealPosition(sf::Vector2f pos)  override { body_.setPosition(pos); }
        void          draw           (sf::RenderWindow&) override;
        bool          intersects     (Entity* e) const   override { return e->getBounds().intersects(getBounds()); }
        sf::FloatRect getBounds      ()          const   override { return body_.getGlobalBounds(); }
        Item*         getItem        ()          const { return item_; }

        virtual void setOpen         (bool)            {}
        virtual bool isOpen          ()          const { return false; }
    };

}

#endif // chest_hpp
