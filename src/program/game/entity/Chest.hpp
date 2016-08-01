/**
 * @file src/program/game/entity/Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_CHEST_HPP
#define ENTITY_CHEST_HPP

#include "../../funcs/items.hpp"

#include "Entity.hpp"
#include "item/Item.hpp"

namespace rr {

    class Item;

    class Chest : public Entity {
    private: sf::Sprite body_;
             Item*      item_;
         
             virtual void           initialize     ()                       override;
             virtual void           draw           (sf::RenderTarget&,
                                                    sf::RenderStates) const override;
    
    public:  enum Type {
                 REGULAR,
                 SPECIAL
             } type_;
         
             Chest(Type = REGULAR);
             Chest(Chest const&);
            ~Chest();
         
             virtual Entity*        clone          ()                 const override { return new Chest(*this); }
             virtual void           setGridPosition(sf::Vector2i pos)       override { body_.setPosition((sf::Vector2f)pos*80.f); }
             virtual void           setPosition    (sf::Vector2f pos)       override { body_.setPosition(pos); }
             virtual bool           collides       (Entity* e)        const override { return e->getBounds().intersects(getBounds()); }
             virtual sf::Vector2i   getGridPosition()                 const override { return (sf::Vector2i)body_.getPosition()/80; }
             virtual sf::Vector2f   getPosition    ()                 const override { return body_.getPosition(); }
             virtual sf::FloatRect  getBounds      ()                 const override { return body_.getGlobalBounds(); }
         
         /// Returns the item which the chest contains
             Item*                  getItem        ()                 const          { return item_; }
         
             virtual std::ifstream& operator<<     (std::ifstream&)    override;
             virtual std::ofstream& operator>>     (std::ofstream&)    override;
    };

}

#endif // ENTITY_CHEST_HPP
