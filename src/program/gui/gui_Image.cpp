/**
 * @file src/program/gui/gui_Image.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "gui.hpp"
#include "../program.hpp"

namespace rr {

    Image::Image(sf::Vector2f pos, sf::Texture& texture, int iconSize, unsigned index)
    : Component(        ),
      icon_    (iconSize) {

        unsigned tu = index%(texture.getSize().x/icon_);
        unsigned tv = index/(texture.getSize().y/icon_);

        body_.setPosition   (pos);
        body_.setTexture    (texture);
        body_.setTextureRect(sf::IntRect(tu*icon_, tv*icon_, icon_, icon_));
        body_.scale         (sf::Vector2f(5, 5));
    }

    Image::~Image() {}

    void Image::setIconIndex(unsigned index) {
        unsigned tu = index%(body_.getTexture()->getSize().x/icon_);
        unsigned tv = index/(body_.getTexture()->getSize().y/icon_);

        body_.setTextureRect(sf::IntRect(tu*icon_, tv*icon_, icon_, icon_));
    }

    void Image::setTexture(sf::Texture& texture) {
        body_.setTexture(texture);
    }

    void Image::scale(sf::Vector2f v) {
        body_.scale(v);
    }

    void Image::paint(sf::Color c) {
        body_.setColor(c);
    }

    void Image::setPosition(sf::Vector2f pos) {
        body_.setPosition(pos);
    }

    void Image::setSize(sf::Vector2f size) {
        body_.setScale(sf::Vector2f(size.x/body_.getGlobalBounds().width, size.y/body_.getGlobalBounds().height));
    }

    void Image::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
    }
}
