/**
 * @file src/program/game/entity/npc/state/NPCSleeping.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCSleeping.hpp"
#include "../../../FOV.hpp"

namespace rr
{

    NPCState*
    NPCSleeping::update(sf::Time&, NPC* npc)
    {
        if (npc->m_direction == NPC::LEFT && *npc->m_currentAnimation != npc->m_standingLeft)
            npc->m_currentAnimation = &npc->m_standingLeft;

        else if (npc->m_direction == NPC::RIGHT && *npc->m_currentAnimation != npc->m_standingRight)
            npc->m_currentAnimation = &npc->m_standingRight;

        return nullptr;
    }

    NPCState*
    NPCSleeping::react(Level* level, NPC* npc, Player* player)
    {
        if (npc->getAttitude() == NPC::HOSTILE)
        {
            if ((npc->detects(player) >= 0) || (FOV::seesEntity(*level, npc, player) && chance(1, 5)))
                return &hunting;
        }

        return nullptr;
    }

    sf::String
    NPCSleeping::toString() const
    { return "SLEEPING"; }

}