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
    public:  enum Plain {
                 HORIZONTAL,
                 VERTICAL
             } plain_;
    
    private: sf::RectangleShape border_;
             sf::Vector2f       valueLimit_;
             Button             indicator_;
             Button             bLeft_;
             Button             bRight_;
             Text               label_;
             float              value_;
    
    public:  ScrollBar(Plain, sf::Vector2f position, float length, sf::Vector2f min_max = sf::Vector2f(0, 100));
            ~ScrollBar();
             
             void         setPosition (sf::Vector2f)            override;
             void         setSize     (sf::Vector2f)            override;
         
         /// Sets the actual value of the scroll bar
             void         setValue    (int);
             void         draw        (sf::RenderWindow&)       override;
             void         buttonEvents(sf::RenderWindow&, sf::Event&);
         
             sf::Vector2f getPosition ()                  const override { return bLeft_.getPosition(); }
             sf::Vector2f getSize     ()                  const override { return border_.getSize(); }
             Text         getText     ()                  const          { return label_; }
         
         /// Returns the actual value of the scroll bar
             int          getValue    ()                  const          { return value_; }
    };

}

#endif
