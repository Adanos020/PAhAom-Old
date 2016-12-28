/**
 * @file src/program/game/ui/Conversation.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "../../gui/Window.hpp"

#include "../Dialogue.hpp"

namespace rr
{

    class Game;
    class Teacher;
    class Player;

    class Conversation : public sf::Drawable
    {
    private: sf::RectangleShape    m_shadow;
             sf::String            m_teacherName;
             Window                m_wConv;
             Window                m_wOpts;
             DialogueTree*         m_dialogue;
             Player*               m_player;
             Teacher*              m_teacher;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Conversation(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the interface.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the conversation window.
             ////////////////////////////////////////////////////////////////////////
             void open(Teacher*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the conversation window and unpauses the game.
             ////////////////////////////////////////////////////////////////////////
             void close(Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the conversation window is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return m_wConv.isVisible() || m_wOpts.isVisible(); }
    };

}

#include "../../Game.hpp"

#include "../entity/npc/Teacher.hpp"
#include "../entity/Player.hpp"
