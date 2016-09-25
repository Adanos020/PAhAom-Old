/**
 * @file src/program/game/entity/player/PlayerMoving.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef PLAYER_STATE_MOVING_HPP
#define PLAYER_STATE_MOVING_HPP

#include "PlayerState.hpp"

namespace rr
{

    class PlayerMoving : public PlayerState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the moving state.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* update(sf::Time&, Player&) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Handles the input.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* handleInput(sf::Event&, Player&) override;
    };

}

#endif // PLAYER_STATE_MOVING_HPP
