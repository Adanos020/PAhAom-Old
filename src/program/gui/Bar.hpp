/**
 * @file src/program/gui/Bar.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_BAR_HPP
#define GUI_BAR_HPP

#include "Component.hpp"

namespace rr {

/// Class for a vertical or a horizontal bar component representing any value you assign it to
    class Bar : public Component {
    private: sf::RectangleShape border_;
             sf::RectangleShape bar_;
    public:  
             enum Plain {
                 HORIZONTAL,
                 VERTICAL
             };
             Bar(Plain, int max_length, sf::Color, sf::Vector2f pos);
         
             void         setPosition        (sf::Vector2f)      override;
             void         setSize            (sf::Vector2f)      override;
             void         setValue           (sf::Vector2f);
             void         draw               (sf::RenderWindow&) override;
         
             sf::Vector2f getPosition        () const            override { return border_.getPosition(); }
             sf::Vector2f getSize            () const            override { return border_.getSize(); }
    };

}

#endif
