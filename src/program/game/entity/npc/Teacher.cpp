/**
 * @file src/program/game/entity/npc/Teacher.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../../Resources.hpp"

#include "../../../funcs/files.hpp"

#include "Teacher.hpp"

namespace rr {

    Teacher::Teacher(Type type) :
      type_(type)
    {
        initialize();
        body_.scale(sf::Vector2f(5, 5));
    }

    Teacher::Teacher(Teacher const& copy) :
      type_(copy.type_)
    {
        body_             = copy.body_;
        currentAnimation_ = copy.currentAnimation_;
    }

    void Teacher::initialize() {
        standingStill_.setSpriteSheet(Resources::texture.npc);

        for (int i=0; i<((type_ == KUNG_FU_MASTER)?20:10); i++) {
            standingStill_.addFrame(sf::IntRect(i*16, type_*16, 16, 16));
        }

        currentAnimation_ = &standingStill_;

        attitude_ = NEUTRAL;

        body_.setAnimation      (*currentAnimation_);
        body_.setLooped         (true);
        if (  type_ == MAGE
            ) body_.setFrameTime(sf::seconds(.4f));
        else  body_.setFrameTime(sf::seconds(.2f));
    }

    void Teacher::update(sf::Time timeStep) {
        body_.update(timeStep);
        body_.play(*currentAnimation_);
    }

    void Teacher::handleDamage(int damage) {
        
    }

    void Teacher::setPath(std::vector<sf::Vector2i> path) {
        
    }

    sf::String Teacher::getName() const {
        switch (type_) {
            case SWORDSMAN     : return Resources::dictionary["npc.teacher.name.swordsman"     ]; break;
            case SHARPSHOOTER  : return Resources::dictionary["npc.teacher.name.sharpshooter"  ]; break;
            case CARPENTER     : return Resources::dictionary["npc.teacher.name.carpenter"     ]; break;
            case MAGE          : return Resources::dictionary["npc.teacher.name.mage"          ]; break;
            case KUNG_FU_MASTER: return Resources::dictionary["npc.teacher.name.kung_fu_master"]; break;
        }

        return "";
    }

    std::ifstream& Teacher::operator<<(std::ifstream& file) {
        currentAnimation_->clearFrames();
        
        sf::Vector2i position;
        int type;

        try {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Teacher::operator>>(std::ofstream& file) {
        file << 21                             << ' '
             << (int) body_.getPosition().x/80 << ' '
             << (int) body_.getPosition().y/80 << ' '
             << type_;

        return file;
    }

}
