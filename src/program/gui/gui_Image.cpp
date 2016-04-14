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
        icn         = iconSize;
        unsigned tu = index%(resources.texture.gui.getSize().x/icn);
        unsigned tv = index/(resources.texture.gui.getSize().y/icn);

        body.setPosition(pos);
        body.setTexture(resources.texture.gui);
        body.setTextureRect(sf::IntRect(tu*icn, tv*icn, icn, icn));
        body.scale(sf::Vector2f(5, 5));
    }

    Image::~Image() {}

    void Image::change(unsigned index) {
        unsigned tu = index%(body.getTexture()->getSize().x/icn);
        unsigned tv = index/(body.getTexture()->getSize().y/icn);

        body.setTextureRect(sf::IntRect(tu*icn, tv*icn, icn, icn));
    }

    void Image::change(sf::Sprite va, sf::Texture tx) {
        body = va;
        body.setTexture(tx);
    }

    void Image::scale(sf::Vector2f v) {
        body.scale(v);
    }

    void Image::paint(sf::Color c) {
        body.setColor(c);
    }

    void Image::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
    }

    void Image::setSize(sf::Vector2f s) {
        body.setScale(sf::Vector2f(s.x/body.getGlobalBounds().width, s.y/body.getGlobalBounds().height));
    }

    void Image::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }
}
