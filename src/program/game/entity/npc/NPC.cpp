/**
 * @file src/program/game/entity/npc/NPC.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "NPC.hpp"

namespace rr
{

    void
    NPC::placeDetectors()
    {
        m_entityDetector[0] = getGridPosition() + sf::Vector2i(-1, -1); // TOP LEFT
        m_entityDetector[1] = getGridPosition() + sf::Vector2i( 0, -1); // TOP
        m_entityDetector[2] = getGridPosition() + sf::Vector2i(+1, -1); // TOP RIGHT
        m_entityDetector[3] = getGridPosition() + sf::Vector2i(+1,  0); // RIGHT
        m_entityDetector[4] = getGridPosition() + sf::Vector2i(+1, +1); // BOTTOM RIGHT
        m_entityDetector[5] = getGridPosition() + sf::Vector2i( 0, +1); // BOTTOM
        m_entityDetector[6] = getGridPosition() + sf::Vector2i(-1, +1); // BOTTOM LEFT
        m_entityDetector[7] = getGridPosition() + sf::Vector2i(-1,  0); // LEFT
    }

    void
    NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Resources::texture.items;
        target.draw(m_body, states);
    }

    void
    NPC::setGridPosition(sf::Vector2i pos)
    {
        m_position = pos;
        m_body.setPosition((sf::Vector2f) pos*80.f);
        placeDetectors();
    }

    sf::Vector2i
    NPC::getGridPosition() const
    {
        return m_position;
    }

    void
    NPC::setPosition(sf::Vector2f pos)
    {
        m_position = (sf::Vector2i) pos/80;
        m_body.setPosition(pos);
        placeDetectors();
    }

    sf::Vector2f
    NPC::getPosition() const
    {
        return m_body.getPosition();
    }

    bool
    NPC::collides(Entity* e) const
    {
        return e->getBounds().intersects(getBounds());
    }

    sf::FloatRect
    NPC::getBounds() const
    {
        return m_body.getGlobalBounds();
    }

    void
    NPC::setDestination(sf::Vector2i dest)
    {
        m_destination = dest;
    }

    sf::Vector2i
    NPC::getDestination() const
    {
        return m_destination;
    }

    DialogueTree*
    NPC::getDialogue() const
    {
        return (DialogueTree*) &m_dialogue;
    }

    void
    NPC::setAttitude(Attitude attitude)
    {
        m_attitude = attitude;
    }

    NPC::Attitude
    NPC::getAttitude() const
    {
        return m_attitude;
    }

    void
    NPC::setState(State state)
    {
        m_state = state;
    }

    NPC::State
    NPC::getState() const
    {
        return m_state;
    }

    void
    NPC::setDirection(Direction direction)
    {
        m_direction = direction;
    }

    NPC::Direction
    NPC::getDirection() const
    {
        return m_direction;
    }

    void
    NPC::move(int tiles[], Direction di)
    {
        if (!m_moving)
        {
            if (di == UP    && (tiles[m_position.x   + (m_position.y-1)*77] != 1 && tiles[m_position.x   + (m_position.y-1)*77] != 5))
            {
                m_position = sf::Vector2i(m_position.x, m_position.y-1);
                m_moving = true;
            }
            if (di == DOWN  && (tiles[m_position.x   + (m_position.y+1)*77] != 1 && tiles[m_position.x   + (m_position.y+1)*77] != 5))
            {
                m_position = sf::Vector2i(m_position.x, m_position.y+1);
                m_moving = true;
            }
            if (di == LEFT)
            {
                if (tiles[m_position.x-1 + m_position.y*77] != 1 && tiles[m_position.x-1 + m_position.y*77] != 5)
                {
                    m_position = sf::Vector2i(m_position.x-1, m_position.y);
                    m_moving = true;
                }
                m_currentAnimation = &m_walkingLeft;
            }
            if (di == RIGHT)
            {
                if (tiles[m_position.x+1 + m_position.y*77] != 1 && tiles[m_position.x+1 + m_position.y*77] != 5)
                {
                    m_position = sf::Vector2i(m_position.x+1, m_position.y);
                    m_moving = true;
                }
                m_currentAnimation = &m_walkingRight;
            }
        }
    }

    NPC::Attrs
    NPC::getAttributes() const
    {
        return m_attrs;
    }

    int
    NPC::detects(Entity* e) const
    {
        for (int i = 0; i < 8; ++i)
        {
            if (e->getGridPosition() == m_entityDetector[i])
                return i;
        }
        return -1;
    }

}
