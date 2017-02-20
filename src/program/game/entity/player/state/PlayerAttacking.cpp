/**
 * @file src/program/game/entity/player/state/PlayerAttacking.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../PlayerAttacking.hpp"

#include "../../../../funcs/keys.hpp"
#include "../../../../Settings.hpp"

namespace rr
{

    PlayerState*
    PlayerAttacking::update(sf::Time&, Player& player)
    {
        if (player.m_body.isPlaying())
            return nullptr;

        return &standing;
    }

    PlayerState*
    PlayerAttacking::handleInput(sf::Event&, Player&)
    { return nullptr; }

}
