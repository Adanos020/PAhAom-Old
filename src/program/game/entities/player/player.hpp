/**
 * @file src/program/game/entities/player/player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include "../../level.hpp"
#include "../../../../../lib/AnimatedSprite.hpp"

namespace rr {

    class Level;

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

        sf::Vector2i       position;
        sf::AnimatedSprite body;
        sf::Animation      walkingLeft;
        sf::Animation      walkingRight;
        sf::Animation*     currentAnimation;
        float              velocity;
    public:
         Player();
        ~Player();

        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    /// Moves the player's character's to a cell in a given direction
        void          move            (float timeStep, std::vector<std::vector<Level::Cell> >, Direction);

    /// Draws the player's character
        void          draw            (sf::RenderWindow&);

    /// Updates the state of the player character
        void          update          ();

    /// Returns the player statistics
        Attrs         getAttributes   ()          const          { return attrs; }

    /// Returns the position of the player character
        sf::Vector2i  getPosition     ()          const          { return position; }

        void          setPosition     (sf::Vector2i)    override;
        bool          intersects      (Entity* e) const override { return e->getBounds().intersects(this->getBounds()); }
        sf::FloatRect getBounds       ()          const override { return body.getGlobalBounds(); }
    };

}

#endif // player_h
