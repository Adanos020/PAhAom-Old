/**
 * @file src/program/game/player/player.h
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
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
        };
        sf::Texture     skin;
        sf::Vector2f    position;
        AnimatedSprite  body;
        Stats           stats;
        double          velocity;

    public:
         Player(sf::Vector2f pos);
        ~Player();

        enum direction { down, left, right, up };

        void         setPosition(sf::Vector2f);
        void         go         (float timeStep, direction);
        void         draw       (sf::RenderWindow&);
        void         update     ();

        Stats        getStats   () const { return stats; }
        sf::Vector2f getPosition() const { return body.getPosition(); }
    };

}

#endif // player_h
