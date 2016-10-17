/**
 * @file src/program/game/entity/npc/NPCHunting.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_HUNTING_HPP
#define NPC_STATE_HUNTING_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCHunting : public NPCState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Reacts to an event.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* react(Level*, NPC*, Player&) override;
    };

}

#endif // NPC_STATE_HUNTING_HPP
