#include "gui.h"

namespace rr {

    Bar::Bar(std::string plain, int max_length, sf::Color c, sf::Vector2f pos) {
        if (plain == "horizontal") {
            border.setSize(sf::Vector2f(max_length, 5));
            bar.setSize(sf::Vector2f(max_length, 5));
        } else if (plain == "vertical") {
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

    void Bar::resize(float scale) {
        if (bar.getSize().x == 5) bar.setScale(1, scale);
        else if (bar.getSize().y == 5) bar.setScale(scale, 1);
    }

    void Bar::draw(sf::RenderWindow& rw) {
        rw.draw(bar);
        rw.draw(border);
    }

}
