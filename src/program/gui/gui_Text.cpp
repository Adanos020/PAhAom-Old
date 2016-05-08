/**
 * @file src/program/gui/gui_Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
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

    void Text::wrap(float width) {
        sf::String text       = text_.getString();
        unsigned offset       = 0;
        bool first            = true;
        unsigned wordBegining = 0;

        for (unsigned pos=0; pos < text.getSize(); pos++) {
            if (text[pos] == '\n'){
                offset = 0;
                first  = true;
                continue;
            } else if (text[pos] == ' ') {
                wordBegining = pos;
                first        = false;
            }

            offset += text_.getFont()->getGlyph(text[pos], text_.getCharacterSize(), text_.getStyle() == sf::Text::Bold).advance;

            if (!first && offset > width) {
                pos       = wordBegining;
                text[pos] = '\n';
                first     = true;
                offset    = 0;
            }
        }

        text_.setString(text);
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
