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
        body_.setSize(sf::Vector2f(35, 35));
        body_.setPosition(pos);
        body_.setFillColor(c);
        body_.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body_.setOutlineThickness(5);

        text_  = new Text (sf::Vector2f(0, 0), txt, resources.font.Unifont, chsize);
        image_ = new Image(pos, 14, 1);
        text_->setPosition(sf::Vector2f(pos.x+45, pos.y+body_.getSize().y/2-text_->getSize().y));

        image_->setParentComponent(this);
        text_ ->setParentComponent(this);
    }

    Checkbox::~Checkbox() {
        delete image_;
        delete text_;
    }

    void Checkbox::check(bool b) {
        checked_ = b;
    }

    void Checkbox::setPosition(sf::Vector2f pos) {
        body_  .setPosition(pos);
        text_ ->setPosition(sf::Vector2f(pos.x+45, pos.y+body_.getSize().y/2-text_->getSize().y));
        image_->setPosition(pos);
    }

    void Checkbox::draw(sf::RenderWindow& rw) {
        rw.draw(body_);
        if (checked_)
            image_->draw(rw);
        text_->draw(rw);
    }

    bool Checkbox::containsMouseCursor(sf::RenderWindow& rw) {
        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Checkbox::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            held_ = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            held_ = false;
        return false;
    }

}
