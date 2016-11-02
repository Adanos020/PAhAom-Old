/**
 * @file src/program/game/entity/npc/state/NPCMoving.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <cmath>

#include "../NPCMoving.hpp"

namespace rr
{

    NPCState*
    NPCMoving::update(sf::Time& delta, NPC* npc)
    {
        sf::Vector2f offset = npc->m_body.getPosition() - (sf::Vector2f) npc->m_position*80.f;
        if (offset != sf::Vector2f(0, 0))
        {
            auto displacement = npc->m_velocity*delta.asSeconds();

            if (offset.x < 0 && displacement-2 >= offset.x) npc->m_body.move(sf::Vector2f( displacement,  0));
            if (offset.x > 0 && displacement+2 <= offset.x) npc->m_body.move(sf::Vector2f(-displacement,  0));
            if (offset.y < 0 && displacement-2 >= offset.y) npc->m_body.move(sf::Vector2f( 0,  displacement));
            if (offset.y > 0 && displacement+2 <= offset.y) npc->m_body.move(sf::Vector2f( 0, -displacement));

            if (  (fabs(offset.x) < npc->m_velocity/128 && fabs(offset.x) > 0) // preventing the npc from wobbling
               || (fabs(offset.y) < npc->m_velocity/128 && fabs(offset.y) > 0) // in between of two cells
                )  npc->m_body.setPosition((sf::Vector2f) npc->m_position*80.f);

            return nullptr;
        }
        npc->m_buffs.speed        -= (npc->m_buffs.speed        == 0 ? 0 : 1);
        npc->m_buffs.regeneration -= (npc->m_buffs.regeneration == 0 ? 0 : 1);
        npc->m_buffs.poison       -= (npc->m_buffs.poison       == 0 ? 0 : 1);
        npc->m_buffs.slowness     -= (npc->m_buffs.slowness     == 0 ? 0 : 1);
        npc->m_buffs.weakness     -= (npc->m_buffs.weakness     == 0 ? 0 : 1);

        if (npc->m_buffs.poison > 0)
            npc->m_attrs.health -= 1.f;

        if (npc->m_buffs.regeneration > 0)
            npc->m_attrs.health += 0.15f;

        return &hunting;
    }

    NPCState*
    NPCMoving::react(Level* level, NPC* npc, Player* player)
    {
        return nullptr;
    }

    sf::String
    NPCMoving::toString() const
    { return "MOVING"; }

}