/**
 * @file src/program/game/entity/npc/state/NPCHunting.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCHunting.hpp"

#include "../../../FOV.hpp"

extern rr::Subject subject;

namespace rr
{

    NPCState*
    NPCHunting::update(sf::Time& delta, NPC* npc)
    {
        return nullptr;
    }

    NPCState*
    NPCHunting::react(Level* level, NPC* npc, Player& player)
    {
        int detector = npc->detects(&player);
        if (detector >= 0) // the npc detects player
        {
            if ((detector == 0 || detector == 3 || detector == 5)
              && npc->getDirection() != NPC::LEFT) npc->setDirection(NPC::RIGHT);
            
            else if ((detector == 2 || detector == 4 || detector == 7)
              && npc->getDirection() != NPC::RIGHT) npc->setDirection(NPC::LEFT);

            if (instanceof <Bandit, NPC> (npc)) // the npc is a bandit
            {
                bool hit = false;
                switch (((Bandit*) npc)->getType())
                {
                    case Bandit::CLUB:
                    {
                        if (chance(MeleeWeapon(MeleeWeapon::CLUB).getAccuracy()*2, 21))
                        {
                            ((Bandit*) npc)->attack(&player);
                            hit = true;
                        }
                    }
                    break;

                    case Bandit::CROSSBOW:
                    {
                        if (chance(RangedWeapon(RangedWeapon::CROSSBOW).getAccuracy()*2, 21))
                        {
                            ((Bandit*) npc)->attack(&player);
                            hit = true;
                        }
                    }
                    break;

                    case Bandit::DAGGER:
                    {
                        if (chance(MeleeWeapon(MeleeWeapon::DAGGER).getAccuracy()*2, 21))
                        {
                            ((Bandit*) npc)->attack(&player);
                            hit = true;
                        }
                    }
                    break;
                }

                if (hit) subject.notify(Observer::NPC_ATTACK_SUCCESS, npc); // the npc hit the player
                else     subject.notify(Observer::NPC_ATTACK_FAILURE, npc); // the player dodged the attack

                return &attacking;
            }
        }
        else if (FOV::seesEntity(level->getTiles(), npc, &player))
        {
            npc->setDestination(player.getGridPosition());
        }
        return nullptr;
    }

}