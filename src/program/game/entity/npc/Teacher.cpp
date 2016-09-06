/**
 * @file src/program/game/entity/npc/Teacher.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../../Resources.hpp"
#include "../../../funcs/files.hpp"
#include "../../../path_finder/PathFinder.hpp"

#include "Teacher.hpp"

namespace rr
{

    Teacher::Teacher(Type type) :
      type_(type)
    {
        velocity_                        = 900.f;
        attrs_.health = attrs_.maxHealth = 100.f;
        attrs_.armor                     =  50.f;
        attrs_.level                     =  30  ;

        initialize();
        body_.scale(sf::Vector2f(5, 5));
    }

    Teacher::Teacher(Teacher const& copy) :
      type_(copy.type_)
    {
        velocity_         = copy.velocity_;
        body_             = copy.body_;
        currentAnimation_ = copy.currentAnimation_;
    }

    void Teacher::initialize()
    {
        standingLeft_.setSpriteSheet(Resources::texture.npc);

        for (int i = 0; i < (type_ == KUNG_FU_MASTER ? 20 : 10); i++)
        {
            standingLeft_.addFrame(sf::IntRect(i*16, type_*16, 16, 16));
        }

        currentAnimation_ = &standingLeft_;

        attitude_ = NEUTRAL;

        body_.setAnimation(*currentAnimation_);
        body_.setLooped   (true);
        
        if (type_ == MAGE)
            body_.setFrameTime(sf::seconds(.4f));
        else  body_.setFrameTime(sf::seconds(.2f));

        // building dialogue trees
        switch (type_)
        {
            case SWORDSMAN:
            {
                auto root = new Answers();

                auto sup = new Sentence(Sentence::PLAYER, "Sup nigga.");
                    auto sup2 = new Sentence(Sentence::_NPC, "Sup. I can teach u magic with weapon but u first pay me lol.");
                        auto sup3 = new Sentence(Sentence::PLAYER, "K lmao.");
                        sup3->setLeft(root);

                    sup2->setLeft(sup3);

                sup->setLeft(sup2);
                root->addAnswer(sup);

                auto teachme = new Sentence(Sentence::PLAYER, "Show me how to kick asses.");
                    auto teaching = new Answers();
                        auto gz = new Sentence(Sentence::_NPC, "Gz.");
                        gz->setLeft(teaching);
                        
                        auto later = new Sentence(Sentence::_NPC, "Come later noob.");
                        later->setLeft(teaching);

                        auto cwm = new Sentence(Sentence::PLAYER, "Melee Weapon Mastery (10SP, 2 gold)");
                        cwm->setLeft(gz);
                        cwm->setRight(later);

                        auto str5 = new Sentence(Sentence::PLAYER, "+5STR (5SP, 1 gold)");
                        str5->setLeft(gz);
                        str5->setRight(later);

                        auto str1 = new Sentence(Sentence::PLAYER, "+1STR (1SP, 10 silver)");
                        str1->setLeft(gz);
                        str1->setRight(later);

                        auto back = new Sentence(Sentence::PLAYER, "Maybe later kek.");
                        back->setLeft(root);

                    teaching->addAnswer(cwm);
                    teaching->addAnswer(str5);
                    teaching->addAnswer(str1);
                    teaching->addAnswer(back);

                teachme->setLeft(teaching);
                root->addAnswer(teachme);

                auto bye = new Sentence(Sentence::PLAYER, "K bye."); // end
                root->addAnswer(bye);

                dialogue_.setTree(root, true);
            } break;
            
            case SHARPSHOOTER:
            {
                
            } break;

            case CARPENTER:
            {
                
            } break;
            
            case MAGE:
            {
                
            } break;
            
            case KUNG_FU_MASTER:
            {
                
            } break;
        }
    }

    void
    Teacher::update(int tiles[], sf::Time timeStep)
    {
        if (moving_)
        {
            sf::Vector2f offset = body_.getPosition()-(sf::Vector2f) position_*80.f;
            if (offset != sf::Vector2f(0, 0))
            {
                if (offset.x < 0) body_.move(sf::Vector2f( velocity_*timeStep.asSeconds(),  0));
                if (offset.x > 0) body_.move(sf::Vector2f(-velocity_*timeStep.asSeconds(),  0));
                if (offset.y < 0) body_.move(sf::Vector2f( 0,  velocity_*timeStep.asSeconds()));
                if (offset.y > 0) body_.move(sf::Vector2f( 0, -velocity_*timeStep.asSeconds()));
            }
            else
            {
                buffs_.speed        -= (buffs_.speed        == 0 ? 0 : 1);
                buffs_.regeneration -= (buffs_.regeneration == 0 ? 0 : 1);
                buffs_.poison       -= (buffs_.poison       == 0 ? 0 : 1);
                buffs_.slowness     -= (buffs_.slowness     == 0 ? 0 : 1);
                buffs_.weakness     -= (buffs_.weakness     == 0 ? 0 : 1);

                if (buffs_.poison > 0)
                    attrs_.health -= 1.f;

                if (buffs_.regeneration > 0)
                    attrs_.health += 0.15f;

                moving_ = false;
            }

            if (  (abs(offset.x) < velocity_/128 && abs(offset.x) > 0) // preventing the teacher from wobbling
               || (abs(offset.y) < velocity_/128 && abs(offset.y) > 0) // in between of two cells
                )  body_.setPosition((sf::Vector2f) position_*80.f);
        }

        body_.update(timeStep);

        switch (state_)
        {
            case STANDING : if      (   direction_        == LEFT
                                    && *currentAnimation_ != standingLeft_
                                     )  currentAnimation_ = &standingLeft_;

                            else if (   direction_        == RIGHT
                                    && *currentAnimation_ != standingRight_
                                     )  currentAnimation_ = &standingRight_;
                            break;

            case WAITING  : break;

            case EXPLORING: if (!moving_)
                            {
                                if (position_ == destination_)
                                {/*
                                    position_ = PathFinder::aStar(position_, destination_, tiles)[0] - position_;
                                    moving_ = true;*/
                                }
                                else
                                {
                                    state_ = STANDING;
                                }
                            }
                            break;
            
            case HUNTING  : break;
            
            case ESCAPING : break;
        }

        body_.play(*currentAnimation_);
    }

    void
    Teacher::handleDamage(int damage)
    {
        
    }

    sf::String
    Teacher::getName() const
    {
        switch (type_)
        {
            case SWORDSMAN     : return Resources::dictionary["npc.teacher.name.swordsman"     ];
            case SHARPSHOOTER  : return Resources::dictionary["npc.teacher.name.sharpshooter"  ];
            case CARPENTER     : return Resources::dictionary["npc.teacher.name.carpenter"     ];
            case MAGE          : return Resources::dictionary["npc.teacher.name.mage"          ];
            case KUNG_FU_MASTER: return Resources::dictionary["npc.teacher.name.kung_fu_master"];
        }

        return "";
    }

    std::ifstream&
    Teacher::operator<<(std::ifstream& file)
    {
        currentAnimation_->clearFrames();
        
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Teacher::operator>>(std::ofstream& file)
    {
        file << 21                             << ' '
             << (int) body_.getPosition().x/80 << ' '
             << (int) body_.getPosition().y/80 << ' '
             << type_;

        return file;
    }

}
