/**
 * @file src/program/gui/Window.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Window.hpp"

#include "../Resources.hpp"

namespace rr
{

    Window::Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color c) :
      m_header (Text(sf::Vector2f(0, 0), head, Resources::font.Unifont, 20, sf::Color::Yellow)),
      m_visible(false)
    {
        m_body.setSize(size);
        m_body.setPosition(position);
        m_body.setFillColor(sf::Color(c.r, c.g, c.b, 128));
        m_body.setOutlineColor(c);
        m_body.setOutlineThickness(5);

        m_header.setPosition(sf::Vector2f(position.x+5, position.y));
        m_header.setParentComponent(this);
    }

    Window::~Window()
    {
        for (auto component : m_components)
        {
            delete component;
        }
        m_components.clear();
    }

    void
    Window::addComponent(Component* c, bool attached)
    {
        if (attached)
            c->setPosition(sf::Vector2f(m_body.getPosition().x + c->getPosition().x, m_body.getPosition().y + c->getPosition().y));
        c->setParentComponent(this);
        m_components.push_back(c);
    }

    void
    Window::setPosition(sf::Vector2f pos)
    {
        for (auto component : m_components)
        {
            component->setPosition(pos + component->getPosition() - m_body.getPosition());
        }
        m_body  .setPosition(pos);
        m_header.setPosition(sf::Vector2f(pos.x+5, pos.y));
    }

    void
    Window::setVisible(bool b)
    {
        m_visible = b;
    }

    void
    Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_visible)
        {
            target.draw(m_body  , states);
            target.draw(m_header, states);
            for (auto component : m_components)
            {
                target.draw(*component, states);
            }
        }
    }

}
