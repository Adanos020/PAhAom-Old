/**
 * @file src/program/game/entities/chest/chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
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

        virtual void          draw           (sf::RenderWindow&) override;
        virtual void          setPosition    (sf::Vector2i pos)  override { body_.setPosition((sf::Vector2f)pos*80.f); }
        virtual void          setRealPosition(sf::Vector2f pos)  override { body_.setPosition(pos); }
        virtual bool          intersects     (Entity* e) const   override { return e->getBounds().intersects(getBounds()); }
        virtual sf::FloatRect getBounds      ()          const   override { return body_.getGlobalBounds(); }
        virtual sf::Vector2i  getPosition    ()          const   override { return (sf::Vector2i)body_.getPosition()/80; }
        virtual sf::Vector2f  getRealPosition()          const   override { return body_.getPosition(); }

    /// Returns the item which the chest contains
        Item*                 getItem        ()          const            { return item_; }
    };

}

#endif // chest_hpp
