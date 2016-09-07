/**
 * @file src/program/game/entities/npc/ai/AIManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../../../../observer/Observer.hpp"
#include "../../../fov/FOV.hpp"

#include "AIManager.hpp"

extern rr::Subject subject;

namespace rr
{

    AIManager::AIManager(Level* level, Player* player) :
      m_level (level),
      m_player(player) {}

    void
    AIManager::makeOrders(NPC* npc)
    {
        if (npc->getState() == NPC::STANDING)
        {
            while (true)
            {
                int x=rand()%m_level->getSize().x, y=rand()%m_level->getSize().y;
                if (m_level->getTilesAsCells()[x + y*m_level->getSize().x] == Level::ROOM && m_level->getTilesAsCells()[x + y*m_level->getSize().x] != Level::OCCUPIED)
                {
                    npc->setDestination(sf::Vector2i(x, y));
                    npc->setState(NPC::EXPLORING);
                    break;
                }
            }
        }

        if (npc->getAttitude() == NPC::AGGRESSIVE && npc->getState() == NPC::HUNTING) // the npc is either aggressive and hunting
        {
            int detector = npc->detects(m_player);
            if (detector != -1) // the npc detects player
            {
                if      ((detector == 0 || detector == 3 || detector == 5) && npc->getDirection() != NPC::LEFT ) npc->setDirection(NPC::LEFT);
                else if ((detector == 2 || detector == 4 || detector == 7) && npc->getDirection() != NPC::RIGHT) npc->setDirection(NPC::RIGHT);

                if (instanceof <Bandit, NPC> (npc)) // the npc is a bandit
                {
                    bool hit = false;
                    switch (((Bandit*) npc)->getType())
                    {
                        case Bandit::CLUB    : if (chance(MeleeWeapon(MeleeWeapon::CLUB).getAccuracy()*2, 21))
                                               {
                                                   ((Bandit*) npc)->attack(m_player);
                                                   hit = true;
                                               }
                                               break;

                        case Bandit::CROSSBOW: if (chance(RangedWeapon(RangedWeapon::CROSSBOW).getAccuracy()*2, 21))
                                               {
                                                   ((Bandit*) npc)->attack(m_player);
                                                   hit = true;
                                               }
                                               break;

                        case Bandit::DAGGER  : if (chance(MeleeWeapon(MeleeWeapon::DAGGER).getAccuracy()*2, 21))
                                               {
                                                   ((Bandit*) npc)->attack(m_player);
                                                   hit = true;
                                               }
                                               break;
                    }

                    if (hit)
                        subject.notify(Observer::NPC_ATTACK_SUCCESS, npc); // the npc hit the player
                    else
                        subject.notify(Observer::NPC_ATTACK_FAILURE, npc); // the player dodged the attack
                }
            }
            else if (FOV::seesEntity(m_level->getTiles(), npc, m_player))
            {
                npc->setDestination(m_player->getGridPosition());
            }
        }
    }

}
