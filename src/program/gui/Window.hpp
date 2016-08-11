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

    class Window : public Component {
    private: sf::RectangleShape      body_;
             Text                    header_;
             std::vector<Component*> components_;
             bool                    visible_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Window();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds a given component to the internal window.
             ////////////////////////////////////////////////////////////////////////

             void addComponent(Component*, bool attached);
             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the internal window visible or not, depending on the
             /// value of the given argument.
             ////////////////////////////////////////////////////////////////////////
             void setVisible(bool);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Method telling if the internal window is visible.
             ////////////////////////////////////////////////////////////////////////
             bool isVisible() const { return visible_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the internal window's title.
             ////////////////////////////////////////////////////////////////////////
             void setHeader(sf::String s) { header_.setString(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the internal window's title.
             ////////////////////////////////////////////////////////////////////////
             Text getHeader() const { return header_; }

             void setPosition(sf::Vector2f) override;
             void setSize(sf::Vector2f siz) override { body_.setSize(siz); }

             sf::Vector2f getSize() const override { return body_.getSize(); }
             sf::Vector2f getPosition() const override { return body_.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the internal window's component of a given type and
             /// index.
             ////////////////////////////////////////////////////////////////////////
             template<typename T>
             T* getComponent(unsigned index) const {
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

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opeartor overload allowing to add the attached components
             /// without calling the addComponent method manually.
             ///
             /// To add multiple components in one line you can just do:
             /// \code
             /// ((((window += comp_1) += comp_2) += comp_3) ...) += comp_n;
             /// \endcode
             ////////////////////////////////////////////////////////////////////////
             Window& operator+= (Component* c) {
                 addComponent(c, true);
                 return *this;
             }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opeartor overload allowing to add the unattached components
             /// without calling the addComponent method manually.
             ///
             /// To add multiple components in one line you can just do:
             /// \code
             /// ((((window |= comp_1) |= comp_2) |= comp_3) ...) |= comp_n;
             /// \endcode
             ////////////////////////////////////////////////////////////////////////
             Window& operator|= (Component* c) {
                 addComponent(c, false);
                 return *this;
             }
    };

}

#endif // GUI_WINDOW_HPP
