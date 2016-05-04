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
        _icn        = iconSize;
        unsigned tu = index%(resources.texture.gui.getSize().x/_icn);
        unsigned tv = index/(resources.texture.gui.getSize().y/_icn);

        _body.setPosition(pos);
        _body.setTexture(resources.texture.gui);
        _body.setTextureRect(sf::IntRect(tu*_icn, tv*_icn, _icn, _icn));
        _body.scale(sf::Vector2f(5, 5));
    }

    Image::~Image() {}

    void Image::change(unsigned index) {
        unsigned tu = index%(_body.getTexture()->getSize().x/_icn);
        unsigned tv = index/(_body.getTexture()->getSize().y/_icn);

        _body.setTextureRect(sf::IntRect(tu*_icn, tv*_icn, _icn, _icn));
    }

    void Image::change(sf::Sprite sprite, sf::Texture texture) {
        _body = sprite;
        _body.setTexture(texture);
    }

    void Image::scale(sf::Vector2f v) {
        _body.scale(v);
    }

    void Image::paint(sf::Color c) {
        _body.setColor(c);
    }

    void Image::setPosition(sf::Vector2f pos) {
        _body.setPosition(pos);
    }

    void Image::setSize(sf::Vector2f size) {
        _body.setScale(sf::Vector2f(size.x/_body.getGlobalBounds().width, size.y/_body.getGlobalBounds().height));
    }

    void Image::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
    }
}
