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
        text  = new Text(sf::Vector2f(0, 0), str, resources.font.Unifont, chsize, c);
        text->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        image = new Image(position, 14, 0);

        text ->setParentComponent(this);
        image->setParentComponent(this);

        body.setPosition(position);
        body.setSize(sf::Vector2f(text->getSize().x+25, chsize*1.3425));
        text->setPosition(sf::Vector2f(position.x+body.getSize().x/2-text->getSize().x/2-chsize/20, position.y-0.5));
        body.setFillColor(sf::Color(0, 0, 0));

        held = false;
    }

    Button::~Button() {
        delete image;
        delete text;
    }

    bool Button::containsMouseCursor(sf::RenderWindow& rw) {
        if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Button::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            held = false;
        return false;
    }

    void Button::setPosition(sf::Vector2f position) {
        body  .setPosition(position);
        text ->setPosition(sf::Vector2f(position.x+body.getSize().x/2-text->getSize().x/2-text->getCharacterSize()/20, position.y-0.5));
        image->setPosition(position);
    }

    void Button::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        text->draw(rw);
    }

}
