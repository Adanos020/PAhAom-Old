/**
 * @file src/program/game/ui/Conversation.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_CONVERSATION_HPP
#define UI_CONVERSATION_HPP

#include "../../gui/Window.hpp"

#include "../entity/npc/NPC.hpp"
#include "../entity/Player.hpp"

#include "../dialogue/Dialogue.hpp"

namespace rr
{

    class Game;

    class Conversation : public sf::Drawable
    {
    private: sf::RectangleShape shadow_;
             sf::String         npcName_;
             Window             wConv_;
             Window             wOpts_;
             DialogueTree*      dialogue_;
             Player*            player_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Conversation(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the conversation window.
             ////////////////////////////////////////////////////////////////////////
             void open(NPC*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the conversation window and unpauses the game.
             ////////////////////////////////////////////////////////////////////////
             void close(Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the conversation window is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return wConv_.isVisible() || wOpts_.isVisible(); }
    };

}

#include "../Game.hpp"

#endif // UI_CONVERSATION_HPP
