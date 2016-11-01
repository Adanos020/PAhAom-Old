/**
 * @file src/program/gui/Separator.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef GUI_SEPARATOR_HPP
#define GUI_SEPARATOR_HPP

#include "Component.hpp"

namespace rr
{

    class Separator : public Component
    {
        private: float           m_length;
                 sf::VertexArray m_vertices;

         virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

        public:  enum Plain
                 {
                     HORIZONTAL,
                     VERTICAL
                 };
                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Regular constructor.
                 ////////////////////////////////////////////////////////////////////////
                 Separator(Plain, float length = 0);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Sets the separator's length.
                 ////////////////////////////////////////////////////////////////////////
                 void setLength(float);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Returns the separator's length.
                 ////////////////////////////////////////////////////////////////////////
                 float getLength() const;
                
                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Sets the separator's color.
                 ////////////////////////////////////////////////////////////////////////
                 void setColor(sf::Color);
                
                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Returns the separator's color.
                 ////////////////////////////////////////////////////////////////////////
                 sf::Color getColor() const;

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Sets the separator's position.
                 ////////////////////////////////////////////////////////////////////////
         virtual void setPosition(sf::Vector2f) override;
                 
                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Returns the separator's position.
                 ////////////////////////////////////////////////////////////////////////
         virtual sf::Vector2f getPosition() const override;

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Doesn't do anything. Use setLength() instead.
                 ////////////////////////////////////////////////////////////////////////
         virtual void setSize(sf::Vector2f) override {}
                 
                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Returns the separator's size.
                 ////////////////////////////////////////////////////////////////////////
         virtual sf::Vector2f getSize() const override;

        private: Plain m_plain;
    };

}

#endif // GUI_SEPARATOR_HPP
