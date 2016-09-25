/**
 * @file src/program/game/entity/player/state/PlayerStanding.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../PlayerStanding.hpp"

#include "../../../../funcs/keys.hpp"
#include "../../../../Settings.hpp"

namespace rr
{

    PlayerState*
    PlayerStanding::update(sf::Time& delta, Player& player)
    {
        if (player.m_currentAnimation == &player.m_walkingLeft)
            player.m_currentAnimation = &player.m_standingLeft;

        else if (player.m_currentAnimation == &player.m_walkingRight)
            player.m_currentAnimation = &player.m_standingRight;

        return nullptr;
    }

    PlayerState*
    PlayerStanding::handleInput(sf::Event& event, Player& player)
    {
        if (isKeyPressed(Settings::keys.move_up))
        {
            if (player.move(Player::UP))
                return &moving;
        }
        if (isKeyPressed(Settings::keys.move_down))
        {
            if (player.move(Player::DOWN))
                return &moving;
        }
        if (isKeyPressed(Settings::keys.move_left))
        {
            if (player.move(Player::LEFT))
                return &moving;
        }
        if (isKeyPressed(Settings::keys.move_right))
        {
            if (player.move(Player::RIGHT))
                return &moving;
        }
        if (wasKeyPressed(event, Settings::keys.attack))
        {
            player.m_body.setLooped(false);
            return &attacking;
        }
        return nullptr;
    }

}
