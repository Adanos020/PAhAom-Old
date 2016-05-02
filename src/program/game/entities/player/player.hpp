/**
 * @file src/program/game/player/player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include "../entities.hpp"
#include "../../../../../lib/AnimatedSprite.hpp"

namespace rr {

/// Class for the player
    class Player : public Entity {
        friend class Game;
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
            bool  better_sight;
        } attrs;

        sf::Vector2f       position;
        sf::AnimatedSprite body;
        sf::Animation      walkingLeft;
        sf::Animation      walkingRight;
        sf::Animation*     currentAnimation;
        float              velocity;
    public:
         Player();
        ~Player();

        enum direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    /// Method making the player character's move in a given direction
        void          move            (float timeStep, direction);

    /// Method drawing the player character
        void          draw            (sf::RenderWindow&);

    /// Updates the state of the player character
        void          update          ();

    /// Returns the player statistics
        Attrs         getAttributes   ()          const          { return attrs; }

    /// Returns the position of the player character
        sf::Vector2f  getPosition     ()          const          { return body.getPosition(); }

        void          setPosition     (sf::Vector2f)    override;
        bool          intersects      (Entity* e) const override { return e->getBounds().intersects(this->getBounds()); }
        sf::FloatRect getBounds       ()          const override { return body.getGlobalBounds(); }
    };

}

#endif // player_h
