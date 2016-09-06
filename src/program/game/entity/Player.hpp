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
#include "item/MeleeWeapon.hpp"
#include "item/RangedWeapon.hpp"
#include "item/Item.hpp"
#include "item/Book.hpp"

namespace rr
{

    class Level;
    class MeleeWeapon;
    class RangedWeapon;
    class Equipable;
    class NPC;

    class Player : public Entity
    {
    private: struct Attrs // Structure for the player attributes.
             {
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
                     bool  melee_weapon_mastery;
                     bool  ranged_weapon_mastery;
                     bool  eagle_eye;
                     bool  mana_regeneration;
                     bool  health_regeneration;
                     bool  faster_learning;
             } attrs_;

             struct Buffs   // Structure for buffs - each buff is represented by an integer
             {              // which tells for how many turns is it going to be valid.
             public: int speed;
                     int regeneration;
                     int poison;
                     int slowness;
                     int weakness;
                     int hunger;
             } buffs_;

             MeleeWeapon*       meleeWeapon_;
             RangedWeapon*      rangedWeapon_;

             sf::Vector2i       position_;
             sf::AnimatedSprite body_;
             sf::Animation      walkingLeft_;
             sf::Animation      walkingRight_;
             sf::Animation*     currentAnimation_;

             bool               moving_;
             float              velocity_;
             int                sightRange_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the player.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the player's body and texture on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  enum Direction
             {
                 UP,
                 DOWN,
                 LEFT,
                 RIGHT
             };

             enum Attribute
             {
                 HEALTH,
                 MANA,
                 STRENGTH,
                 DEXTERITY
             };
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Player();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Player(Player const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the player.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Player(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the player's position relatively to the grid marked out
             /// by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual void setGridPosition(sf::Vector2i pos) override { position_ = pos; body_.setPosition((sf::Vector2f) pos*80.f); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's position relatively to the grid marked
             /// out by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2i getGridPosition() const override { return position_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the player's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f pos) override { position_ = (sf::Vector2i) pos/80; body_.setPosition(pos); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's position relatively to the graphics
             /// card's coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition() const override { return body_.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if another entity's bound box intersects with the
             /// player's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual bool collides(Entity* e) const override { return e->getBounds().intersects(getBounds()); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::FloatRect getBounds() const override { return body_.getGlobalBounds(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Moves the player's character to a cell in a given direction.
             ///
             /// \param tiles the set of tiles of the level in which the player moves
             ////////////////////////////////////////////////////////////////////////
             void move(int[], Direction);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player use a given item.
             ////////////////////////////////////////////////////////////////////////
             void useItem(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player equip a given item.
             ////////////////////////////////////////////////////////////////////////
             bool equipItem(Equipable*, bool);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's melee weapon that he equipped.
             ////////////////////////////////////////////////////////////////////////
             MeleeWeapon* getMeleeWeapon() const { return meleeWeapon_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's ranged weapon that he equipped.
             ////////////////////////////////////////////////////////////////////////
             RangedWeapon* getRangedWeapon() const { return rangedWeapon_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the player's state.
             ///
             /// \param timeStep the time duration of a single frame
             ///
             /// The things updated in this function are the animations, states of
             /// the seeked path, moving the player, etc.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Clock&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player attack an NPC.
             ////////////////////////////////////////////////////////////////////////
             void attack(NPC*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player handle the damage dealt by an NPC.
             ////////////////////////////////////////////////////////////////////////
             void handleDamage(int damage);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Gives a specific amount of experience to the player.
             ////////////////////////////////////////////////////////////////////////
             void addExperience(int exp) { attrs_.experience += exp; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player learn the skill given as a type of book he
             /// can read.
             ///
             /// The possible values are:
             /// - CRAFTING
             /// - ALCHEMY
             /// - MELEE_WEAPON_MASTERY
             /// - RANGED_WEAPON_MASTERY
             /// - EAGLE_EYE
             /// - MANA_REGEN
             /// - HEALTH_REGEN
             /// - FASTER_LEARNING
             /// SPELLS_BOOK is not handled because it would make no sense.
             ////////////////////////////////////////////////////////////////////////
             void learnSkill(Book::Type, int sp);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the player increase the chosen attribute by a given
             /// value.
             ///
             /// The possible values are:
             /// - HEALTH
             /// - MANA
             /// - STRENGTH
             /// - DEXTERITY
             ////////////////////////////////////////////////////////////////////////
             void increaseAttribute(Attribute, float, int sp);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's attributes.
             ////////////////////////////////////////////////////////////////////////
             Attrs getAttributes() const { return attrs_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's attributes.
             ////////////////////////////////////////////////////////////////////////
             Buffs getBuffs() const { return buffs_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's sight range.
             ////////////////////////////////////////////////////////////////////////
             int getSightRange() const { return sightRange_ + (attrs_.eagle_eye ? 5 : 0); }
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the player is moving.
             ////////////////////////////////////////////////////////////////////////
             bool isMoving() const { return moving_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the player's atributes.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the game cheats if the debug mode is enabled.
             ////////////////////////////////////////////////////////////////////////
             void cheat();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the player from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the player to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;
    };

}

#include "npc/NPC.hpp"

#endif // ENTITY_PLAYER_HPP
