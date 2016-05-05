/**
 * @file src/program/game/entites/player/player_Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "player.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Player::Player() {
        walkingLeft_ .setSpriteSheet(resources.texture.player);
        walkingRight_.setSpriteSheet(resources.texture.player);
        walkingLeft_ .addFrame(sf::IntRect(0, 16, 16, 16));
        walkingRight_.addFrame(sf::IntRect(0, 0,  16, 16));

        currentAnimation_ = &walkingRight_;

        body_.setLooped(false);
        body_.pause();
        body_.setPosition(sf::Vector2f(0, 0));
        body_.scale(sf::Vector2f(5, 5));

        position_          = sf::Vector2i(0, 0);
        velocity_          = 0.9f;

        attrs_.health      =  30.f;
        attrs_.mana        =   5.f;
        attrs_.maxHealth   =  30.f;
        attrs_.maxMana     =   5.f;
        attrs_.strength    =  10.f;
        attrs_.dexterity   =  10.f;
        attrs_.skillPoints =   0.f;
        attrs_.experience  =   0.f;
        attrs_.nextLevel   = 100.f;
        attrs_.level       =   0.f;

        attrs_.crafting              = false;
        attrs_.alchemy               = false;
        attrs_.cold_weapon_mastery   = false;
        attrs_.ranged_weapon_mastery = false;
        attrs_.better_sight          = false;

        moving_ = false;
    }

    Player::~Player() {}

    void Player::setPosition(sf::Vector2i pos) {
        position_  = pos;
        body_.setPosition((sf::Vector2f)pos*80.f);
    }

    void Player::setRealPosition(sf::Vector2f pos) {
        position_  = (sf::Vector2i)pos/80;
        body_.setPosition(pos);
    }

    void Player::move(std::vector<std::vector<Level::Cell> > tiles, Direction di) {
        if (!moving_) {
            if (di == UP) {
                if (tiles[position_.x][position_.y-1] != Level::WALL) {
                    position_ = sf::Vector2i(position_.x, position_.y-1);
                    moving_ = true;
                }
            }
            if (di == DOWN) {
                if (tiles[position_.x][position_.y+1] != Level::WALL) {
                    position_ = sf::Vector2i(position_.x, position_.y+1);
                    moving_ = true;
                }
            }
            if (di == LEFT) {
                if (tiles[position_.x-1][position_.y] != Level::WALL) {
                    position_ = sf::Vector2i(position_.x-1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingLeft_;
            }
            if (di == RIGHT) {
                if (tiles[position_.x+1][position_.y] != Level::WALL) {
                    position_ = sf::Vector2i(position_.x+1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingRight_;
            }
        }
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

    void Player::update(float timeStep) {
        if (moving_) {
            sf::Vector2f offset = body_.getPosition()-(sf::Vector2f)position_*80.f;
            if (offset != sf::Vector2f(0, 0)) {
                if (offset.x < 0) body_.move(sf::Vector2f( timeStep*velocity_,  0));
                if (offset.x > 0) body_.move(sf::Vector2f(-timeStep*velocity_,  0));
                if (offset.y < 0) body_.move(sf::Vector2f( 0,  timeStep*velocity_));
                if (offset.y > 0) body_.move(sf::Vector2f( 0, -timeStep*velocity_));
            }
            else
                moving_ = false;
         // preventing the player from wobbling in one place while trying to reach the next cell
            if ((abs(offset.x) < 20*velocity_ && abs(offset.x) > 0) || (abs(offset.y) < 20*velocity_ && abs(offset.y) > 0))
                body_.setPosition((sf::Vector2f)position_*80.f);
        }

        if (attrs_.health >= attrs_.maxHealth) attrs_.health = attrs_.maxHealth;
        if (attrs_.health <= 0)                attrs_.health = 0;
        if (attrs_.mana   <= 0)                attrs_.mana   = 0;
        if (attrs_.mana   >= attrs_.maxMana)   attrs_.mana   = attrs_.maxMana;
        if (attrs_.experience >= attrs_.nextLevel) {
            attrs_.experience  = 0;
            attrs_.nextLevel  *= 1.25f;
            attrs_.level      ++;

            float temp         = attrs_.health/attrs_.maxHealth;
            attrs_.maxHealth  += 10;
            attrs_.health      = temp*attrs_.maxHealth;

            temp               = attrs_.mana/attrs_.maxMana;
            attrs_.maxMana    += 1;
            attrs_.mana        = temp*attrs_.maxMana;
        }
        body_.play(*currentAnimation_);
    }

}
