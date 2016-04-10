/**
 * @file src/program/game/player/Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "player.h"

namespace rr {

    Player::Player(sf::Vector2f pos) {
        skin.loadFromFile("data/graphics/player.png");

        body.setPosition(pos);

        position = pos;
        velocity = 0.5;
        stats.hp = 30.0;
        stats.mp = 5.0;
        stats.maxhp = 30.0;
        stats.maxmp = 5.0;
        stats.sp = 0;
        stats.exp = 0;
        stats.nextlvl = 100;
        stats.lvl = 0;
    }

    Player::~Player() {

    }

    void Player::setPosition(sf::Vector2f pos) {
        if (position != pos) position = pos;
        body.setPosition(pos);
    }

    void Player::go(float ts, direction di) {
        if (di == up) {
            position.y -= ts*velocity;
            setPosition(position);
        } else if (di == down) {
            position.y += ts*velocity;
            setPosition(position);
        } else if (di == left) {
            position.x -= ts*velocity;
            setPosition(position);
/*
            body[0].texCoords = sf::Vector2f(0, 14);
            body[1].texCoords = sf::Vector2f(14, 14);
            body[2].texCoords = sf::Vector2f(14, 28);
            body[3].texCoords = sf::Vector2f(0, 28);*/
        } else if (di == right) {
            position.x += ts*velocity;
            setPosition(position);
/*
            body[0].texCoords = sf::Vector2f(0, 0);
            body[1].texCoords = sf::Vector2f(14, 0);
            body[2].texCoords = sf::Vector2f(14, 14);
            body[3].texCoords = sf::Vector2f(0, 14);*/
        }
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body, &skin);
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

    }

}
