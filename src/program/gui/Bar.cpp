/**
 * @file src/program/gui/Bar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Bar.hpp"

namespace rr {

    Bar::Bar(Plain plain, int max_length, sf::Color c, sf::Vector2f pos)
    :
      Component() {

        if      (plain == HORIZONTAL) {
            border_.setSize(sf::Vector2f(max_length, 5));
            bar_   .setSize(sf::Vector2f(max_length, 5));
        }
        else if (plain == VERTICAL) {
            border_.setSize(sf::Vector2f(5, max_length));
            bar_   .setSize(sf::Vector2f(5, max_length));
        }

        border_.setFillColor       (sf::Color::Transparent);
        border_.setOutlineColor    (sf::Color(128, 128, 128));
        border_.setOutlineThickness(5);
        border_.setPosition        (pos);

        bar_.setFillColor          (c);
        bar_.setPosition           (pos);
    }

    Bar::~Bar() {}

    void Bar::setPosition(sf::Vector2f pos) {
        border_.setPosition(pos);
        bar_   .setPosition(pos);
    }

    void Bar::setSize(sf::Vector2f size) {
        //bar_.setSize(sf::Vector2f(border_.getSize().x/size.x * bar_.getSize().x));
        border_.setSize(size);
    }

    void Bar::setValue(sf::Vector2f scale) {
        if      (  bar_.getSize().x == 5
                 ) bar_.setScale(1, scale.y);
        else if (  bar_.getSize().y == 5
                 ) bar_.setScale(scale.x, 1);
    }

    void Bar::draw(sf::RenderWindow& rw) {
        rw.draw(bar_);
        rw.draw(border_);
    }

}
