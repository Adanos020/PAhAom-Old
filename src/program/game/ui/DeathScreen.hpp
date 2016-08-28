/**
 * @file src/program/game/ui/DeathScreen.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_DEATHSCREEN_HPP
#define UI_DEATHSCREEN_HPP

#include "../../gui/Text.hpp"
#include "../../gui/Button.hpp"

namespace rr
{

    class Game;

    class DeathScreen : public sf::Drawable
    {
    private: sf::RectangleShape shadow_;
             sf::Time           endAnimation_;

             Text               tYouDied_;
             Button             bNewGame_;
             Button             bQuit_;

             bool               visible_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             DeathScreen();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the screen of death.
             ////////////////////////////////////////////////////////////////////////
             void open() { visible_ = true; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the screen of death.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() { return visible_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the screen of death's state.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Clock&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the screen of death's components.
             ////////////////////////////////////////////////////////////////////////
             void reset();
    };

}

#include "../Game.hpp"

#endif // UI_DEATHSCREEN_HPP
