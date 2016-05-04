/**
 * @file src/program/gui/gui_Image.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Image::Image(sf::Vector2f pos, int iconSize, unsigned index) {
        icon_        = iconSize;
        unsigned tu = index%(resources.texture.gui.getSize().x/icon_);
        unsigned tv = index/(resources.texture.gui.getSize().y/icon_);

        body_.setPosition(pos);
        body_.setTexture(resources.texture.gui);
        body_.setTextureRect(sf::IntRect(tu*icon_, tv*icon_, icon_, icon_));
        body_.scale(sf::Vector2f(5, 5));
    }

    Image::~Image() {}

    void Image::change(unsigned index) {
        unsigned tu = index%(body_.getTexture()->getSize().x/icon_);
        unsigned tv = index/(body_.getTexture()->getSize().y/icon_);

        body_.setTextureRect(sf::IntRect(tu*icon_, tv*icon_, icon_, icon_));
    }

    void Image::change(sf::Sprite sprite, sf::Texture texture) {
        body_ = sprite;
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
