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
        text_  = new Text(sf::Vector2f(0, 0), str, resources.font.Unifont, chsize, c);
        text_->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        image_ = new Image(position, resources.texture.gui, 14, 0);

        text_ ->setParentComponent(this);
        image_->setParentComponent(this);

        body_.setPosition(position);
        body_.setSize(sf::Vector2f(text_->getSize().x+25, chsize*1.3425));
        text_->setPosition(sf::Vector2f(position.x+body_.getSize().x/2-text_->getSize().x/2-chsize/20, position.y-0.5));
        body_.setFillColor(sf::Color(0, 0, 0));

        held_ = false;
    }

    Button::~Button() {
        delete image_;
        delete text_;
    }

    bool Button::containsMouseCursor(sf::RenderWindow& rw) {
        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Button::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            held_ = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            held_ = false;
        return false;
    }

    void Button::setPosition(sf::Vector2f position) {
        body_  .setPosition(position);
        text_ ->setPosition(sf::Vector2f(position.x+body_.getSize().x/2-text_->getSize().x/2-text_->getCharacterSize()/20, position.y-0.5));
        image_->setPosition(position);
    }

    void Button::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
        text_->draw(rw);
    }

}
