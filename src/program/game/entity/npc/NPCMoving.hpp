/**
 * @file src/program/game/entity/npc/NPCMoving.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_MOVING_HPP
#define NPC_STATE_MOVING_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCMoving : public NPCState
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

#endif // NPC_STATE_MOVING_HPP
