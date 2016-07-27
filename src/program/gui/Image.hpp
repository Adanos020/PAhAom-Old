/**
 * @file src/program/gui/Image.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include "Component.hpp"

namespace rr {

/// Class for an image component which can be loaded from a file
    class Image : public Component {
    private: sf::Sprite body_;
             int        icon_;
    
    public:  Image(sf::Vector2f position, sf::Texture&, int iconSize, unsigned index);
        
             void          setPosition (sf::Vector2f)      override;
             void          setSize     (sf::Vector2f)      override;
         
         /// Changes the icon index
             void          setIconIndex(unsigned index);
         /// Changes the texture
             void          setTexture  (sf::Texture&);
         /// Method scaling the body's size
             void          scale       (sf::Vector2f);
         /// Method painting the body to a given color
             void          paint       (sf::Color);
         
             void          draw        (sf::RenderWindow&) override;
         
         /// Returns the image's body
             sf::Sprite    getBody     () const                     { return body_; }
         
             sf::Vector2f  getPosition () const            override { return body_.getPosition(); }
             sf::Vector2f  getSize     () const            override { return sf::Vector2f(body_.getGlobalBounds().width, body_.getGlobalBounds().height); }
    };

}

#endif