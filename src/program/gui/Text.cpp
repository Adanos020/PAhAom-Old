#include "gui.h"

extern sf::Font pixelFont;

namespace rr {

    Text::Text(Component* parentComponent, std::wstring str, unsigned chsize, sf::Color c) :Component() {
        parent = parentComponent;

        text.setFont(pixelFont);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    Text::Text(Component* parentComponent, std::wstring str, sf::Vector2f pos, unsigned chsize, sf::Color c) :Component() {
        parent = parentComponent;

        text.setFont(pixelFont);
        text.setPosition(pos);
        text.setCharacterSize(chsize);
        text.setString(str);
        text.setColor(c);
    }

    inline Text::Component::~Component() {}
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

    void Text::setString(std::string s) {
        text.setString(s);
    }

    void Text::setString(std::wstring s) {
        text.setString(s);
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(text);
    }

}
