/**
 * @file src/program/game/entity/npc/NPCState.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_HPP
#define NPC_STATE_HPP

#include "../NPC.hpp"
#include "../Player.hpp"

namespace rr
{

    class NPCState
    {
        public: 

                ////////////////////////////////////////////////////////////////////////
                /// \brief Virtual destructor.
                ////////////////////////////////////////////////////////////////////////
        virtual ~NPCState() {}

                ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*, Player&, Level*) = 0;
    };

}

#include "../../Level.hpp"

#endif // NPC_STATE_HPP
