/**
 * @file src/program/game/entity/npc/NPCStanding.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_STANDING_HPP
#define NPC_STATE_STANDING_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCStanding : public NPCState
    {
        public: 

                ////////////////////////////////////////////////////////////////////////
                /// \brief Virtual destructor.
                ////////////////////////////////////////////////////////////////////////
        virtual ~NPCStanding() {}

                ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*, Player&, Level*) override;
    };

}

#endif // NPC_STATE_STANDING_HPP
