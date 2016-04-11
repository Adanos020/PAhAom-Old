/**
 * @file src/program/gui/Window.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

#include <type_traits>
#include <typeinfo>

extern rr::Resources resources;

namespace rr {

    Window::Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color c) {
        body.setSize(size);
        body.setPosition(position);
        body.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        body.setOutlineColor(c);
        body.setOutlineThickness(5);

        header = new Text(sf::Vector2f(0, 0), head, resources.font.Unifont, 20, sf::Color::Yellow);
        header->setPosition(sf::Vector2f(position.x+5, position.y));

        header->setParentComponent(this);

        visible = false;
    }

    Window::~Window() {
        delete header;
        components.clear();
    }

    void Window::addComponent(Component* c, bool attached) {
        if (attached)
            c->setPosition(sf::Vector2f(body.getPosition().x+c->getPosition().x, body.getPosition().y+c->getPosition().y));
        c->setParentComponent(this);
        components.push_back(c);
    }

    void Window::setVisible(bool b) {
        visible = b;
    }

    void Window::draw(sf::RenderWindow& rw) {
        if (visible) {
            rw.draw(body);
            header->draw(rw);
            for (auto x : components)
                x->draw(rw);
        }
    }

}
