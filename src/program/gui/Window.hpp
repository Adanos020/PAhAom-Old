/**
 * @file src/program/gui/Window.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <vector>

#include "Component.hpp"
#include "Text.hpp"

#include "../funcs/classes.hpp"

namespace rr
{

    class Window : public Component
    {
    private: sf::RectangleShape      m_body;
             Text                    m_header;
             std::vector<Component*> m_components;
             bool                    m_visible;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Window(sf::String head = "", sf::Vector2f size = sf::Vector2f(0, 0),
                    sf::Vector2f position = sf::Vector2f(0, 0), sf::Color = sf::Color(128, 128, 128));

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
             bool isVisible() const { return m_visible; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the internal window's title.
             ////////////////////////////////////////////////////////////////////////
             void setHeader(sf::String s) { m_header.setString(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the internal window's title.
             ////////////////////////////////////////////////////////////////////////
             Text getHeader() const { return m_header; }

             void setPosition(sf::Vector2f) override;
             void setSize(sf::Vector2f siz) override { m_body.setSize(siz); }

             sf::Vector2f getSize() const override { return m_body.getSize(); }
             sf::Vector2f getPosition() const override { return m_body.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the internal window's component of a given type and
             /// index.
             ////////////////////////////////////////////////////////////////////////
             template<typename T>
             T* getComponent(unsigned index) const
             {
                 if (std::is_base_of<Component, T>::value)
                 {
                     for (unsigned i=0; i<m_components.size(); i++)
                     {
                         if (instanceof<T, Component>(m_components[i]))
                         {
                             if (  index-- == 0
                                 ) return (T*)m_components[i];
                         }
                     }
                 }
                 else
                 {
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
             Window& operator+= (Component* c)
             {
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
             Window& operator|= (Component* c)
             {
                 addComponent(c, false);
                 return *this;
             }
    };

}

#endif // GUI_WINDOW_HPP
