/**
 * @file src/program/gui/Image.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "gui.hpp"

namespace rr {

    Image::Image(sf::Vector2f pos, int iconSize, sf::Texture skin, unsigned index) {
        icn         = iconSize;
        unsigned tu = index%(skin.getSize().x/icn);
        unsigned tv = index/(skin.getSize().x/icn);

        body.setPosition(pos);
        body.setTexture(skin);
        body.setTextureRect(sf::IntRect(tu*14, tv*14, 14, 14));
        body.scale(sf::Vector2f(5, 5));
    }

    Image::~Image() {}

    void Image::change(unsigned index) {
        unsigned tu = index%((*body.getTexture()).getSize().x/icn);
        unsigned tv = index/((*body.getTexture()).getSize().x/icn);

        body.setTextureRect(sf::IntRect(tu*14, tv*14, 14, 14));
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
