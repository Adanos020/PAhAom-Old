/**
 * @file src/program/game/entities/npc/ai/MeleeAI.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "MeleeAI.hpp"

namespace rr
{

    bool
    MeleeAI::canMoveTowards(Entity* entity, NPC* npc) const
    {
        return false;
    }

    void
    MeleeAI::moveTowards(Entity* entity, NPC* npc)
    {

    }

    bool
    MeleeAI::canMoveAwayFrom(Entity* entity, NPC* npc) const
    {
        return false;
    }

    void
    MeleeAI::moveAwayFrom(Entity* entity, NPC* npc)
    {

    }

    bool
    MeleeAI::canEscapeFrom(Entity* entity, NPC* npc) const
    {
        return false;
    }

    void
    MeleeAI::escapeFrom(Entity* entity, NPC* npc)
    {

    }

    bool
    MeleeAI::canAttack(Entity* entity, NPC* npc) const
    {
        auto distance = entity->getGridPosition() - npc->getGridPosition();
        return distance.x >= -1 && distance.x <= 1 && distance.y >= -1 && distance.y <= 1;
    }

    void
    MeleeAI::attack(Entity* entity, NPC* npc)
    {
        if (instanceof <Player, Entity> (entity))
            npc->attack((Player*) entity);

        else if (instanceof <NPC, Entity> (entity))
            npc->attack((NPC*) entity);
    }

    bool
    MeleeAI::tooCloseTo(Entity* entity, NPC* npc) const
    {
        return entity->getGridPosition() == npc->getGridPosition();
    }

    bool
    MeleeAI::tooFarFrom(Entity* entity, NPC* npc) const
    {
        auto distance = entity->getGridPosition() - npc->getGridPosition();
        return distance.x < -1 || distance.x > 1 || distance.y < -1 || distance.y > 1;
    }

    void
    MeleeAI::standStill()
    {

    }

}
