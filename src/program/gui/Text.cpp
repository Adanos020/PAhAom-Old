#include "gui.h"

namespace rr {

    Text::Text(std::string str, unsigned chsize, sf::Color c) :Component() {
        font.loadFromFile("data/font/I-pixel-u-mod.ttf");

        text.setFont(font);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::Text(std::wstring str, unsigned chsize, sf::Color c) :Component() {
        font.loadFromFile("data/font/I-pixel-u-mod.ttf");

        text.setFont(font);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::Text(std::string str, sf::Vector2f pos, unsigned chsize, sf::Color c) :Component() {
        font.loadFromFile("data/font/I-pixel-u-mod.ttf");

        text.setFont(font);
        text.setPosition(pos);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::Text(std::wstring str, sf::Vector2f pos, unsigned chsize, sf::Color c) :Component() {
        font.loadFromFile("data/font/I-pixel-u-mod.ttf");

        text.setFont(font);
        text.setPosition(pos);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    void Text::setPosition(sf::Vector2f pos) {
        text.setPosition(pos);
    }

    void Text::setCharacterSize(unsigned chsize) {
        text.setCharacterSize(chsize);
    }

    void Text::setColor(sf::Color c) {
        text.setColor(c);
    }

    void Text::setString(std::string s) {
        text.setString(s);
    }

    void Text::setString(std::wstring s) {
        text.setString(s);
    }

    sf::Vector2f Text::getSize() {
        return sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
    }

    sf::Vector2f Text::getPosition() {
        return text.getPosition();
    }

    double Text::getCharacterSize() {
        return text.getCharacterSize();
    }

    sf::Color Text::getColor() {
        return text.getColor();
    }

    std::string Text::getString() {
        return text.getString();
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(text);
    }

}
