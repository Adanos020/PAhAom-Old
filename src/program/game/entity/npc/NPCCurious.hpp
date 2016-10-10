/**
 * @file src/program/game/entity/npc/NPCCurious.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_CURIOUS_HPP
#define NPC_STATE_CURIOUS_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCCurious : public NPCState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Virtual destructor.
                ////////////////////////////////////////////////////////////////////////
        virtual ~NPCCurious() {}

                ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Reacts to an event.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* react(Level*, NPC*, Player&) override;
    };

}

#endif // NPC_STATE_CURIOUS_HPP
