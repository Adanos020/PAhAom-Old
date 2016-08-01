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
             
             virtual void         draw               (sf::RenderTarget&,
                                                      sf::RenderStates) const override;

    public:  Button(sf::Vector2f position, sf::String, unsigned chsize, sf::Color = sf::Color::White);

             void                 setText            (sf::String);
        
             bool                 containsMouseCursor(sf::RenderWindow&);
             bool                 isPressed          (sf::RenderWindow&, sf::Event&);
             bool                 isHeld             ()                 const          { return held_; }
             Text                 getText            ()                 const          { return text_; }

             virtual sf::Vector2f getPosition        ()                 const override { return body_.getPosition(); }
             virtual sf::Vector2f getSize            ()                 const override { return body_.getSize(); }
             virtual void         setPosition        (sf::Vector2f)           override;
             virtual void         setSize            (sf::Vector2f size)      override { body_.setSize(size); }
    };

}

#endif // GUI_BUTTON_HPP
