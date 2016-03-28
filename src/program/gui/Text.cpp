/**
 * @file src/program/gui/Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "gui.h"

namespace rr {

    Text::Text(Component* parentComponent, sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        parent = parentComponent;

        text.setFont(font);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::Text(Component* parentComponent, sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        parent = parentComponent;

        text.setFont(font);
        text.setPosition(pos);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::~Text() {}

    void Text::setPosition(sf::Vector2f pos) {
        text.setPosition(pos);
    }

    void Text::setCharacterSize(unsigned chsize) {
        text.setCharacterSize(chsize);
    }

    void Text::setColor(sf::Color c) {
        text.setColor(c);
    }

    void Text::setString(sf::String s) {
        text.setString(s);
    }

    void Text::setFont(sf::Font f) {
        text.setFont(f);
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(text);
    }

}
