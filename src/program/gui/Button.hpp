/**
 * @file src/program/gui/Button.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include "Component.hpp"
#include "Image.hpp"
#include "Text.hpp"

namespace rr {

/// Class for a button component which by being clicked can cause any action you assign to it
    class Button : public Component {
    private: sf::RectangleShape body_;
             Image              image_;
             Text               text_;
             bool               held_;
    
    public:  Button(sf::Vector2f position, sf::String, unsigned chsize, sf::Color = sf::Color::White);
            ~Button();
        
             bool         containsMouseCursor(sf::RenderWindow&);
             bool         isPressed          (sf::RenderWindow&, sf::Event&);
             bool         isHeld             () const                     { return held_; }
             Text         getText            () const                     { return text_; }
             sf::Vector2f getPosition        () const            override { return body_.getPosition(); }
             sf::Vector2f getSize            () const            override { return body_.getSize(); }
             void         setPosition        (sf::Vector2f)      override;
             void         draw               (sf::RenderWindow&) override;
         
             void         setSize            (sf::Vector2f)      override {}
    };

}

#endif
