/**
 * @file src/program/game/player/player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include "../../../../lib/AnimatedSprite.hpp"

namespace rr {

/// Class for the player
    class Player {
        friend class Game;
    private:
        struct Stats {
        public:
            double hp;
            double mp;
            double maxhp;
            double maxmp;
            int    sp;
            int    exp;
            int    nextlvl;
            int    lvl;
        } stats;

        sf::Vector2f       position;
        sf::AnimatedSprite body;
        sf::Animation      walkingLeft;
        sf::Animation      walkingRight;
        sf::Animation*     currentAnimation;
        double             velocity;
    public:
         Player(sf::Vector2f pos);
        ~Player();

        enum direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    /// Sets the player character's position
        void         setPosition(sf::Vector2f);

    /// Method making the player character's move in a given direction
        void         move       (float timeStep, direction);

    /// Method drawing the player character
        void         draw       (sf::RenderWindow&);

    /// Updates the state of the player character
        void         update     ();

    /// Returns the player statistics
        Stats        getStats   () const { return stats; }

    /// Returns the position of the player character
        sf::Vector2f getPosition() const { return body.getPosition(); }
    };

}

#endif // player_h
