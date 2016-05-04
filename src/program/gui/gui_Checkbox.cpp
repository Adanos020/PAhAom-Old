/**
 * @file src/program/gui/gui_Checkbox.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Checkbox::Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color c) {
        _body.setSize(sf::Vector2f(35, 35));
        _body.setPosition(pos);
        _body.setFillColor(c);
        _body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        _body.setOutlineThickness(5);

        _text  = new Text (sf::Vector2f(0, 0), txt, resources.font.Unifont, chsize);
        _image = new Image(pos, 14, 1);
        _text->setPosition(sf::Vector2f(pos.x+45, pos.y+_body.getSize().y/2-_text->getSize().y));

        _image->setParentComponent(this);
        _text ->setParentComponent(this);
    }

    Checkbox::~Checkbox() {
        delete _image;
        delete _text;
    }

    void Checkbox::check(bool b) {
        _checked = b;
    }

    void Checkbox::setPosition(sf::Vector2f pos) {
        _body  .setPosition(pos);
        _text ->setPosition(sf::Vector2f(pos.x+45, pos.y+_body.getSize().y/2-_text->getSize().y));
        _image->setPosition(pos);
    }

    void Checkbox::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
        if (_checked)
            _image->draw(rw);
        _text->draw(rw);
    }

    bool Checkbox::containsMouseCursor(sf::RenderWindow& rw) {
        if (_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            _body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        _body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Checkbox::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            _held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            _held = false;
        return false;
    }

}
