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
        m_moving   = false;

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

        m_body.setAnimation(*m_currentAnimation);
        m_body.setLooped(true);
        
        if (m_type == MAGE)
            m_body.setFrameTime(sf::seconds(.4f));
        else  m_body.setFrameTime(sf::seconds(.2f));

        // building dialogue trees
        switch (m_type)
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

                m_dialogue.setTree(root, true);
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
    Teacher::update(int tiles[], sf::Time& timeStep)
    {
        if (m_moving)
        {
            sf::Vector2f offset = m_body.getPosition()-(sf::Vector2f) m_position*80.f;
            if (offset != sf::Vector2f(0, 0))
            {
                if (offset.x < 0) m_body.move(sf::Vector2f( m_velocity*timeStep.asSeconds(),  0));
                if (offset.x > 0) m_body.move(sf::Vector2f(-m_velocity*timeStep.asSeconds(),  0));
                if (offset.y < 0) m_body.move(sf::Vector2f( 0,  m_velocity*timeStep.asSeconds()));
                if (offset.y > 0) m_body.move(sf::Vector2f( 0, -m_velocity*timeStep.asSeconds()));
            }
            else
            {
                m_buffs.speed        -= (m_buffs.speed        == 0 ? 0 : 1);
                m_buffs.regeneration -= (m_buffs.regeneration == 0 ? 0 : 1);
                m_buffs.poison       -= (m_buffs.poison       == 0 ? 0 : 1);
                m_buffs.slowness     -= (m_buffs.slowness     == 0 ? 0 : 1);
                m_buffs.weakness     -= (m_buffs.weakness     == 0 ? 0 : 1);

                if (m_buffs.poison > 0)
                    m_attrs.health -= 1.f;

                if (m_buffs.regeneration > 0)
                    m_attrs.health += 0.15f;

                m_moving = false;
            }

            if (  (abs(offset.x) < m_velocity/128 && abs(offset.x) > 0) // preventing the teacher from wobbling
               || (abs(offset.y) < m_velocity/128 && abs(offset.y) > 0) // in between of two cells
                )  m_body.setPosition((sf::Vector2f) m_position*80.f);
        }

        m_body.update(timeStep);

        m_body.play(*m_currentAnimation);
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
