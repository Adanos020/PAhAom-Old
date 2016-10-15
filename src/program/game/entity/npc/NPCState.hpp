/**
 * @file src/program/game/entity/npc/NPCState.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_HPP
#define NPC_STATE_HPP

#include "../Player.hpp"

namespace rr
{

    class NPC;

    class NPCAttacking;
    class NPCHunting;
    class NPCMoving;
    class NPCSleeping;

    class NPCState
    {
        public:
         static NPCAttacking attacking;
         static NPCHunting   hunting;
         static NPCMoving    moving;
         static NPCSleeping  sleeping;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Virtual destructor.
                ////////////////////////////////////////////////////////////////////////
        virtual ~NPCState() {}

                ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Reacts to an event.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* react(Level*, NPC*, Player&) = 0;
    };

}

#include "NPCAttacking.hpp"
#include "NPCHunting.hpp"
#include "NPCMoving.hpp"
#include "NPCSleeping.hpp"

#include "../../Level.hpp"

#include "../NPC.hpp"

#endif // NPC_STATE_HPP
