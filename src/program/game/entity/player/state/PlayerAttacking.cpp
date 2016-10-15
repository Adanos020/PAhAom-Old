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
    PlayerAttacking::update(sf::Time& delta, Player& player)
    {
        player.m_body.update(delta);
        if (player.m_body.isPlaying())
            return nullptr;

        return &standing;
    }

    PlayerState*
    PlayerAttacking::handleInput(sf::Event& event, Player& player)
    {
        return nullptr;
    }

}
