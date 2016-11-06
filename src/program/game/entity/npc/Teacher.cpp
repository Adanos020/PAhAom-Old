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

    void Teacher::initialize()
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

                m_dialogue.setTree(conv1, true);
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

        m_type = (Type) type;

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
             << m_type;

        return file;
    }

}
