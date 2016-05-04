/**
 * @file src/program/gui/gui__bar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"

namespace rr {

    Bar::Bar(Plain plain, int max_length, sf::Color c, sf::Vector2f pos) {
        if (plain == HORIZONTAL) {
            _border.setSize(sf::Vector2f(max_length, 5));
            _bar.setSize(sf::Vector2f(max_length, 5));
        } else if (plain == VERTICAL) {
            _border.setSize(sf::Vector2f(5, max_length));
            _bar.setSize(sf::Vector2f(5, max_length));
        }

        _border.setFillColor(sf::Color::Transparent);
        _border.setOutlineColor(sf::Color(128, 128, 128));
        _border.setOutlineThickness(5);
        _border.setPosition(pos);

        _bar.setFillColor(c);
        _bar.setPosition(pos);
    }

    Bar::~Bar() {}

    void Bar::setPosition(sf::Vector2f pos) {
        _border.setPosition(pos);
        _bar.setPosition(pos);
    }

    void Bar::setSize(sf::Vector2f scale) {
        if (_bar.getSize().x == 5)
            _bar.setScale(1, scale.y);
        else if (_bar.getSize().y == 5)
            _bar.setScale(scale.x, 1);
    }

    void Bar::draw(sf::RenderWindow& rw) {
        rw.draw(_bar);
        rw.draw(_border);
    }

}
