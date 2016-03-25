#include "gui.h"

#include <iostream>

namespace rr {

    Checkbox::Checkbox(Component* parentComponent, sf::Vector2f pos, std::wstring txt, int chsize, sf::Color c) {
        parent = parentComponent;

        position = pos;

        body.setSize(sf::Vector2f(35, 35));
        body.setPosition(pos);
        body.setFillColor(c);
        body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body.setOutlineThickness(5);

        image = new Image(this, pos, 14, "data/graphics/gui.png", 1);
        text = new Text(this, txt, sf::Vector2f(0, 0), chsize);
        text->setPosition(sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y));
    }

    Checkbox::~Checkbox() {}

    void Checkbox::check(bool b) {
        checked = b;
    }

    void Checkbox::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
        text->setPosition(sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y));
        image->setPosition(pos);
    }

    void Checkbox::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        if (checked) image->draw(rw);
        text->draw(rw);
    }

    bool Checkbox::containsMouseCursor(sf::RenderWindow& rw) {
        if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

}
