/**
 * @file src/program/game/entity/player/PlayerStanding.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef PLAYER_STATE_STANDING_HPP
#define PLAYER_STATE_STANDING_HPP

#include "PlayerState.hpp"

namespace rr
{

    class PlayerStanding : public PlayerState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the standing state.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* update(sf::Time&, Player&) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Handles the input.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* handleInput(sf::Event&, Player&) override;
    };

}

#endif // PLAYER_STATE_STANDING_HPP
