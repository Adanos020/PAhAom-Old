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

        m_attrs.health = m_attrs.maxHealth =  20.f;
        m_attrs.armor                      =   5.f;
        m_attrs.level                      =   5  ;

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
        m_standingLeft.setSpriteSheet(Resources::texture.enemies);
        m_standingRight.setSpriteSheet(Resources::texture.enemies);

        m_walkingLeft.setSpriteSheet(Resources::texture.enemies);
        m_walkingRight.setSpriteSheet(Resources::texture.enemies);

        m_attackingLeft.setSpriteSheet(Resources::texture.enemies);
        m_attackingRight.setSpriteSheet(Resources::texture.enemies);

        // adding the frames to the animations
        m_standingLeft.addFrame(sf::IntRect(0, m_type*32 + 16, 16, 16));

        m_standingRight.addFrame(sf::IntRect(0, m_type*32, 16, 16));

        m_walkingLeft.addFrame(sf::IntRect( 0, m_type*32 + 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(16, m_type*32 + 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect( 0, m_type*32 + 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(32, m_type*32 + 16, 16, 16));

        m_walkingRight.addFrame(sf::IntRect( 0, m_type*32, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(16, m_type*32, 16, 16));
        m_walkingRight.addFrame(sf::IntRect( 0, m_type*32, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(32, m_type*32, 16, 16));

        m_attackingLeft.addFrame(sf::IntRect(0, m_type*32 + 16, 16, 16));

        m_attackingRight.addFrame(sf::IntRect(0, m_type*32, 16, 16));

        m_currentAnimation = chance(1, 2) ? &m_standingLeft : &m_standingRight;

        // setting the animated sprite's properties
        m_body.setAnimation(*m_currentAnimation);
        m_body.setLooped(true);
        m_body.setFrameTime(sf::seconds(.2f));

        m_attitude = AGGRESSIVE;
        m_state    = chance(1, 3) ? STANDING : WAITING;
    }

    void
    Bandit::update(int tiles[], sf::Time timeStep)
    {
        if (m_moving)
        {
            sf::Vector2f offset = m_body.getPosition() - (sf::Vector2f) m_position*80.f;
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

            if (  (abs(offset.x) < m_velocity/128 && abs(offset.x) > 0) // preventing the bandit from wobbling
               || (abs(offset.y) < m_velocity/128 && abs(offset.y) > 0) // in between of two cells
                )  m_body.setPosition((sf::Vector2f) m_position*80.f);
        }

        m_body.update(timeStep);

        if (!m_body.isPlaying())
        {
            if      (m_direction == LEFT ) m_currentAnimation = &m_standingLeft;
            else if (m_direction == RIGHT) m_currentAnimation = &m_standingRight;
            m_body.setLooped(true);
        }

        switch (m_state)
        {
            case STANDING : if      (   m_direction        == LEFT
                                    && *m_currentAnimation != m_standingLeft
                                     )  m_currentAnimation = &m_standingLeft;

                            else if (   m_direction        == RIGHT
                                    && *m_currentAnimation != m_standingRight
                                     )  m_currentAnimation = &m_standingRight;
                            break;

            case WAITING  : break;

            case EXPLORING: if (!m_moving)
                            {
                                if (m_position != m_destination)
                                {
                                    //m_position = PathFinder::aStar(m_position, m_destination, tiles)[0];
                                    m_moving = true;
                                }
                                else
                                {
                                    m_state = STANDING;
                                }
                            }
                            break;

            case HUNTING  : break;

            case ESCAPING : break;
        }

        m_body.play(*m_currentAnimation);
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

    void
    Bandit::handleDamage(int damage)
    {
        if (damage >= m_attrs.armor)
            m_attrs.health -= (damage - m_attrs.armor);
        m_state = HUNTING;
    }

    void
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

        npc->handleDamage(range(0, maxDamage));
    }

    void
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

        player->handleDamage(range(0, maxDamage));
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
        int state     = 0,
            direction = 0,
            type      = 0;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, state);
            readFile <int> (file, direction);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_state     = (  State  )     state;
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
             << m_state                         << ' '
             << m_direction                     << ' '
             << m_type;

        return file;
    }

}
