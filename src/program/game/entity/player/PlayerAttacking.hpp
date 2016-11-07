/**
 * @file src/program/game/entity/player/PlayerAttacking.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "PlayerState.hpp"

namespace rr
{

    class PlayerAttacking : public PlayerState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the attacking state.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* update(sf::Time&, Player&) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Handles the input.
                ////////////////////////////////////////////////////////////////////////
        virtual PlayerState* handleInput(sf::Event&, Player&) override;
    };

}
