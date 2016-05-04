/**
 * @file src/program/gui/gui_Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"

namespace rr {

    Text::Text(sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        text_.setFont         (font);
        text_.setCharacterSize(chsize);
        text_.setString       (str);
        text_.setColor        (c);
        text_.setStyle        (sf::Text::Bold);
    }

    Text::Text(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        text_.setFont         (font);
        text_.setPosition     (pos);
        text_.setCharacterSize(chsize);
        text_.setString       (str);
        text_.setColor        (c);
        text_.setStyle        (sf::Text::Bold);
    }

    Text::~Text() {}

    void Text::setPosition(sf::Vector2f pos) {
        text_.setPosition(pos);
    }

    void Text::setCharacterSize(unsigned chsize) {
        text_.setCharacterSize(chsize);
    }

    void Text::setColor(sf::Color c) {
        text_.setColor(c);
    }

    void Text::setString(sf::String s) {
        text_.setString(s);
    }

    void Text::setFont(sf::Font f) {
        text_.setFont(f);
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(text_);
    }

}
