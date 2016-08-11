/**
 * @file src/program/game/messages/MessageManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include "../gui/Text.hpp"
#include "../observer/Observer.hpp"
#include "../game/entity/Entity.hpp"

namespace rr {

    class Message : public sf::Drawable {
    private: Text     message_;
             sf::Time timeElapsed_;
             sf::Time lifeTime_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the message on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Message(sf::String, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Style::Regular);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the message's position on the screen.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the lifetime counter of the message.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Time);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the message's position on the screen.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getPosition() const { return message_.getPosition (); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the message's size.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getSize() const { return message_.getSize(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the message's text's fill color.
             ////////////////////////////////////////////////////////////////////////
             sf::Color getColor() const { return message_.getFillColor(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the message's string.
             ////////////////////////////////////////////////////////////////////////
             sf::String getString() const { return message_.getString(); }
    };

    class MessageManager : public Observer {
    private: std::vector<Message> messages_;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Adds the message to the list.
             ////////////////////////////////////////////////////////////////////////
             void addMessage(Message);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the state of the massages stored in the list.
             ///
             /// If a message's life time expires, then it is deleted.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Time);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the messages on the screen.
             ////////////////////////////////////////////////////////////////////////
             void draw(sf::RenderWindow&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reacts to a specific event. It can either do something with
             /// a given entity or just ignore it.
             ////////////////////////////////////////////////////////////////////////
             virtual void onNotify(Event, Entity*) override;
    };

}

#endif // MESSAGEMANAGER_HPP
