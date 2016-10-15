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
           m_attrs.maxHealth = 10.f;
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
        m_body.setFrameTime(sf::seconds(.1f));

        m_attitude = HOSTILE;
        m_state = new NPCSleeping();
    }

    void
    Bandit::update(int tiles[], sf::Time& delta)
    {
        auto newState = m_state->update(delta, this);
        if (newState != nullptr)
            m_state = newState;

        m_body.update(delta);

        if (!m_body.isPlaying())
        {
            if      (m_direction == LEFT ) m_currentAnimation = &m_standingLeft;
            else if (m_direction == RIGHT) m_currentAnimation = &m_standingRight;
            m_body.setLooped(true);
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

    int
    Bandit::handleDamage(int damage)
    {
        if (damage >= m_attrs.armor)
        {
            m_attrs.health -= (damage - m_attrs.armor);
            m_state = &m_state->hunting;
        }

        return damage - m_attrs.armor;
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
            readFile < int > (file, position.x);
            readFile < int > (file, position.y);
            readFile < int > (file, state);
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
