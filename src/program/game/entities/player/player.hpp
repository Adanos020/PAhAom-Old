/**
 * @file src/program/game/entities/player/player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef player_hpp
#define player_hpp

#include <SFML/Graphics.hpp>
#include "../../../../../lib/AnimatedSprite.hpp"
#include "../entities.hpp"

namespace rr {

    class Level;
    class ColdWeapon;
    class Equipable;

/// Class for the player
    class Player : public Entity {
    private:
    /// Structure for the player attributes
        struct Attrs {
        public:
            float health;
            float mana;
            float maxHealth;
            float maxMana;
            float strength;
            float dexterity;
            float experience;
            float nextLevel;
            float level;
            float skillPoints;

            bool  crafting;
            bool  alchemy;
            bool  cold_weapon_mastery;
            bool  ranged_weapon_mastery;
            bool  eagle_eye;
            bool  mana_regeneration;
            bool  health_regeneration;
            bool  faster_learning;
        } attrs_;

        ColdWeapon*        coldWeapon_;

        sf::Vector2i       position_;
        sf::AnimatedSprite body_;
        sf::Animation      walkingLeft_;
        sf::Animation      walkingRight_;
        sf::Animation*     currentAnimation_;

        bool               moving_;
        float              velocity_;
        int                sightRange_;

        virtual void          initialize     ()                override;
    public:
         Player();
         Player(Player const&);
        ~Player() {}

        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        virtual Entity*       clone          ()          const override { return new Player(*this); }
        virtual Entity*       create         ()          const override { return new Player(); }

        virtual void          draw           (sf::RenderWindow&);
        virtual void          setPosition    (sf::Vector2i)    override;
        virtual void          setRealPosition(sf::Vector2f)    override;

        virtual bool          intersects     (Entity* e) const override { return e->getBounds().intersects(getBounds()); }
        virtual sf::FloatRect getBounds      ()          const override { return body_.getGlobalBounds(); }
        virtual sf::Vector2i  getPosition    ()          const override { return (sf::Vector2i)body_.getPosition()/80; }
        virtual sf::Vector2f  getRealPosition()          const override { return body_.getPosition(); }

    /// Moves the player's character's to a cell in a given direction
        void                  move           (int[], Direction);
    /// Makes the player use a given item
        void                  useItem        (Item*);
    /// Makes the player equip a given item
        bool                  equipItem      (Equipable*, bool);
    /// Updates the state of the player character
        void                  update         (sf::Time);
    /// Returns the player's attributes
        Attrs                 getAttributes  ()          const          { return attrs_; }
    /// Returns the player's sight range
        int                   getSightRange  ()          const          { return sightRange_; }
    /// Resets the player's atributes
        void                  reset          ();

        virtual std::ifstream& operator<<(std::ifstream&)      override;
        virtual std::ofstream& operator>>(std::ofstream&)      override;
    };

}

#endif // player_h
