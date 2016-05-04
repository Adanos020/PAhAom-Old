/**
 * @file src/program/gui/gui_Window.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Window::Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color c) {
        _body.setSize(size);
        _body.setPosition(position);
        _body.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        _body.setOutlineColor(c);
        _body.setOutlineThickness(5);

        _header = new Text(sf::Vector2f(0, 0), head, resources.font.Unifont, 20, sf::Color::Yellow);
        _header->setPosition(sf::Vector2f(position.x+5, position.y));

        _header->setParentComponent(this);

        _visible = false;
    }

    Window::~Window() {
        delete _header;
        _components.clear();
    }

    void Window::addComponent(Component* c, bool attached) {
        if (attached)
            c->setPosition(sf::Vector2f(_body.getPosition().x+c->getPosition().x, _body.getPosition().y+c->getPosition().y));
        c->setParentComponent(this);
        _components.push_back(c);
    }

    void Window::setVisible(bool b) {
        _visible = b;
    }

    void Window::draw(sf::RenderWindow& rw) {
        if (_visible) {
            rw.draw(_body);
            _header->draw(rw);
            for (auto x : _components)
                x->draw(rw);
        }
    }

}
