/**
 * @file src/program/game/entites/player/player_Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "player.hpp"
#include "../../../program.hpp"
#include <iostream>

extern rr::Resources resources;
extern rr::Subject   subject;

namespace rr {

    Player::Player()
        : Entity                       (),
          position_                    (sf::Vector2i(0, 0)),
          currentAnimation_            (&walkingRight_),
          moving_                      (false),
          velocity_                    (1120.f),
          sightRange_                  (5) {

        attrs_.health                = 0.f;
        attrs_.mana                  = 5.f;
        attrs_.maxHealth             = 30.f;
        attrs_.maxMana               = 5.f;
        attrs_.strength              = 10.f;
        attrs_.dexterity             = 10.f;
        attrs_.skillPoints           = 0.f;
        attrs_.experience            = 0.f;
        attrs_.nextLevel             = 100.f;
        attrs_.level                 = 0.f;

        attrs_.crafting              = false;
        attrs_.alchemy               = false;
        attrs_.cold_weapon_mastery   = false;
        attrs_.ranged_weapon_mastery = false;
        attrs_.eagle_eye             = false;
        attrs_.mana_regeneration     = false;
        attrs_.health_regeneration   = false;
        attrs_.faster_learning       = false;

        walkingLeft_ .setSpriteSheet(resources.texture.player);
        walkingRight_.setSpriteSheet(resources.texture.player);
        walkingLeft_ .addFrame(sf::IntRect(0, 16, 16, 16));
        walkingRight_.addFrame(sf::IntRect(0, 0,  16, 16));

        body_.setLooped(false);
        body_.pause();
        body_.setPosition(sf::Vector2f(0, 0));
        body_.scale(sf::Vector2f(5, 5));
    }

    void Player::setPosition(sf::Vector2i pos) {
        position_ = pos;
        body_.setPosition((sf::Vector2f)pos*80.f);
    }

    void Player::setRealPosition(sf::Vector2f pos) {
        position_ = (sf::Vector2i)pos/80;
        body_.setPosition(pos);
    }

    void Player::move(int tiles[], Direction di) {
        if (!moving_) {
            if (di == UP) {
                if (tiles[position_.x+(position_.y-1)*77] != 1) {
                    position_ = sf::Vector2i(position_.x, position_.y-1);
                    moving_ = true;
                }
            }
            if (di == DOWN) {
                if (tiles[position_.x+(position_.y+1)*77] != 1) {
                    position_ = sf::Vector2i(position_.x, position_.y+1);
                    moving_ = true;
                }
            }
            if (di == LEFT) {
                if (tiles[position_.x-1+position_.y*77] != 1) {
                    position_ = sf::Vector2i(position_.x-1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingLeft_;
            }
            if (di == RIGHT) {
                if (tiles[position_.x+1+position_.y*77] != 1) {
                    position_ = sf::Vector2i(position_.x+1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingRight_;
            }
        }
    }

    void Player::update(sf::Time timeStep) {
        if (moving_) {
            sf::Vector2f offset = body_.getPosition()-(sf::Vector2f)position_*80.f;
            if (offset != sf::Vector2f(0, 0)) {
                if (offset.x < 0) body_.move(sf::Vector2f( velocity_*timeStep.asSeconds(),  0));
                if (offset.x > 0) body_.move(sf::Vector2f(-velocity_*timeStep.asSeconds(),  0));
                if (offset.y < 0) body_.move(sf::Vector2f( 0,  velocity_*timeStep.asSeconds()));
                if (offset.y > 0) body_.move(sf::Vector2f( 0, -velocity_*timeStep.asSeconds()));
            }
            else
                moving_ = false;

            if (  (abs(offset.x) < velocity_/32 && abs(offset.x) > 0) // preventing the player from wobbling
               || (abs(offset.y) < velocity_/32 && abs(offset.y) > 0) // in between of two cells
                )  body_.setPosition((sf::Vector2f)position_*80.f);
        }

        if (attrs_.health >= attrs_.maxHealth) attrs_.health = attrs_.maxHealth;
        if (attrs_.health <= 0)                attrs_.health = 0;
        if (attrs_.mana   <= 0)                attrs_.mana   = 0;
        if (attrs_.mana   >= attrs_.maxMana)   attrs_.mana   = attrs_.maxMana;
        if (attrs_.experience  >= attrs_.nextLevel) {
            attrs_.experience   = 0;
            attrs_.nextLevel   *= 1.25f;
            attrs_.level       ++;
            attrs_.skillPoints += (attrs_.faster_learning) ? 15 : 10;

            float temp          = attrs_.health/attrs_.maxHealth;
            attrs_.maxHealth   += 10;
            attrs_.health       = temp*attrs_.maxHealth;

            temp                = attrs_.mana/attrs_.maxMana;
            attrs_.maxMana     += 1;
            attrs_.mana         = temp*attrs_.maxMana;
        }

        body_.update(timeStep);
        body_.play(*currentAnimation_);
    }

    void Player::reset() {
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
        attrs_.eagle_eye             = false;
        attrs_.mana_regeneration     = false;
        attrs_.health_regeneration   = false;
        attrs_.faster_learning       = false;
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }

    void Player::useItem(Item* item) {
        if (instanceof<Discoverable, Item>(item) && !((Discoverable*)item)->isDiscovered()) {
            ((Discoverable*)item)->reveal();
            subject.notify(Observer::ITEM_DISCOVERED, item);
        }
        subject.notify(Observer::ITEM_USED, item);
        if (instanceof<Potion, Item>(item)) {
            switch (((Potion*)item)->effect_) {
            case Potion::HEALING:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:
                    attrs_.health += attrs_.maxHealth*0.25;
                    break;
                case Potion::MEDIUM:
                    attrs_.health += attrs_.maxHealth*0.50;
                    break;
                case Potion::BIG:
                    attrs_.health += attrs_.maxHealth*0.75;
                    break;
                }
                break;
            case Potion::MAGIC:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:
                    attrs_.mana += attrs_.maxMana*0.25;
                    break;
                case Potion::MEDIUM:
                    attrs_.mana += attrs_.maxMana*0.50;
                    break;
                case Potion::BIG:
                    attrs_.mana += attrs_.maxMana*0.75;
                    break;
                }
                break;
            case Potion::STRENGTH:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:
                    attrs_.strength += 1;
                    break;
                case Potion::MEDIUM:
                    attrs_.strength += 2;
                    break;
                case Potion::BIG:
                    attrs_.strength += 3;
                    break;
                }
                break;
            case Potion::DEXTERITY:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:
                    attrs_.dexterity += 1;
                    break;
                case Potion::MEDIUM:
                    attrs_.dexterity += 2;
                    break;
                case Potion::BIG:
                    attrs_.dexterity += 3;
                    break;
                }
                break;
            case Potion::SPEED:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:

                    break;
                case Potion::MEDIUM:

                    break;
                case Potion::BIG:

                    break;
                }
                break;
            case Potion::REGENERATION:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:

                    break;
                case Potion::MEDIUM:

                    break;
                case Potion::BIG:

                    break;
                }
                break;
            case Potion::POISON:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:

                    break;
                case Potion::MEDIUM:

                    break;
                case Potion::BIG:

                    break;
                }
                break;
            case Potion::SLOWNESS:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:

                    break;
                case Potion::MEDIUM:

                    break;
                case Potion::BIG:

                    break;
                }
                break;
            case Potion::WEAKNESS:
                switch (((Potion*)item)->size_) {
                case Potion::SMALL:

                    break;
                case Potion::MEDIUM:

                    break;
                case Potion::BIG:

                    break;
                }
                break;
            }
        }
        else if (instanceof<Book, Item>(item)) {
            switch (((Book*)item)->type_) {
            case Book::CRAFTING:
                attrs_.crafting              = true;
                break;
            case Book::ALCHEMY:
                attrs_.alchemy               = true;
                break;
            case Book::COLD_WEAPON_MASTERY:
                attrs_.cold_weapon_mastery   = true;
                break;
            case Book::RANGED_WEAPON_MASTERY:
                attrs_.ranged_weapon_mastery = true;
                break;
            case Book::EAGLE_EYE:
                attrs_.eagle_eye             = true;
                break;
            case Book::MANA_REGEN:
                attrs_.mana_regeneration     = true;
                break;
            case Book::HEALTH_REGEN:
                attrs_.health_regeneration   = true;
                break;
            case Book::FASTER_LEARNING:
                attrs_.faster_learning       = true;
                break;
            case Book::SPELLS_BOOK:

                break;
            }
        }
        else if (instanceof<Rune, Item>(item)) {

        }
        else if (instanceof<ColdWeapon, Item>(item)) {

        }
    }

}
