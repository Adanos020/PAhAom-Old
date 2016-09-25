/**
 * @file src/program/game/entity/player/PlayerState.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <SFML/Graphics.hpp>

namespace rr
{

    class Player;

    class PlayerStanding;
    class PlayerMoving;
    class PlayerAttacking;

    class PlayerState
    {
        public:
         static PlayerStanding  standing;
         static PlayerMoving    moving;
         static PlayerAttacking attacking;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Virtual destructor.
                ////////////////////////////////////////////////////////////////////////
        virtual ~PlayerState() {}

                ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* update(sf::Time&, Player&) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Handles the input.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* handleInput(sf::Event&, Player&) = 0;
    };

}

#include "PlayerStanding.hpp"
#include "PlayerMoving.hpp"
#include "PlayerAttacking.hpp"

#include "../Player.hpp"

#endif
