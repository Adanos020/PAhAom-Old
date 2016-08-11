/**
 * @file src/program/gui/Bar.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_BAR_HPP
#define GUI_BAR_HPP

#include "Component.hpp"

namespace rr {

    class Bar : public Component {
    private: sf::RectangleShape border_;
             sf::RectangleShape bar_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the bar on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    public:  enum Plain {
                 HORIZONTAL,
                 VERTICAL
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ///
             /// \param plain the plain in which the bar is situated; the possible
             /// values are:
             /// - HORIZONTAL
             /// - VERTICAL
             /// \param color the color of the bar, not the border
             ////////////////////////////////////////////////////////////////////////
             Bar(Plain, int max_length, sf::Color, sf::Vector2f pos);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the bar's body's position.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the bar's body's position.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getPosition() const override { return border_.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the bar's body's size.
             ////////////////////////////////////////////////////////////////////////
             void setSize(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the bar's body's size.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getSize() const override { return border_.getSize(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the bar's display value.
             ////////////////////////////////////////////////////////////////////////
             void setValue(sf::Vector2f);
    };

}

#endif // GUI_BAR_HPP
