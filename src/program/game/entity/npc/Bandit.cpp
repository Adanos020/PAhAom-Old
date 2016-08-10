/**
 * @file src/program/game/entity/npc/Bandit.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../../Resources.hpp"

#include "../../../funcs/files.hpp"

#include "Bandit.hpp"

namespace rr {

    Bandit::Bandit(Weapon weapon, bool asleep) :
      asleep_(asleep),
      weapon_(weapon)
    {
        attrs_.health   = attrs_.maxHealth = 20.f;
        attrs_.armor                       = 10.f;
        attrs_.level                       =  1  ;

        initialize();
        body_.scale      (sf::Vector2f(5, 5));
    }

    Bandit::Bandit(Bandit const& copy) :
      attrs_ (copy.attrs_ ),
      asleep_(copy.asleep_),
      weapon_(copy.weapon_)
    {
        body_             = copy.body_;
        currentAnimation_ = copy.currentAnimation_;
    }

    void Bandit::initialize() {
        standingLeft_  .setSpriteSheet(Resources::texture.enemies);
        standingRight_ .setSpriteSheet(Resources::texture.enemies);
        walkingLeft_   .setSpriteSheet(Resources::texture.enemies);
        walkingRight_  .setSpriteSheet(Resources::texture.enemies);
        attackingLeft_ .setSpriteSheet(Resources::texture.enemies);
        attackingRight_.setSpriteSheet(Resources::texture.enemies);

        standingLeft_  .addFrame(sf::IntRect(0, weapon_*32 + 16, 16, 16));

        standingRight_ .addFrame(sf::IntRect(0, weapon_*32     , 16, 16));

        walkingLeft_   .addFrame(sf::IntRect(0, weapon_*32 + 16, 16, 16));

        walkingRight_  .addFrame(sf::IntRect(0, weapon_*32     , 16, 16));

        attackingLeft_ .addFrame(sf::IntRect(0, weapon_*32 + 16, 16, 16));

        attackingRight_.addFrame(sf::IntRect(0, weapon_*32     , 16, 16));

        currentAnimation_ = &standingLeft_;

        attitude_ = Resources::dictionary["npc.attitude.aggressive"];

        body_.setAnimation(*currentAnimation_);
        body_.setLooped   (true);
        body_.setFrameTime(sf::seconds(.2f));
    }

    void Bandit::update(sf::Time timeStep) {
        body_.update(timeStep);
        body_.play(*currentAnimation_);

        if (asleep_) {

        }
        else {

        }
    }

    void Bandit::handleDamage(int damage) {
        if (  damage >= attrs_.armor
            ) attrs_.health -= (damage - attrs_.armor);
    }

    void Bandit::attack(NPC* npc) {
        int maxDamage;
        switch (weapon_) {
            case CLUB    : maxDamage = 10;
            case CROSSBOW: maxDamage =  5;
            case DAGGER  : maxDamage =  8;
        }
        
        npc->handleDamage(rand()%maxDamage);
    }

    void Bandit::attack(Player* player) {
        int maxDamage;
        switch (weapon_) {
            case CLUB    : maxDamage = 10;
            case CROSSBOW: maxDamage =  5;
            case DAGGER  : maxDamage =  8;
        }
        
        player->handleDamage(rand()%maxDamage);
    }

    std::ifstream& Bandit::operator<<(std::ifstream& file) {
        currentAnimation_->clearFrames();
        
        sf::Vector2u position;
        int weapon;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);  
            readFile <  bool  > (file, asleep_);                
            readFile <  int   > (file, weapon);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        weapon_ = (Weapon) weapon;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Bandit::operator>>(std::ofstream& file) {
        file << 20                                   << ' '
             << (unsigned) body_.getPosition().x/80u << ' '
             << (unsigned) body_.getPosition().y/80u << ' '
             << asleep_                              << ' '
             << weapon_;

        return file;
    }

}
