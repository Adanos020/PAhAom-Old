/**
 * @file src/program/game/entity/npc/state/NPCAttacking.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCAttacking.hpp"
#include <iostream>

namespace rr
{

    NPCState*
    NPCAttacking::update(sf::Time&, NPC*)
    { return &hunting; }

    NPCState*
    NPCAttacking::react(Level*, NPC*, Player*)
    { return nullptr; }

    sf::String
    NPCAttacking::toString() const
    { return "ATTACKING"; }

}