/**
 * @file src/program/game/entity/npc/state/NPCHunting.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../NPCHunting.hpp"

#include "../../../FOV.hpp"
#include "../../../PathFinder.hpp"

extern rr::Subject subject;

namespace rr
{

    NPCState*
    NPCHunting::update(sf::Time& delta, NPC* npc)
    {
        return nullptr;
    }

    NPCState*
    NPCHunting::react(Level* level, NPC* npc, Player* player)
    {
        if (npc->getAttitude() == NPC::HOSTILE)
        {
            int detector = npc->detects(player);
            if (detector >= 0) // the npc detects player
            {
                if ((detector == 0 || detector == 3 || detector == 5)
                    && npc->getDirection() != NPC::LEFT) npc->setDirection(NPC::RIGHT);
                
                else if ((detector == 2 || detector == 4 || detector == 7)
                    && npc->getDirection() != NPC::RIGHT) npc->setDirection(NPC::LEFT);

                bool hit = false;
                if (instanceof <Bandit, NPC> (npc))
                {
                    switch (((Bandit*) npc)->getType())
                    {
                        case Bandit::CLUB:
                        {
                            if (chance(MeleeWeapon(MeleeWeapon::CLUB).getAccuracy()*2, 21))
                            {
                                ((Bandit*) npc)->attack(player);
                                hit = true;
                            }
                        }
                        break;

                        case Bandit::CROSSBOW:
                        {
                            if (chance(RangedWeapon(RangedWeapon::CROSSBOW).getAccuracy()*2, 21))
                            {
                                ((Bandit*) npc)->attack(player);
                                hit = true;
                            }
                        }
                        break;

                        case Bandit::DAGGER:
                        {
                            if (chance(MeleeWeapon(MeleeWeapon::DAGGER).getAccuracy()*2, 21))
                            {
                                ((Bandit*) npc)->attack(player);
                                hit = true;
                            }
                        }
                        break;
                    }
                }

                if (hit) subject.notify(Observer::NPC_ATTACK_SUCCESS, npc); // the npc hit the player
                else     subject.notify(Observer::NPC_ATTACK_FAILURE, npc); // the player dodged the attack

                if (npc->getDirection() == NPC::LEFT)
                {
                    npc->m_currentAnimation = &npc->m_attackingLeft;
                }
                else
                {
                    npc->m_currentAnimation = &npc->m_attackingRight;
                }
                npc->m_body.setLooped(false);

                return &attacking;
            }
            else if (npc->m_stepsToFollow > 0 || FOV::seesEntity(*level, npc, player))
            {
                npc->setDestination(player->getGridPosition());
                npc->m_stepsToFollow = 10;
            }
        }

        std::vector <sf::Vector2i> path;
        while (true)
        {
            if (level->getTilesAsCells()[npc->getDestination().x + npc->getDestination().y*level->getSize().x] == Level::ROOM
                || level->getTilesAsCells()[npc->getDestination().x + npc->getDestination().y*level->getSize().x] == Level::ENTRANCE)
            {
                path = PathFinder::aStar(npc->getDestination(), npc->getGridPosition(), level->getTiles());

                // we don't want any destination to which there is no actual path
                if (!path.empty())
                    break;
            }
            npc->setDestination(sf::Vector2i(rand()%level->getSize().x, rand()%level->getSize().y));
        }

        if (npc->getGridPosition() != npc->getDestination()
            || (npc->getAttitude() == NPC::HOSTILE && npc->detects(player) < 0))
        {
            auto offset = path[1] - npc->getGridPosition();

            if      (offset == sf::Vector2i( 0, -1)) npc->move(level->getTiles(), NPC::UP);
            else if (offset == sf::Vector2i( 0,  1)) npc->move(level->getTiles(), NPC::DOWN);
            else if (offset == sf::Vector2i(-1,  0)) npc->move(level->getTiles(), NPC::LEFT);
            else if (offset == sf::Vector2i( 1,  0)) npc->move(level->getTiles(), NPC::RIGHT);

            else if (offset == sf::Vector2i(-1, -1)) npc->move(level->getTiles(), NPC::UPLEFT);
            else if (offset == sf::Vector2i( 1, -1)) npc->move(level->getTiles(), NPC::UPRIGHT);
            else if (offset == sf::Vector2i(-1,  1)) npc->move(level->getTiles(), NPC::DOWNLEFT);
            else if (offset == sf::Vector2i( 1,  1)) npc->move(level->getTiles(), NPC::DOWNRIGHT);

            --npc->m_stepsToFollow;
            //std::cout << npc->m_stepsToFollow << '\n';

            return &moving;
        }

        return nullptr;
    }

}