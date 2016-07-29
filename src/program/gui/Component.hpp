/**
 * @file src/program/gui/Component.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace rr {

/// Abstract class for all the GUI components
    class Component {
    private: Component* parentComponent_;
    
    public:  virtual ~Component() {}

         /// Method drawing the component on the screen
             virtual void         draw               (sf::RenderWindow&)  = 0;
         /// Sets the component's body's position
             virtual void         setPosition        (sf::Vector2f)       = 0;
         /// Sets the component's body's size
             virtual void         setSize            (sf::Vector2f)       = 0;
         /// Returns the component's body's position
             virtual sf::Vector2f getPosition        ()             const = 0;
         /// Returns the component's body's size
             virtual sf::Vector2f getSize            ()             const = 0;
         /// Sets the component's parent component
             void                 setParentComponent (Component* p)       { parentComponent_ = p; }
         /// Returns the component's parent component
             Component*           getParentComponent ()             const { return parentComponent_; }
    };

}

#endif // GUI_COMPONENT_HPP
