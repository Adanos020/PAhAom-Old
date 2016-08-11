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

    class ScrollBar : public Component {
    private: sf::RectangleShape border_;
             sf::Vector2f       valueLimit_;
             Button             indicator_;
             Button             bLeft_;
             Button             bRight_;
             Text               label_;
             float              value_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the scroll bar on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  enum Plain {
                 HORIZONTAL,
                 VERTICAL
             } plain_;

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
     virtual sf::Vector2f getPosition () const override { return bLeft_.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the scroll bar's body's size.
             ////////////////////////////////////////////////////////////////////////
     virtual void setSize(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the scroll bar's body's size.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getSize() const override { return border_.getSize(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the string of the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             void setText(sf::String s) { label_.setString(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             Text getText() const { return label_; }

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
             int getValue() const { return value_; }
    };

}

#endif // GUI_SCROLLBAR_HPP
