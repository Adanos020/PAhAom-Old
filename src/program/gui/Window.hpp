/**
 * @file src/program/gui/Window.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <vector>

#include "Component.hpp"
#include "Text.hpp"

#include "../funcs/classes.hpp"

namespace rr {

/// Class for an internal window component which also can be a component of another internal window component
    class Window : public Component {
    private: sf::RectangleShape      body_;
             Text                    header_;
             std::vector<Component*> components_;
             bool                    visible_;

             virtual void draw        (sf::RenderTarget&,
                                       sf::RenderStates) const override;

    public:  Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
            ~Window();
     
         /// Adds a given component to the internal window
             void         addComponent(Component*, bool attached);
         /// Sets the internal window visible or not, depending on the value of the given argument
             void         setVisible  (bool);
         /// Sets the internal window's title
             void         setTitle    (sf::String title)              { header_.setString(title); }

             void         setPosition (sf::Vector2f)         override;
             void         setSize     (sf::Vector2f siz)     override { body_.setSize(siz); }

         /// Method telling if the internal window is visible
             bool         isVisible   ()               const          { return visible_; }

             void         setHeader   (sf::String s)                  { header_.setString(s); }
             sf::Vector2f getSize     ()               const override { return body_.getSize(); }
             sf::Vector2f getPosition ()               const override { return body_.getPosition(); }

         /// Returns the internal window's component of a given type and index

             template<typename T> T* getComponent(unsigned index) const {
                 if (std::is_base_of<Component, T>::value) {
                     for (unsigned i=0; i<components_.size(); i++) {
                         if (instanceof<T, Component>(components_[i])) {
                             if (  index-- == 0
                                 ) return (T*)components_[i];
                         }
                     }
                 }
                 else {
                     puts("element of given type not found");
                     return nullptr;
                 }
                 puts("element with a given index not found");
                 return nullptr;
             }

             Text         getHeader   ()               const          { return header_; }

         /// Opeartor overload allowing to add the attached components without calling the addComponent method manually
             Window&      operator+=  (Component* c)                  { addComponent(c, true);
                                                                        return *this;
                                                                      }
    };

}

#endif // GUI_WINDOW_HPP
