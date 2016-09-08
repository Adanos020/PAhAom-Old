/**
 * @file src/program/game/entity/Player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
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
             } m_attrs;

             struct Buffs   // Structure for buffs - each buff is represented by an integer
             {              // which tells for how many turns is it going to be valid.
             public: int speed;
                     int regeneration;
                     int poison;
                     int slowness;
                     int weakness;
                     int hunger;
             } m_buffs;

             MeleeWeapon*       m_meleeWeapon;
             RangedWeapon*      m_rangedWeapon;

             sf::Vector2i       m_position;
             sf::AnimatedSprite m_body;


             sf::Animation      m_standingLeft;
             sf::Animation      m_standingRight;
             sf::Animation      m_walkingLeft;
             sf::Animation      m_walkingRight;
             sf::Animation*     m_currentAnimation;

             bool               m_moving;
             float              m_velocity;
             int                m_sightRange;

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
     virtual void setGridPosition(sf::Vector2i pos) override { m_position = pos; m_body.setPosition((sf::Vector2f) pos*80.f); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's position relatively to the grid marked
             /// out by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2i getGridPosition() const override { return m_position; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the player's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f pos) override { m_position = (sf::Vector2i) pos/80; m_body.setPosition(pos); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's position relatively to the graphics
             /// card's coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition() const override { return m_body.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if another entity's bound box intersects with the
             /// player's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual bool collides(Entity* e) const override { return e->getBounds().intersects(getBounds()); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::FloatRect getBounds() const override { return m_body.getGlobalBounds(); }

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
             MeleeWeapon* getMeleeWeapon() const { return m_meleeWeapon; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's ranged weapon that he equipped.
             ////////////////////////////////////////////////////////////////////////
             RangedWeapon* getRangedWeapon() const { return m_rangedWeapon; }

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
             void addExperience(int exp) { m_attrs.experience += exp; }

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
             Attrs getAttributes() const { return m_attrs; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's attributes.
             ////////////////////////////////////////////////////////////////////////
             Buffs getBuffs() const { return m_buffs; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the player's sight range.
             ////////////////////////////////////////////////////////////////////////
             int getSightRange() const { return m_sightRange + (m_attrs.eagle_eye ? 5 : 0); }
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the player is moving.
             ////////////////////////////////////////////////////////////////////////
             bool isMoving() const { return m_moving; }

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
