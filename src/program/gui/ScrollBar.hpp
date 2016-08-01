/**
 * @file src/program/gui/ScrollBar.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_SCROLLBAR_HPP
#define GUI_SCROLLBAR_HPP

#include "Component.hpp"
#include "Button.hpp"
#include "Text.hpp"

namespace rr {

/// Class for a ScrollBar component
    class ScrollBar : public Component {
    private: sf::RectangleShape border_;
             sf::Vector2f       valueLimit_;
             Button             indicator_;
             Button             bLeft_;
             Button             bRight_;
             Text               label_;
             float              value_;

             virtual void draw        (sf::RenderTarget&,
                                       sf::RenderStates) const override;

    public:  enum Plain {
                 HORIZONTAL,
                 VERTICAL
             } plain_;

             ScrollBar(Plain, sf::Vector2f position, float length, sf::Vector2f min_max = sf::Vector2f(0, 100));
             
             void         setPosition (sf::Vector2f)           override;
             void         setSize     (sf::Vector2f)           override;
             void         setText     (sf::String s)                    { label_.setString(s); }

         /// Sets the actual value of the scroll bar
             void         setValue    (int);
             void         buttonEvents(sf::RenderWindow&, sf::Event&);
         
             sf::Vector2f getPosition ()                 const override { return bLeft_.getPosition(); }
             sf::Vector2f getSize     ()                 const override { return border_.getSize(); }
             Text         getText     ()                 const          { return label_; }

         /// Returns the actual value of the scroll bar
             int          getValue    ()                 const          { return value_; }
    };

}

#endif // GUI_SCROLLBAR_HPP
