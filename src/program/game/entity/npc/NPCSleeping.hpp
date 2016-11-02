/**
 * @file src/program/game/entity/npc/NPCSleeping.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_SLEEPING_HPP
#define NPC_STATE_SLEEPING_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCSleeping : public NPCState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Reacts to an event.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* react(Level*, NPC*, Player*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Returns the string of the state.
                ////////////////////////////////////////////////////////////////////////
        virtual sf::String toString() const override;
    };

}

#endif // NPC_STATE_SLEEPING_HPP
