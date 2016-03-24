#include "gui.h"

namespace rr {

    Checkbox::Checkbox(sf::Vector2f pos, std::string txt, int chsize, sf::Color c) :Button(pos, txt, chsize, c) {
        checked = false;

        position = pos;

        body.setSize(sf::Vector2f(35, 35));
        body.setPosition(pos);
        body.setFillColor(c);
        body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body.setOutlineThickness(5);

        image = new Image(pos, 14, "data/graphics/gui.png", 1);
        text = new Text(txt, sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y), chsize);
    }

    Checkbox::Checkbox(sf::Vector2f pos, std::wstring txt, int chsize, sf::Color c) :Button(pos, txt, chsize, c) {
        position = pos;

        body.setSize(sf::Vector2f(35, 35));
        body.setPosition(pos);
        body.setFillColor(c);
        body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body.setOutlineThickness(5);

        image = new Image(pos, 14, "data/graphics/gui.png", 1);
        text = new Text(txt, sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y), chsize);
    }

    Checkbox::~Checkbox() {}

    void Checkbox::check(bool b) {
        checked = b;
    }

    bool Checkbox::isChecked() {
        return checked;
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

}
