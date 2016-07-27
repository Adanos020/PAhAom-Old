/**
 * @file src/program/gui/Text.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_TEXT_HPP
#define GUI_TEXT_HPP

#include "Component.hpp"

namespace rr {

/// A class for a text component
    class Text : public Component {
    private: sf::Text text_;
    
    public:  Text(                       sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Bold);
             Text(sf::Vector2f position, sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Bold);
        
             void            setPosition     (sf::Vector2f)      override;
         
         /// Wraps the text
             void            wrap            (float width);
         /// Sets the text's character size
             void            setCharacterSize(unsigned c)                 { text_.setCharacterSize(c); }
         /// Sets the text's color
             void            setColor        (sf::Color c)                { text_.setColor(c); }
         /// Sets the text's string
             void            setString       (sf::String s)               { text_.setString(s); }
         /// Sets the text's font
             void            setFont         (sf::Font f)                 { text_.setFont(f); }
         /// Sets the text's style
             void            setStyle        (sf::Text::Style s)          { text_.setStyle(s); }
         
             void            draw            (sf::RenderWindow&) override;
             void            setSize         (sf::Vector2f)      override {}
         
             sf::Vector2f    getSize         () const            override { return sf::Vector2f(text_.getGlobalBounds().width, text_.getGlobalBounds().height); }
             sf::Vector2f    getPosition     () const            override { return text_.getPosition(); }
         
         /// Returns the text's character size
             int             getCharacterSize() const                     { return text_.getCharacterSize(); }
         /// Returns the text's color
             sf::Color       getColor        () const                     { return text_.getColor(); }
         /// Returns the text's string
             sf::String      getString       () const                     { return text_.getString(); }
         /// Returns the text style
             sf::Text::Style getStyle        () const                     { return (sf::Text::Style)text_.getStyle(); }
    };

}

#endif