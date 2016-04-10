/**
 * @file src/program/gui/Bar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "gui.hpp"

namespace rr {

    Bar::Bar(Plain plain, int max_length, sf::Color c, sf::Vector2f pos) {
        if (plain == HORIZONTAL) {
            border.setSize(sf::Vector2f(max_length, 5));
            bar.setSize(sf::Vector2f(max_length, 5));
        } else if (plain == VERTICAL) {
            border.setSize(sf::Vector2f(5, max_length));
            bar.setSize(sf::Vector2f(5, max_length));
        }

        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color(128, 128, 128));
        border.setOutlineThickness(5);
        border.setPosition(pos);

        bar.setFillColor(c);
        bar.setPosition(pos);
    }

    Bar::~Bar() {}

    void Bar::setPosition(sf::Vector2f pos) {
        border.setPosition(pos);
        bar.setPosition(pos);
    }

    void Bar::setSize(sf::Vector2f scale) {
        if (bar.getSize().x == 5)
            bar.setScale(1, scale.y);
        else if (bar.getSize().y == 5)
            bar.setScale(scale.x, 1);
    }

    void Bar::draw(sf::RenderWindow& rw) {
        rw.draw(bar);
        rw.draw(border);
    }

}
