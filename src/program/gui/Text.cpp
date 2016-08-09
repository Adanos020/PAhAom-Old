/**
 * @file src/program/gui/Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Text.hpp"

namespace rr {

    Text::Text(sf::String str, sf::Font& font, unsigned chsize, sf::Color color, sf::Text::Style style) {
        text_.setFont            (font);
        text_.setCharacterSize   (chsize);
        text_.setString          (str);
        text_.setFillColor       (color);
        text_.setStyle           (style);
        text_.setOutlineColor    (sf::Color::Black);
        text_.setOutlineThickness((float) chsize/20.f);
    }

    Text::Text(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color color, sf::Text::Style style) {
        text_.setFont            (font);
        text_.setPosition        (pos);
        text_.setCharacterSize   (chsize);
        text_.setString          (str);
        text_.setFillColor       (color);
        text_.setStyle           (style);
        text_.setOutlineColor    (sf::Color::Black);
        text_.setOutlineThickness((float) chsize/20.f);
    }

    void Text::setPosition(sf::Vector2f pos) {
        text_.setPosition(pos);
    }

    void Text::wrap(float width) {
        sf::String text         = text_.getString();
        unsigned   offset       = 0;
        bool       first        = true;
        unsigned   wordBegining = 0;

        for (unsigned pos=0; pos<text.getSize(); pos++) {
            if      (text[pos] == '\n') {
                offset = 0;
                first  = true;
                continue;
            }
            else if (text[pos] == ' ') {
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

    void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(text_, states);
    }

}
