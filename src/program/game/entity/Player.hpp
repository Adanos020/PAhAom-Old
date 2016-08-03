/**
 * @file src/program/game/entity/Player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ENTITY_PLAYER_HPP
#define ENTITY_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "../../../../lib/AnimatedSprite.hpp"

#include "Entity.hpp"
#include "npc/NPC.hpp"
#include "item/ColdWeapon.hpp"
#include "item/Item.hpp"

namespace rr {

    class Level;
    class ColdWeapon;
    class Equipable;

/// Class for the player
    class Player : public Entity {
    private: struct Attrs { /// Structure for the player attributes
             public: float health;
                     float maxHealth;
                     float mana;
                     float maxMana;
                     float strength;
                     float dexterity;
                     float experience;
                     float nextLevel;
                     int   level;
                     float skillPoints;
                     float armor;
                 
                     bool  crafting;
                     bool  alchemy;
                     bool  cold_weapon_mastery;
                     bool  ranged_weapon_mastery;
                     bool  eagle_eye;
                     bool  mana_regeneration;
                     bool  health_regeneration;
                     bool  faster_learning;
             } attrs_;

             struct {   /// Structure for buffs - each buff is represented by an integer
                        /// which tells for how many turns is it going to be valid 
             public: int speed;
                     int regeneration;
                     int poison;
                     int slowness;
                     int weakness;
                     int hunger;
             } buffs_;

             ColdWeapon*        coldWeapon_;

             sf::Vector2i       position_;
             sf::AnimatedSprite body_;
             sf::Animation      walkingLeft_;
             sf::Animation      walkingRight_;
             sf::Animation*     currentAnimation_;
     
             bool               moving_;
             float              velocity_;
             int                sightRange_;
     
             virtual void          initialize     ()                       override;
             virtual void          draw           (sf::RenderTarget&,
                                                   sf::RenderStates) const override;

    public:  Player();
             Player(Player const&);
    
             enum Direction {
                 UP,
                 DOWN,
                 LEFT,
                 RIGHT
             };

             virtual Entity*       clone          ()                 const override { return new Player(*this); }

             virtual void          setGridPosition(sf::Vector2i pos)       override { position_ = pos; body_.setPosition((sf::Vector2f)pos*80.f); }
             virtual void          setPosition    (sf::Vector2f pos)       override { position_ = (sf::Vector2i)pos/80; body_.setPosition(pos); }

             virtual bool          collides       (Entity* e)        const override { return e->getBounds().intersects(getBounds()); }
             virtual sf::FloatRect getBounds      ()                 const override { return body_.getGlobalBounds(); }
             virtual sf::Vector2i  getGridPosition()                 const override { return position_; }
             virtual sf::Vector2f  getPosition    ()                 const override { return body_.getPosition(); }

         /// Moves the player's character's to a cell in a given direction
             void                  move           (int[], Direction);
         /// Makes the player use a given item
             void                  useItem        (Item*);
         /// Makes the player equip a given item
             bool                  equipItem      (Equipable*, bool);
         /// Updates the state of the player character
             void                  update         (sf::Time);
         /// Makes the player attack an NPC
             void                  attack         (NPC*);
         /// Makes the player handle the damage dealt by an NPC
             void                  handleDamage   (int damage);
         /// Returns the player's attributes
             Attrs                 getAttributes  ()                 const          { return attrs_; }
         /// Returns the player's sight range
             int                   getSightRange  ()                 const          { return sightRange_; }
         /// Resets the player's atributes
             void                  reset          ();

             virtual std::ifstream& operator<<    (std::ifstream&)         override;
             virtual std::ofstream& operator>>    (std::ofstream&)         override;
    };

}

#endif // ENTITY_PLAYER_HPP
