/**
 * @file src/program/game/player/Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "player.hpp"
#include "../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Player::Player(sf::Vector2f pos) {
        walkingLeft .setSpriteSheet(resources.texture.player);
        walkingRight.setSpriteSheet(resources.texture.player);
        walkingLeft .addFrame(sf::IntRect(0, 14,  14, 14));
        walkingRight.addFrame(sf::IntRect(0, 0, 14, 14));

        currentAnimation = &walkingRight;

        body.setLooped(false);
        body.pause();
        body.setPosition(pos);
        body.setOrigin(sf::Vector2f(7, 7));
        body.scale(sf::Vector2f(5, 5));

        position      = pos;
        velocity      = 0.5;
        stats.hp      = 30.0;
        stats.mp      = 5.0;
        stats.maxhp   = 30.0;
        stats.maxmp   = 5.0;
        stats.sp      = 0;
        stats.exp     = 0;
        stats.nextlvl = 100;
        stats.lvl     = 0;
    }

    Player::~Player() {

    }

    void Player::setPosition(sf::Vector2f pos) {
        if (position != pos)
            position  = pos;
        body.setPosition(pos);
    }

    void Player::go(float ts, direction di) {
        if        (di == UP) {
            position.y -= ts*velocity;
            setPosition(position);
        } else if (di == DOWN) {
            position.y += ts*velocity;
            setPosition(position);
        } else if (di == LEFT) {
            position.x -= ts*velocity;
            setPosition(position);
            currentAnimation = &walkingLeft;
        } else if (di == RIGHT) {
            position.x += ts*velocity;
            setPosition(position);
            currentAnimation = &walkingRight;
        }
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }

    void Player::update() {
        if (stats.hp>=stats.maxhp)
            stats.hp = stats.maxhp;
        if (stats.hp<=0)
            stats.hp = 0;
        if (stats.mp<=0)
            stats.mp = 0;
        if (stats.mp>=stats.maxmp)
            stats.mp = stats.maxmp;
        if (stats.exp>=stats.nextlvl) {
            stats.exp = 0;
            stats.nextlvl *= 1.25;
            stats.lvl++;
        }
        body.play(*currentAnimation);
    }

}
