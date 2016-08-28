/**
 * @file src/program/gui/Window.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Window.hpp"

#include "../Resources.hpp"

namespace rr
{

    Window::Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color c) :
      header_  (Text(sf::Vector2f(0, 0), head, Resources::font.Unifont, 20, sf::Color::Yellow)),
      visible_ (false)
    {
        body_.setSize            (size);
        body_.setPosition        (position);
        body_.setFillColor       (sf::Color(c.r, c.g, c.b, 128));
        body_.setOutlineColor    (c);
        body_.setOutlineThickness(5);

        header_.setPosition       (sf::Vector2f(position.x+5, position.y));
        header_.setParentComponent(this);
    }

    Window::~Window()
    {
        for (auto component : components_)
        {
            delete component;
        }
        components_.clear();
    }

    void
    Window::addComponent(Component* c, bool attached)
    {
        if (  attached
            ) c->setPosition(sf::Vector2f(body_.getPosition().x + c->getPosition().x, body_.getPosition().y + c->getPosition().y));
        c->setParentComponent(this);
        components_.push_back(c);
    }

    void
    Window::setPosition(sf::Vector2f pos)
    {
        for (auto component : components_)
        {
            component->setPosition(pos + component->getPosition() - body_.getPosition());
        }
        body_  .setPosition(pos);
        header_.setPosition(sf::Vector2f(pos.x+5, pos.y));
    }

    void
    Window::setVisible(bool b)
    {
        visible_ = b;
    }

    void
    Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (visible_)
        {
            target.draw(body_  , states);
            target.draw(header_, states);
            for (auto component : components_)
            {
                target.draw(*component, states);
            }
        }
    }

}
