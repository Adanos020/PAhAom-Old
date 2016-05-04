/**
 * @file src/program/gui/gui__text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"

namespace rr {

    Text::Text(sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        _text.setFont         (font);
        _text.setCharacterSize(chsize);
        _text.setString       (str);
        _text.setColor        (c);
        _text.setStyle        (sf::Text::Bold);
    }

    Text::Text(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        _text.setFont         (font);
        _text.setPosition     (pos);
        _text.setCharacterSize(chsize);
        _text.setString       (str);
        _text.setColor        (c);
        _text.setStyle        (sf::Text::Bold);
    }

    Text::~Text() {}

    void Text::setPosition(sf::Vector2f pos) {
        _text.setPosition(pos);
    }

    void Text::setCharacterSize(unsigned chsize) {
        _text.setCharacterSize(chsize);
    }

    void Text::setColor(sf::Color c) {
        _text.setColor(c);
    }

    void Text::setString(sf::String s) {
        _text.setString(s);
    }

    void Text::setFont(sf::Font f) {
        _text.setFont(f);
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(_text);
    }

}
