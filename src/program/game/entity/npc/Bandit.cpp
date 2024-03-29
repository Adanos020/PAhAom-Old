/**
 * @file src/program/game/entity/npc/Bandit.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../../../Resources.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

#include "../../PathFinder.hpp"

#include "Bandit.hpp"

namespace rr
{

    Bandit::Bandit(Type type) :
      m_type(type)
    {
        m_velocity = 900.f;
        m_moving   = false;

        m_attrs.health =
           m_attrs.maxHealth = 20.f;
        m_attrs.armor        =  5.f;
        m_attrs.level        =  5  ;

        initialize();
        m_body.scale(sf::Vector2f(5, 5));
    }

    Bandit::Bandit(Bandit const& copy) :
      m_type(copy.m_type)
    {
        m_velocity         = copy.m_velocity;
        m_attrs            = copy.m_attrs;
        m_body             = copy.m_body;
        m_currentAnimation = copy.m_currentAnimation;
    }

    void
    Bandit::initialize()
    {
        // loading the sprite sheets for the animations
        switch (m_type)
        {
            case CLUB:
            {
                m_standingLeft.setSpriteSheet(Resources::texture.npc_bully);
                m_standingRight.setSpriteSheet(Resources::texture.npc_bully);

                m_walkingLeft.setSpriteSheet(Resources::texture.npc_bully);
                m_walkingRight.setSpriteSheet(Resources::texture.npc_bully);

                m_attackingLeft.setSpriteSheet(Resources::texture.npc_bully);
                m_attackingRight.setSpriteSheet(Resources::texture.npc_bully);
            }
            break;

            case CROSSBOW:
            {
                m_standingLeft.setSpriteSheet(Resources::texture.npc_csbow);
                m_standingRight.setSpriteSheet(Resources::texture.npc_csbow);

                m_walkingLeft.setSpriteSheet(Resources::texture.npc_csbow);
                m_walkingRight.setSpriteSheet(Resources::texture.npc_csbow);

                m_attackingLeft.setSpriteSheet(Resources::texture.npc_csbow);
                m_attackingRight.setSpriteSheet(Resources::texture.npc_csbow);
            }
            break;

            case DAGGER:
            {
                m_standingLeft.setSpriteSheet(Resources::texture.npc_rogue);
                m_standingRight.setSpriteSheet(Resources::texture.npc_rogue);

                m_walkingLeft.setSpriteSheet(Resources::texture.npc_rogue);
                m_walkingRight.setSpriteSheet(Resources::texture.npc_rogue);

                m_attackingLeft.setSpriteSheet(Resources::texture.npc_rogue);
                m_attackingRight.setSpriteSheet(Resources::texture.npc_rogue);
            }
            break;
        }

        // adding the frames to the animations
        m_standingLeft.addFrame(sf::IntRect(0, 16, 16, 16));

        m_standingRight.addFrame(sf::IntRect(0, 0, 16, 16));

        m_walkingLeft.addFrame(sf::IntRect( 0, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(16, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect( 0, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(32, 16, 16, 16));

        m_walkingRight.addFrame(sf::IntRect( 0, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(16, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect( 0, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(32, 0, 16, 16));

        m_attackingLeft.addFrame(sf::IntRect( 0, 32, 16, 16));
        m_attackingLeft.addFrame(sf::IntRect(16, 32, 16, 16));
        m_attackingLeft.addFrame(sf::IntRect(32, 32, 16, 16));
        m_attackingLeft.addFrame(sf::IntRect( 0, 32, 16, 16));

        m_attackingRight.addFrame(sf::IntRect( 0, 48, 16, 16));
        m_attackingRight.addFrame(sf::IntRect(16, 48, 16, 16));
        m_attackingRight.addFrame(sf::IntRect(32, 48, 16, 16));
        m_attackingRight.addFrame(sf::IntRect( 0, 48, 16, 16));

        m_currentAnimation = chance(1, 2) ? &m_standingLeft : &m_standingRight;

        m_direction = (m_currentAnimation == &m_standingLeft) ? LEFT : RIGHT;

        // setting the animated sprite's properties
        m_body.setAnimation(*m_currentAnimation);
        m_body.setLooped(true);
        m_body.setFrameTime(sf::seconds(.1f));

        m_attitude = HOSTILE;
        m_state = new NPCSleeping();
        m_stepsToFollow = 0;
    }

    sf::String
    Bandit::getName() const
    {
        switch (m_type)
        {
            case CLUB    : return Resources::dictionary["npc.bandit.name.bully"      ]; break;
            case CROSSBOW: return Resources::dictionary["npc.bandit.name.crossbowman"]; break;
            case DAGGER  : return Resources::dictionary["npc.bandit.name.rogue"      ]; break;
        }

        return "";
    }

    int
    Bandit::handleDamage(int damage)
    {
        if (damage >= m_attrs.armor)
        {
            damage -= m_attrs.armor;
            m_state = &m_state->hunting;
        }
        else
        {
            damage = 0;
        }

        m_attrs.health -= damage;
        return damage;
    }

    int
    Bandit::attack(NPC* npc)
    {
        if      (m_direction == LEFT ) m_currentAnimation = &m_attackingLeft;
        else if (m_direction == RIGHT) m_currentAnimation = &m_attackingRight;
        m_body.setLooped(false);

        int maxDamage = 0;
        switch (m_type)
        {
            case CLUB    : maxDamage = 10; break;
            case CROSSBOW: maxDamage =  5; break;
            case DAGGER  : maxDamage =  8; break;
        }

        return npc->handleDamage(range(0, maxDamage));
    }

    int
    Bandit::attack(Player* player)
    {
        if      (m_direction == LEFT ) m_currentAnimation = &m_attackingLeft;
        else if (m_direction == RIGHT) m_currentAnimation = &m_attackingRight;
        m_body.setLooped(false);

        int maxDamage = 0;
        switch (m_type)
        {
            case CLUB    : maxDamage = 10; break;
            case CROSSBOW: maxDamage =  5; break;
            case DAGGER  : maxDamage =  8; break;
        }

        return player->handleDamage(range(0, maxDamage));
    }

    std::ifstream&
    Bandit::operator<<(std::ifstream& file)
    {
        m_standingLeft  .clearFrames();
        m_standingRight .clearFrames();
        m_walkingLeft   .clearFrames();
        m_walkingRight  .clearFrames();
        m_attackingLeft .clearFrames();
        m_attackingRight.clearFrames();

        sf::Vector2i position;
        int direction = 0,
            type      = 0;

        try
        {
            readFile < int > (file, position.x);
            readFile < int > (file, position.y);
            readFile < int > (file, direction);
            readFile < int > (file, type);
            readFile <float> (file, m_attrs.health);
            readFile <float> (file, m_attrs.maxHealth);
            readFile < int > (file, m_attrs.level);
            readFile <float> (file, m_attrs.armor);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_direction = (Direction) direction;
        m_type      = (   Type  )      type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Bandit::operator>>(std::ofstream& file)
    {
        file << 20                              << ' '
             << (int) m_body.getPosition().x/80 << ' '
             << (int) m_body.getPosition().y/80 << ' '
             << m_direction                     << ' '
             << m_type                          << ' '
             << m_attrs.health                  << ' '
             << m_attrs.maxHealth               << ' '
             << m_attrs.level                   << ' '
             << m_attrs.armor                   << ' ';

        return file;
    }

}
