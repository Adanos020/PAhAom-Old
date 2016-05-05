/**
 * @file src/program/gui/gui_Window.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Window::Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color c) {
        body_.setSize(size);
        body_.setPosition(position);
        body_.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        body_.setOutlineColor(c);
        body_.setOutlineThickness(5);

        header_ = new Text(sf::Vector2f(0, 0), head, resources.font.Unifont, 20, sf::Color::Yellow);
        header_->setPosition(sf::Vector2f(position.x+5, position.y));

        header_->setParentComponent(this);

        visible_ = false;
    }

    Window::~Window() {
        delete header_;
        components_.clear();
    }

    void Window::addComponent(Component* c, bool attached) {
        if (attached)
            c->setPosition(sf::Vector2f(body_.getPosition().x+c->getPosition().x, body_.getPosition().y+c->getPosition().y));
        c->setParentComponent(this);
        components_.push_back(c);
    }

    void Window::setVisible(bool b) {
        visible_ = b;
    }

    void Window::draw(sf::RenderWindow& rw) {
        if (visible_) {
            rw.draw(body_);
            header_->draw(rw);
            for (auto x : components_)
                x->draw(rw);
        }
    }

}
