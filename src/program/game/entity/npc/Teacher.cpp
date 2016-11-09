/**
 * @file src/program/game/entity/npc/Teacher.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../../../Resources.hpp"
#include "../../../funcs/files.hpp"
#include "../../PathFinder.hpp"

#include "Teacher.hpp"

namespace rr
{

    Teacher::Teacher(Type type) :
      m_type(type)
    {
        m_velocity = 900.f;

        m_attrs.health = m_attrs.maxHealth = 100.f;
        m_attrs.armor                      =  50.f;
        m_attrs.level                      =  30  ;

        initialize();
        m_body.scale(sf::Vector2f(5, 5));
    }

    Teacher::Teacher(Teacher const& copy) :
      m_type(copy.m_type)
    {
        m_velocity         = copy.m_velocity;
        m_body             = copy.m_body;
        m_currentAnimation = copy.m_currentAnimation;
    }

    void
    Teacher::setDialogue(Branch::SwitchTo dtype)
    {
        if (dtype != Branch::NONE)
            m_dialogueType = dtype;
        switch (dtype)
        {
            case Branch::QUEST: m_currentDialogue = &m_dialogue_quest; break;
            case Branch::CHECK: m_currentDialogue = &m_dialogue_check; break;
            case Branch::TEACH: m_currentDialogue = &m_dialogue_teach; break;

            default: break;
        }
    }

    void
    Teacher::initialize()
    {
        m_standingLeft.setSpriteSheet(Resources::texture.npc);

        for (int i = 0; i < (m_type == KUNG_FU_MASTER ? 20 : 10); i++)
        {
            m_standingLeft.addFrame(sf::IntRect(i*16, m_type*16, 16, 16));
        }

        m_currentAnimation = &m_standingLeft;

        m_attitude = NEUTRAL;
        m_state = new NPCSleeping();
        m_stepsToFollow = 0;

        m_body.setAnimation(*m_currentAnimation);
        m_body.setLooped(true);
        
        if (m_type == MAGE)
            m_body.setFrameTime(sf::seconds(.4f));
        else
            m_body.setFrameTime(sf::seconds(.2f));

        // building dialogue trees
        switch (m_type)
        {
            case SWORDSMAN:
            {
                // QUEST
                auto conv1  = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.1"]);
                auto conv2  = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.2"]);
                auto conv3  = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.3"]);
                auto conv4  = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.4"]);
                auto conv5  = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.5"]);
                auto conv6  = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.6"]);
                auto conv7  = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.7"]);
                auto conv8  = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.8"]);
                auto conv9  = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.9"]);
                auto conv10 = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.10"]);
                auto conv11 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.11"]);
                auto conv12 = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.conv.12"]);
                auto conv13 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.conv.13"]);

                conv1->setLeft(conv2);
                conv2->setLeft(conv3);
                conv3->setLeft(conv4);
                conv4->setLeft(conv5);
                conv5->setLeft(conv6);
                conv6->setLeft(conv7);
                conv7->setLeft(conv8);
                conv8->setLeft(conv9);
                conv9->setLeft(conv10);
                conv10->setLeft(conv11);
                conv11->setLeft(conv12);
                conv12->setLeft(conv13);
                conv13->setLeft(nullptr); // end

                conv13->switchTo = Branch::CHECK;

                m_dialogue_quest.setTree(conv1, true);

                // CHECK
                auto check1 = new Sentence(Sentence::_NPC, Resources::dictionary["teacher.swordsman.question.1"]);

                auto check2 = new Answers();
                    auto check2_1 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.questfail.2"]);
                    auto check2_2 = new Sentence(Sentence::_NPC  , Resources::dictionary["teacher.swordsman.questfail.3"]);

                    auto check2_3 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.questsuccess.1"]);
                    auto check2_4 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.questsuccess.2"]);

                    check2_1->setLeft(check2_2);
                    check2_2->setLeft(nullptr); // end
                    
                    check2_3->setLeft(check2_4);
                    check2_4->setLeft(nullptr); // end

                    check2_4->switchTo = Branch::TEACH;

                    check2->addAnswer(check2_1);
                    check2->addAnswer(check2_3);

                check1->setLeft(check2);

                m_dialogue_check.setTree(check1);

                // TEACH
                auto teach = new Answers();
                    auto teach1 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.teachme"]);
                    
                    auto skills = new Answers();
                        auto skills1 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.skill"]);
                        auto skills2 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.strength5"]);
                        auto skills3 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.swordsman.strength1"]);
                        auto skills4 = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.later"]);

                        auto success = new Sentence(Sentence::_NPC, Resources::dictionary["teacher.learnsuccess"]);
                        auto failure = new Sentence(Sentence::_NPC, Resources::dictionary["teacher.learnfailure"]);

                        skills1->setLeft(success);
                        skills1->setRight(failure);

                        skills2->setLeft(success);
                        skills2->setRight(failure);

                        skills3->setLeft(success);
                        skills3->setRight(failure);

                        skills4->setLeft(teach);

                        success->setLeft(skills);
                        failure->setLeft(skills);

                        skills->addAnswer(skills1);
                        skills->addAnswer(skills2);
                        skills->addAnswer(skills3);
                        skills->addAnswer(skills4);
                        
                    teach1->setLeft(skills);

                    auto seeya = new Sentence(Sentence::PLAYER, Resources::dictionary["teacher.bye"]);

                    teach->addAnswer(teach1);
                    teach->addAnswer(seeya);

                    seeya->setLeft(nullptr); // end

                m_dialogue_teach.setTree(teach);

                m_currentDialogue = &m_dialogue_quest;
            }
            break;

            case SHARPSHOOTER:
            {

            }
            break;

            case CARPENTER:
            {

            }
            break;
            
            case MAGE:
            {

            }
            break;
            
            case KUNG_FU_MASTER:
            {

            }
            break;
        }
    }

    int
    Teacher::handleDamage(int damage)
    {
        if (damage >= m_attrs.armor)
        {
            m_attrs.health -= (damage - m_attrs.armor);
            m_state = &m_state->hunting;
        }

        return damage - m_attrs.armor;
    }

    sf::String
    Teacher::getName() const
    {
        switch (m_type)
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
        m_currentAnimation->clearFrames();
        
        sf::Vector2i position;
        int type;
        int dtype;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, type);
            readFile <int> (file, dtype);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;
        m_dialogueType = (Branch::SwitchTo) dtype;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Teacher::operator>>(std::ofstream& file)
    {
        file << 21                              << ' '
             << (int) m_body.getPosition().x/80 << ' '
             << (int) m_body.getPosition().y/80 << ' '
             << m_type                          << ' '
             << m_dialogueType;

        return file;
    }

}
