/**
 * @file src/program/game/entities/item/Item.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

#include "../../../Resources.hpp"

#include "../Entity.hpp"

namespace rr {

/// Class for an item
    class Item : public Entity {
    protected: sf::VertexArray body_;
               bool            disposable_;
               bool            stackable_;
               bool            cursed_;
               int             ID_;
               int             amount_;
               unsigned        iconIndex_;

               virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
                   states.texture = &Resources::texture.items;
                   target.draw(body_, states);
               }
    
    public:	   virtual ~Item() {}
               
           /// Changes the amount
               virtual void               setAmount      (int x)                     { amount_ = x; }
           /// Returns the item's ID
               virtual int                getID          ()          const           { return ID_; }
           /// Returns the amount of this item
               virtual int                getAmount      ()          const           { return amount_; }
           /// Tells if the item is disposable
               virtual bool               isDisposable   ()          const           { return disposable_; }
           /// Tells if the item is stackable
               virtual bool               isStackable    ()          const           { return stackable_; }
           /// Tells if the item is cursed
               virtual bool               isCursed       ()          const           { return cursed_; }
           /// Returns the sprite of this item
               virtual sf::VertexArray    getBody        ()          const           { return body_; }
           /// Returns the name of this item
               virtual sf::String         getName        ()          const = 0;
           /// Returns the description of this item
               virtual sf::String         getDescription ()          const = 0;
           /// Returns the texture's icon index
               virtual unsigned           getIconIndex   ()          const           { return iconIndex_; }
               
               virtual void               setGridPosition(sf::Vector2u pos) override {
                   body_[0].position = (sf::Vector2f)pos*80.f;
                   body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
                   body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
                   body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);
               }
               virtual sf::Vector2u       getGridPosition()          const  override { return (sf::Vector2u) body_[0].position/80u; }
               virtual void               setPosition    (sf::Vector2f pos) override {
                   body_[0].position =               pos;
                   body_[1].position =  sf::Vector2f(pos.x+80, pos.y);
                   body_[2].position =  sf::Vector2f(pos.x+80, pos.y+80);
                   body_[3].position =  sf::Vector2f(pos.x   , pos.y+80);
               }
               virtual sf::Vector2f       getPosition()              const  override { return body_[0].position/80.f; }
               virtual bool               collides       (Entity* e) const  override { return (e->getBounds().intersects(getBounds())); }
               virtual sf::FloatRect      getBounds      ()          const  override { return sf::FloatRect(body_[0].position, body_[2].position-body_[0].position); }
    };

    class Discoverable : public Item {
    public: virtual ~Discoverable() {}

        /// Reveals the item's properties
            virtual void reveal      ()       = 0;
        /// Tells if the item is discovered
            virtual bool isDiscovered() const = 0;
    };

    class Equipable : public Discoverable {
    protected: bool equipped_ = false;
    
    public:    virtual ~Equipable() {}

           /// Equips or unequips the item
               virtual void equip     (bool)   = 0;
           /// Tells if the item is equipped
               virtual bool isEquipped() const = 0;
    };

    class Weapon : public Equipable {
    protected: float requirement_;
               float damageDealt_;
               float speed_;
               float accuracy_;
               int   level_;
               bool  identified_;
    
    public:    float getRequirement() const          { return requirement_; }
               float getDamageDealt() const          { return damageDealt_; }
               float getSpeed      () const          { return speed_; }
               float getAccuracy   () const          { return accuracy_; }
               int   getLevel      () const          { return level_; }

       virtual bool  isDiscovered  () const override { return identified_; }

       virtual void  enhance       () = 0;
       virtual void  enchant       () = 0;
    };

}

#endif // ITEM_HPP
