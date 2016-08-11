/**
 * @file src/program/game/entity/npc/Bandit.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../../Resources.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"
#include "../../../path_finder/PathFinder.hpp"

#include "Bandit.hpp"

namespace rr {

    Bandit::Bandit(Type type) :
      type_(type)
    {
        attrs_.health   = attrs_.maxHealth = 20.f;
        attrs_.armor                       =  5.f;
        attrs_.level                       =  5  ;

        initialize();
        body_.scale(sf::Vector2f(5, 5));
    }

    Bandit::Bandit(Bandit const& copy) :
      type_(copy.type_)
    {
        attrs_            = copy.attrs_;
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

        standingLeft_  .addFrame(sf::IntRect(0, type_*32 + 16, 16, 16));

        standingRight_ .addFrame(sf::IntRect(0, type_*32     , 16, 16));

        walkingLeft_   .addFrame(sf::IntRect(0, type_*32 + 16, 16, 16));

        walkingRight_  .addFrame(sf::IntRect(0, type_*32     , 16, 16));

        attackingLeft_ .addFrame(sf::IntRect(0, type_*32 + 16, 16, 16));

        attackingRight_.addFrame(sf::IntRect(0, type_*32     , 16, 16));

        currentAnimation_ = (chance(1, 2)) ? &standingLeft_ : &standingRight_;

        attitude_ = AGGRESSIVE;

        body_.setAnimation(*currentAnimation_);
        body_.setLooped   (true);
        body_.setFrameTime(sf::seconds(.2f));
    }

    void Bandit::update(sf::Time timeStep) {
        body_.update(timeStep);
        body_.play(*currentAnimation_);

        switch (state_) {
            case STANDING : break;
            
            case EXPLORING: if (!path_.empty()) {

                            } else {
                                
                            }
                            break;
            
            case HUNTING  : break;
            
            case ESCAPING : break;
        }
    }

    void Bandit::handleDamage(int damage) {
        if (  damage >= attrs_.armor
            ) attrs_.health -= (damage - attrs_.armor);
    }

    void Bandit::setPath(std::vector<sf::Vector2i> path) {
        for (int i=path.size()-1; i>=0; --i) {
            path_.push(path[i]);
        }
        state_ = EXPLORING;
    }

    sf::String Bandit::getName() const {
        switch (type_) {
            case CLUB    : return Resources::dictionary["npc.bandit.name.bully"      ]; break;
            case CROSSBOW: return Resources::dictionary["npc.bandit.name.crossbowman"]; break;
            case DAGGER  : return Resources::dictionary["npc.bandit.name.rogue"      ]; break;
        }

        return "";
    }

    void Bandit::attack(NPC* npc) {
        int maxDamage;
        switch (type_) {
            case CLUB    : maxDamage = 10;
            case CROSSBOW: maxDamage =  5;
            case DAGGER  : maxDamage =  8;
        }

        npc->handleDamage(rand()%maxDamage);
    }

    void Bandit::attack(Player* player) {
        int maxDamage;
        switch (type_) {
            case CLUB    : maxDamage = 10;
            case CROSSBOW: maxDamage =  5;
            case DAGGER  : maxDamage =  8;
        }

        player->handleDamage(rand()%maxDamage);
    }

    std::ifstream& Bandit::operator<<(std::ifstream& file) {
        standingLeft_  .clearFrames();
        standingRight_ .clearFrames();
        walkingLeft_   .clearFrames();
        walkingRight_  .clearFrames();
        attackingLeft_ .clearFrames();
        attackingRight_.clearFrames();

        sf::Vector2i position;
        int type;

        try {
            readFile <int > (file, position.x);
            readFile <int > (file, position.y);
            readFile <int > (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Bandit::operator>>(std::ofstream& file) {
        file << 20                             << ' '
             << (int) body_.getPosition().x/80 << ' '
             << (int) body_.getPosition().y/80 << ' '
             << type_;

        return file;
    }

}
