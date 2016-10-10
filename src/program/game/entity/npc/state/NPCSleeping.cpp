/**
 * @file src/program/game/entity/npc/state/NPCSleeping.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCSleeping.hpp"

namespace rr
{

    NPCState*
    NPCSleeping::update(sf::Time& delta, NPC* npc)
    {
        if (npc->m_direction == NPC::LEFT && *npc->m_currentAnimation != npc->m_standingLeft)
            npc->m_currentAnimation = &npc->m_standingLeft;

        else if (npc->m_direction == NPC::RIGHT && *npc->m_currentAnimation != npc->m_standingRight)
            npc->m_currentAnimation = &npc->m_standingRight;

        return nullptr;
    }

    NPCState*
    NPCSleeping::react(Level* level, NPC* npc, Player& player)
    {
        return nullptr;
    }

}