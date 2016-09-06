/**
 * @file src/program/game/entities/npc/ai/AIManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_AI_MANAGER_HPP
#define NPC_AI_MANAGER_HPP

namespace rr
{

    class NPC;
    class Level;

    class AIManager
    {
        private: Level* m_level;

        public:  ////////////////////////////////////////////////////////////////////////
                 /// \brief Regular constructor.
                 ////////////////////////////////////////////////////////////////////////
                 AIManager(Level* = nullptr);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Makes orders to a given NPC.
                 ////////////////////////////////////////////////////////////////////////
                 void makeOrders(NPC*);
    };

}

#include "../../../level/Level.hpp"

#endif // NPC_AI_MANAGER_HPP
