/**
 * @file src/program/game/messages/messages.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef messages_hpp
#define messages_hpp

#include "../gui/gui.hpp"
#include "../observer/observer.hpp"
#include "../game/entities/entities.hpp"

namespace rr {

/// Class for a message
    class Message {
    private: Text     message_;
             sf::Time timeElapsed_;
             sf::Time lifeTime_;
    
    public:  Message(sf::String, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Style::Regular);

         /// Sets the message's position on the screen
             void         setPosition(sf::Vector2f);
         /// Updates the lifetime counter of the message
             void         update     (sf::Time);
         /// Draws the message on the screen
             void         draw       (sf::RenderWindow&);
         
             sf::Vector2f getPosition() const { return message_.getPosition(); }
             sf::Vector2f getSize    () const { return message_.getSize    (); }
             sf::Color    getColor   () const { return message_.getColor   (); }
             sf::String   getString  () const { return message_.getString  (); }
    };

/// Class for the message manager implementing the Observer interface
    class MessageManager : public Observer {
    private: std::vector<Message> messages_;
    
    public:  MessageManager();

             void         addMessage(Message);
             void         update    (sf::Time);
             void         draw      (sf::RenderWindow&);
         
             virtual void onNotify  (Event, Entity*) override;
    };

}

#endif // messages_hpp
