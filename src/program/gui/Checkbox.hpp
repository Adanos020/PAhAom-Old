/**
 * @file src/program/gui/Checkbox.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_CHECKBOX_HPP
#define GUI_CHECKBOX_HPP

#include "Component.hpp"
#include "Image.hpp"
#include "Text.hpp"

namespace rr {

/// Class for a checkbox component which can be checked or unchecked, depending on the parity of the number of clicks performed on it
    class Checkbox : public Component {
    private: sf::RectangleShape body_;
             Image              image_;
             Text               text_;
             bool               checked_;
             bool               held_;
    
    public:  Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
            ~Checkbox();
        
         /// Sets the checkbox checked or not, depending on the value of the given argument
             void         check              (bool b);
         
             void         draw               (sf::RenderWindow& rw) override;
             void         setPosition        (sf::Vector2f)         override;
         
             bool         containsMouseCursor(sf::RenderWindow&);
             bool         isPressed          (sf::RenderWindow&, sf::Event&);
             sf::Vector2f getPosition        () const               override { return body_.getPosition(); }
             sf::Vector2f getSize            () const               override { return body_.getSize(); }
         
         /// Method telling if the checkbox is checked
             bool         isChecked          () const                        { return checked_; }
         
             Text         getText            () const                        { return text_; }
         
             void         setSize            (sf::Vector2f)         override {}
    };

}

#endif
