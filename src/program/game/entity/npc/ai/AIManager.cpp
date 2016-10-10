/**
 * @file src/program/game/entities/npc/ai/AIManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../../../../Observer.hpp"
#include "../../../FOV.hpp"
#include "../../../PathFinder.hpp"

#include "AIManager.hpp"

extern rr::Subject subject;

namespace rr
{

    AIManager::AIManager(Level* level, Player* player) :
      m_level (level),
      m_player(player)
    {}

    void
    AIManager::makeOrders(NPC* npc)
    {
        
    }

}
