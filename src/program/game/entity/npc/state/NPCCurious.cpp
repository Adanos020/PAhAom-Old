/**
 * @file src/program/game/entity/npc/state/NPCCurious.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCCurious.hpp"

#include "../../../FOV.hpp"
#include "../../../PathFinder.hpp"

namespace rr
{

    NPCState*
    NPCCurious::update(sf::Time& delta, NPC* npc)
    {
        return nullptr;
    }

    NPCState*
    NPCCurious::react(Level* level, NPC* npc, Player& player)
    {
        while (true)
        {
            int x=rand()%level->getSize().x, y=rand()%level->getSize().y;
            if (level->getTilesAsCells()[x + y*level->getSize().x] == Level::ROOM)
            {
                npc->setDestination(sf::Vector2i(x, y));
                break;
            }
        }

        if (npc->getGridPosition() != npc->getDestination())
        {
            auto path = PathFinder::aStar(npc->getDestination(), npc->getGridPosition(), level->getTiles());
            if (!path.empty())
            {
                auto offset = npc->getGridPosition() - path.front();
                if (offset == sf::Vector2i(0, -1))
                    npc->move(level->getTiles(), NPC::UP);
                else if (offset == sf::Vector2i(0, 1))
                    npc->move(level->getTiles(), NPC::DOWN);
                else if (offset == sf::Vector2i(-1, 0))
                    npc->move(level->getTiles(), NPC::LEFT);
                else if (offset == sf::Vector2i(1, 0))
                    npc->move(level->getTiles(), NPC::RIGHT);
            }
        }

        if (npc->getAttitude() == NPC::HOSTILE
          && (npc->detects(&player) >= 0 || FOV::seesEntity(level->getTiles(), npc, &player)))
            return &hunting;

        return nullptr;
    }

}