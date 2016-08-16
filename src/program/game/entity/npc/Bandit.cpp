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
      type_    (type  )
    {
        velocity_                        = 900.f;
        attrs_.health = attrs_.maxHealth =  20.f;
        attrs_.armor                     =   5.f;
        attrs_.level                     =   5  ;

        initialize();
        body_.scale(sf::Vector2f(5, 5));
    }

    Bandit::Bandit(Bandit const& copy) :
      type_(copy.type_)
    {
        velocity_         = copy.velocity_;
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

        currentAnimation_ = chance(1, 2) ? &standingLeft_ : &standingRight_;

        attitude_ = AGGRESSIVE;
        state_    = chance(1, 3) ? STANDING : WAITING;

        body_.setAnimation(*currentAnimation_);
        body_.setLooped   (true);
        body_.setFrameTime(sf::seconds(.2f));
    }

    void Bandit::update(int tiles[], sf::Time timeStep) {
        if (moving_) {
            sf::Vector2f offset = body_.getPosition() - (sf::Vector2f) position_*80.f;
            if (offset != sf::Vector2f(0, 0)) {
                if (offset.x < 0) body_.move(sf::Vector2f( velocity_*timeStep.asSeconds(),  0));
                if (offset.x > 0) body_.move(sf::Vector2f(-velocity_*timeStep.asSeconds(),  0));
                if (offset.y < 0) body_.move(sf::Vector2f( 0,  velocity_*timeStep.asSeconds()));
                if (offset.y > 0) body_.move(sf::Vector2f( 0, -velocity_*timeStep.asSeconds()));
            }
            else {
                buffs_.speed        -= (buffs_.speed        == 0 ? 0 : 1);
                buffs_.regeneration -= (buffs_.regeneration == 0 ? 0 : 1);
                buffs_.poison       -= (buffs_.poison       == 0 ? 0 : 1);
                buffs_.slowness     -= (buffs_.slowness     == 0 ? 0 : 1);
                buffs_.weakness     -= (buffs_.weakness     == 0 ? 0 : 1);

                if (  buffs_.poison > 0
                    ) attrs_.health -= 1.f;

                if (  buffs_.regeneration > 0
                    ) attrs_.health += 0.15f;

                moving_ = false;
            }

            if (  (abs(offset.x) < velocity_/128 && abs(offset.x) > 0) // preventing the teacher from wobbling
               || (abs(offset.y) < velocity_/128 && abs(offset.y) > 0) // in between of two cells
                )  body_.setPosition((sf::Vector2f) position_*80.f);
        }

        body_.update(timeStep);

        if (!body_.isPlaying()) {
            if      (  direction_ == LEFT
                     ) currentAnimation_ = &standingLeft_;
            else if (  direction_ == RIGHT
                     ) currentAnimation_ = &standingRight_;
            body_.setLooped(true);
        }

        switch (state_) {
            case STANDING : if      (   direction_        == LEFT
                                    && *currentAnimation_ != standingLeft_
                                     )  currentAnimation_ = &standingLeft_;

                            else if (   direction_        == RIGHT
                                    && *currentAnimation_ != standingRight_
                                     )  currentAnimation_ = &standingRight_;
                            break;

            case WAITING  : break;

            case EXPLORING: if (!moving_) {
                                if (position_ != destination_) {
                                    /*position_ = PathFinder::aStar(position_, destination_, tiles)[0] - position_;
                                    moving_ = true;*/
                                } else {
                                    state_ = STANDING;
                                }
                            }
                            break;

            case HUNTING  : break;

            case ESCAPING : break;
        }

        body_.play(*currentAnimation_);
    }

    sf::String Bandit::getName() const {
        switch (type_) {
            case CLUB    : return Resources::dictionary["npc.bandit.name.bully"      ]; break;
            case CROSSBOW: return Resources::dictionary["npc.bandit.name.crossbowman"]; break;
            case DAGGER  : return Resources::dictionary["npc.bandit.name.rogue"      ]; break;
        }

        return "";
    }

    void Bandit::handleDamage(int damage) {
        if (  damage >= attrs_.armor
            ) attrs_.health -= (damage - attrs_.armor);
        state_ = HUNTING;
    }

    void Bandit::attack(NPC* npc) {
        if      (  direction_ == LEFT
                 ) currentAnimation_ = &attackingLeft_;
        else if (  direction_ == RIGHT
                 ) currentAnimation_ = &attackingRight_;
        body_.setLooped(false);

        int maxDamage = 0;
        switch (type_) {
            case CLUB    : maxDamage = 10; break;
            case CROSSBOW: maxDamage =  5; break;
            case DAGGER  : maxDamage =  8; break;
        }

        npc->handleDamage(range(0, maxDamage));
    }

    void Bandit::attack(Player* player) {
        if      (  direction_ == LEFT
                 ) currentAnimation_ = &attackingLeft_;
        else if (  direction_ == RIGHT
                 ) currentAnimation_ = &attackingRight_;
        body_.setLooped(false);

        int maxDamage = 0;
        switch (type_) {
            case CLUB    : maxDamage = 10; break;
            case CROSSBOW: maxDamage =  5; break;
            case DAGGER  : maxDamage =  8; break;
        }

        player->handleDamage(range(0, maxDamage));
    }

    std::ifstream& Bandit::operator<<(std::ifstream& file) {
        standingLeft_  .clearFrames();
        standingRight_ .clearFrames();
        walkingLeft_   .clearFrames();
        walkingRight_  .clearFrames();
        attackingLeft_ .clearFrames();
        attackingRight_.clearFrames();

        sf::Vector2i position;
        int state, direction, type;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, state);
            readFile <int> (file, direction);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        state_     = (  State  )     state;
        direction_ = (Direction) direction;
        type_      = (   Type  )      type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Bandit::operator>>(std::ofstream& file) {
        file << 20                             << ' '
             << (int) body_.getPosition().x/80 << ' '
             << (int) body_.getPosition().y/80 << ' '
             << state_                         << ' '
             << direction_                     << ' '
             << type_;

        return file;
    }

}
