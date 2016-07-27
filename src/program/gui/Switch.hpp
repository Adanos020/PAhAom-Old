/**
 * @file src/program/gui/Switch.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_SWITCH_HPP
#define GUI_SWITCH_HPP

#include "Component.hpp"
#include "Button.hpp"
#include "Text.hpp"

namespace rr {

/// Class for a switch component which can contain as many options you add to it and switch between them
    class Switch : public Component {
    private: sf::RectangleShape      body_;
             std::vector<sf::String> options_;
             Button                  left_;
             Button                  right_;
             Text                    text_;
             mutable unsigned        counter_;
    
    public:  Switch(sf::Vector2f size, sf::Vector2f position);
        
             void                 setPosition        (sf::Vector2f)      override;
             void                 setSize            (sf::Vector2f)      override;
         
         /// Method for handling the button events
             void                 buttonEvents       (sf::RenderWindow&, sf::Event&);
         /// Adds an option to the switch
             void                 addOption          (sf::String);
         /// Sets the current option
             void                 setCurrentOption   (sf::String);
         
             void                 draw               (sf::RenderWindow&) override;
         
         /// Returns the current option
             sf::String           getCurrentOption   () const                     { return options_[counter_]; }
             virtual sf::Vector2f getPosition        () const            override { return left_.getPosition(); }
             virtual sf::Vector2f getSize            () const            override { return body_.getSize(); }
         
             Text                 getText            () const                     { return text_; }
    };

}

#endif
