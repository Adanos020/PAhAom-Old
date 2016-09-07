/**
 * @file src/program/gui/ScrollBar.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef GUI_SCROLLBAR_HPP
#define GUI_SCROLLBAR_HPP

#include "Component.hpp"
#include "Button.hpp"
#include "Text.hpp"

namespace rr
{

    class ScrollBar : public Component
    {
    private: sf::RectangleShape m_border;
             sf::Vector2f       m_valueLimit;
             Button             m_indicator;
             Button             m_bLeft;
             Button             m_bRight;
             Text               m_label;
             float              m_value;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the scroll bar on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  enum Plain
             {
                 HORIZONTAL,
                 VERTICAL
             } m_plain;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ///
             /// \param plain the plain in which the scroll bar is situated; the
             /// possible values are:
             /// - HORIZONTAL
             /// - VERTICAL
             ////////////////////////////////////////////////////////////////////////
             ScrollBar(Plain, sf::Vector2f position, float length, sf::Vector2f min_max = sf::Vector2f(0, 100));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the scroll bar's body's position.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the scroll bar's body's position.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition () const override { return m_bLeft.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the scroll bar's body's size.
             ////////////////////////////////////////////////////////////////////////
     virtual void setSize(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the scroll bar's body's size.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getSize() const override { return m_border.getSize(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the string of the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             void setText(sf::String s) { m_label.setString(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             Text getText() const { return m_label; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the actual value of the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             void setValue(int);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the actual value of the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             int getValue() const { return m_value; }
    };

}

#endif // GUI_SCROLLBAR_HPP
