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
        _walkingLeft .setSpriteSheet(resources.texture.player);
        _walkingRight.setSpriteSheet(resources.texture.player);
        _walkingLeft .addFrame(sf::IntRect(0, 16, 16, 16));
        _walkingRight.addFrame(sf::IntRect(0, 0,  16, 16));

        _currentAnimation = &_walkingRight;

        _body.setLooped(false);
        _body.pause();
        _body.setPosition(sf::Vector2f(0, 0));
        _body.scale(sf::Vector2f(5, 5));

        _position          = sf::Vector2i(0, 0);
        _velocity          = 0.9f;

        _attrs.health      =  30.f;
        _attrs.mana        =   5.f;
        _attrs.maxHealth   =  30.f;
        _attrs.maxMana     =   5.f;
        _attrs.strength    =  10.f;
        _attrs.dexterity   =  10.f;
        _attrs.skillPoints =   0.f;
        _attrs.experience  =   0.f;
        _attrs.nextLevel   = 100.f;
        _attrs.level       =   0.f;

        _attrs.crafting              = false;
        _attrs.alchemy               = false;
        _attrs.cold_weapon_mastery   = false;
        _attrs.ranged_weapon_mastery = false;
        _attrs.better_sight          = false;

        _moving = false;
    }

    Player::~Player() {}

    void Player::setPosition(sf::Vector2i pos) {
        if (_position != pos) {
            _position  = pos;
            _body.setPosition((sf::Vector2f)pos*80.f);
        }
    }

    void Player::move(std::vector<std::vector<Level::Cell> > tiles, Direction di) {
        if (!_moving) {
            if (di == UP) {
                if (tiles[_position.x][_position.y-1] != Level::WALL) {
                    _position = sf::Vector2i(_position.x, _position.y-1);
                    _moving = true;
                }
            }
            if (di == DOWN) {
                if (tiles[_position.x][_position.y+1] != Level::WALL) {
                    _position = sf::Vector2i(_position.x, _position.y+1);
                    _moving = true;
                }
            }
            if (di == LEFT) {
                if (tiles[_position.x-1][_position.y] != Level::WALL) {
                    _position = sf::Vector2i(_position.x-1, _position.y);
                    _moving = true;
                }
                _currentAnimation = &_walkingLeft;
            }
            if (di == RIGHT) {
                if (tiles[_position.x+1][_position.y] != Level::WALL) {
                    _position = sf::Vector2i(_position.x+1, _position.y);
                    _moving = true;
                }
                _currentAnimation = &_walkingRight;
            }
        }
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
    }

    void Player::update(float timeStep) {
        if (_moving) {
            sf::Vector2f offset = _body.getPosition()-(sf::Vector2f)_position*80.f;
            if (offset != sf::Vector2f(0, 0)) {
                if (offset.x <  0 && offset.y == 0) _body.move(sf::Vector2f( timeStep*_velocity,  0));
                if (offset.x >  0 && offset.y == 0) _body.move(sf::Vector2f(-timeStep*_velocity,  0));
                if (offset.x == 0 && offset.y <  0) _body.move(sf::Vector2f( 0,  timeStep*_velocity));
                if (offset.x == 0 && offset.y >  0) _body.move(sf::Vector2f( 0, -timeStep*_velocity));
            }
            else
                _moving = false;
            if ((abs(offset.x) < 20*_velocity && abs(offset.x) > 0) || (abs(offset.y) < 20*_velocity && abs(offset.y) > 0))
                _body.setPosition((sf::Vector2f)_position*80.f);
        }

        if (_attrs.health >= _attrs.maxHealth)
            _attrs.health  = _attrs.maxHealth;
        if (_attrs.health <= 0)
            _attrs.health  = 0;
        if (_attrs.mana <= 0)
            _attrs.mana  = 0;
        if (_attrs.mana >= _attrs.maxMana)
            _attrs.mana  = _attrs.maxMana;
        if (_attrs.experience>=_attrs.nextLevel) {
            _attrs.experience = 0;
            _attrs.nextLevel *= 1.25f;
            _attrs.level     ++;

            float temp        = _attrs.health/_attrs.maxHealth;
            _attrs.maxHealth += 10;
            _attrs.health     = temp*_attrs.maxHealth;

            temp              = _attrs.mana/_attrs.maxMana;
            _attrs.maxMana   += 1;
            _attrs.mana       = temp*_attrs.maxMana;
        }
        _body.play(*_currentAnimation);
    }

}
