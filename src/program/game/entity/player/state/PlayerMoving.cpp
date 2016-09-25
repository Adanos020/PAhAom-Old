/**
 * @file src/program/game/entity/player/state/PlayerMoving.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <cmath>

#include "../PlayerMoving.hpp"
#include "../../../../Observer.hpp"

extern rr::Subject subject;

namespace rr
{

    PlayerState*
    PlayerMoving::update(sf::Time& delta, Player& player)
    {
        sf::Vector2f offset = player.m_body.getPosition() - (sf::Vector2f) player.m_position*80.f;
        if (offset != sf::Vector2f(0, 0))
        {
            auto displacement = player.m_velocity*delta.asSeconds();
            if (offset.x < 0 && displacement-2 >= offset.x) player.m_body.move(sf::Vector2f( displacement,  0));
            if (offset.x > 0 && displacement-2 <= offset.x) player.m_body.move(sf::Vector2f(-displacement,  0));
            if (offset.y < 0 && displacement-2 >= offset.y) player.m_body.move(sf::Vector2f( 0,  displacement));
            if (offset.y > 0 && displacement-2 <= offset.y) player.m_body.move(sf::Vector2f( 0, -displacement));

            if (  (fabs(offset.x) < player.m_velocity/80 && fabs(offset.x) > 0) // preventing the player from wobbling
               || (fabs(offset.y) < player.m_velocity/80 && fabs(offset.y) > 0) // in between of two cells
                )  player.m_body.setPosition((sf::Vector2f) player.m_position*80.f);

            return &moving;
        }
        player.m_buffs.speed        -= (player.m_buffs.speed        == 0 ? 0 : 1);
        player.m_buffs.regeneration -= (player.m_buffs.regeneration == 0 ? 0 : 1);
        player.m_buffs.poison       -= (player.m_buffs.poison       == 0 ? 0 : 1);
        player.m_buffs.slowness     -= (player.m_buffs.slowness     == 0 ? 0 : 1);
        player.m_buffs.weakness     -= (player.m_buffs.weakness     == 0 ? 0 : 1);
        player.m_buffs.hunger       ++;

        if (player.m_buffs.hunger ==  500) subject.notify(Observer::PLAYER_HUNGRY  , nullptr);
        if (player.m_buffs.hunger == 1000) subject.notify(Observer::PLAYER_STARVING, nullptr);

        if (player.m_attrs.mana_regeneration)
            player.m_attrs.mana += 0.1;

        if      (player.m_buffs.hunger <   500) player.m_attrs.health += (player.m_attrs.health_regeneration ? 0.1f : 0.05f);
        else if (player.m_buffs.hunger <  1000) player.m_attrs.health += (player.m_attrs.health_regeneration ? 0.05f : 0.f);
        else if (player.m_buffs.hunger >= 1000) player.m_attrs.health -= (player.m_attrs.health_regeneration ? 0.f : 0.05f);

        if (player.m_buffs.poison > 0)
            player.m_attrs.health -= 1.f;

        if (player.m_buffs.regeneration > 0)
            player.m_attrs.health += 0.15f;

        return &standing;
    }

    PlayerState*
    PlayerMoving::handleInput(sf::Event& event, Player& player)
    {
        return nullptr;
    }

}
