/**
 * @file src/program/gui/gui_Button.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;
extern rr::Settings  settings;

namespace rr {

    Button::Button(sf::Vector2f position, sf::String str, unsigned chsize, sf::Color c) :Component() {
        _text  = new Text(sf::Vector2f(0, 0), str, resources.font.Unifont, chsize, c);
        _text->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        _image = new Image(position, 14, 0);

        _text ->setParentComponent(this);
        _image->setParentComponent(this);

        _body.setPosition(position);
        _body.setSize(sf::Vector2f(_text->getSize().x+25, chsize*1.3425));
        _text->setPosition(sf::Vector2f(position.x+_body.getSize().x/2-_text->getSize().x/2-chsize/20, position.y-0.5));
        _body.setFillColor(sf::Color(0, 0, 0));

        _held = false;
    }

    Button::~Button() {
        delete _image;
        delete _text;
    }

    bool Button::containsMouseCursor(sf::RenderWindow& rw) {
        if (_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            _body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        _body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Button::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            _held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            _held = false;
        return false;
    }

    void Button::setPosition(sf::Vector2f position) {
        _body  .setPosition(position);
        _text ->setPosition(sf::Vector2f(position.x+_body.getSize().x/2-_text->getSize().x/2-_text->getCharacterSize()/20, position.y-0.5));
        _image->setPosition(position);
    }

    void Button::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
        _text->draw(rw);
    }

}
