/**
 * @file src/program/game/player/player_Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "player.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Player::Player() {
        walkingLeft .setSpriteSheet(resources.texture.player);
        walkingRight.setSpriteSheet(resources.texture.player);
        walkingLeft .addFrame(sf::IntRect(0, 16, 16, 16));
        walkingRight.addFrame(sf::IntRect(0, 0,  16, 16));

        currentAnimation = &walkingRight;

        body.setLooped(false);
        body.pause();
        body.setPosition(sf::Vector2f(0, 0));
        body.scale(sf::Vector2f(5, 5));

        position          = sf::Vector2i(0, 0);
        velocity          = 0.5f;

        attrs.health      =  30.f;
        attrs.mana        =   5.f;
        attrs.maxHealth   =  30.f;
        attrs.maxMana     =   5.f;
        attrs.strength    =  10.f;
        attrs.dexterity   =  10.f;
        attrs.skillPoints =   0.f;
        attrs.experience  =   0.f;
        attrs.nextLevel   = 100.f;
        attrs.level       =   0.f;

        attrs.crafting              = false;
        attrs.alchemy               = false;
        attrs.cold_weapon_mastery   = false;
        attrs.ranged_weapon_mastery = false;
        attrs.better_sight          = false;
    }

    Player::~Player() {}

    void Player::setPosition(sf::Vector2i pos) {
        if (position != pos)
            position  = pos;
        body.setPosition((sf::Vector2f)pos*80.f);
    }

    void Player::move(float ts, std::vector<std::vector<Level::Cell> > tiles, Direction di) {
        if (di == UP) {
            if (tiles[position.x][position.y-1] != Level::WALL)
                setPosition(sf::Vector2i(position.x, position.y-1));
        }
        else if (di == DOWN) {
            if (tiles[position.x][position.y+1] != Level::WALL)
                setPosition(sf::Vector2i(position.x, position.y+1));
        }
        else if (di == LEFT) {
            if (tiles[position.x-1][position.y] != Level::WALL)
                setPosition(sf::Vector2i(position.x-1, position.y));
            currentAnimation = &walkingLeft;
        }
        else if (di == RIGHT) {
            if (tiles[position.x+1][position.y] != Level::WALL)
                setPosition(sf::Vector2i(position.x+1, position.y));
            currentAnimation = &walkingRight;
        }
        sf::sleep(sf::seconds(0.05f));
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }

    void Player::update() {
        if (attrs.health >= attrs.maxHealth)
            attrs.health  = attrs.maxHealth;
        if (attrs.health <= 0)
            attrs.health  = 0;
        if (attrs.mana <= 0)
            attrs.mana  = 0;
        if (attrs.mana >= attrs.maxMana)
            attrs.mana  = attrs.maxMana;
        if (attrs.experience>=attrs.nextLevel) {
            attrs.experience = 0;
            attrs.nextLevel *= 1.25f;
            attrs.level     ++;

            float temp       = attrs.health/attrs.maxHealth;
            attrs.maxHealth += 10;
            attrs.health     = temp*attrs.maxHealth;

            temp             = attrs.mana/attrs.maxMana;
            attrs.maxMana   += 1;
            attrs.mana       = temp*attrs.maxMana;
        }
        body.play(*currentAnimation);
    }

}
