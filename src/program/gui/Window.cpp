#include "gui.h"
#include <type_traits>
#include <typeinfo>

namespace rr {

    Window::Window(std::string head, sf::Vector2f size, sf::Vector2f position, sf::Color c) {
        body.setSize(size);
        body.setPosition(position);
        body.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        body.setOutlineColor(c);
        body.setOutlineThickness(5);

        header = new Text(head, 20, sf::Color::Yellow);
        header->setPosition(sf::Vector2f(position.x+5, position.y));

        visible = false;
    }

    Window::Window(std::wstring head, sf::Vector2f size, sf::Vector2f position, sf::Color c) {
        body.setSize(size);
        body.setPosition(position);
        body.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        body.setOutlineColor(c);
        body.setOutlineThickness(5);

        header = new Text(head, 20, sf::Color::Yellow);
        header->setPosition(sf::Vector2f(position.x+5, position.y));

        visible = false;
    }

    Window::~Window() {
        delete header;
        for (auto x : components)
            delete x;
    }

    void Window::addComponent(Component* c) {
        c->setPosition(sf::Vector2f(body.getPosition().x+c->getPosition().x, body.getPosition().y+c->getPosition().y));
        components.push_back(c);
    }

    void Window::setVisible(bool b) {
        visible = b;
    }

    bool Window::isVisible() {
        return visible;
    }

    sf::Vector2f Window::getPosition() {
        return body.getPosition();
    }

    sf::Vector2f Window::getSize() {
        return body.getSize();
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
