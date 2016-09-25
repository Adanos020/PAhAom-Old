/**
 * @file src/program/game/entities/npc/ai/AIManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_AI_MANAGER_HPP
#define NPC_AI_MANAGER_HPP

namespace rr
{

    class NPC;
    class Level;
    class Player;

    class AIManager
    {
        private: Level*  m_level;
                 Player* m_player;

        public:  ////////////////////////////////////////////////////////////////////////
                 /// \brief Regular constructor.
                 ////////////////////////////////////////////////////////////////////////
                 AIManager(Level* = nullptr, Player* = nullptr);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Makes orders to a given NPC.
                 ////////////////////////////////////////////////////////////////////////
                 void makeOrders(NPC*);
    };

}

#include "../../../Level.hpp"

#endif // NPC_AI_MANAGER_HPP
