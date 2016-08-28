/**
 * @file src/program/gui/Checkbox.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Checkbox.hpp"

#include "../Resources.hpp"

namespace rr
{

    Checkbox::Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color c) :
      image_(Image(pos, Resources::texture.gui, 14, 1)),
      text_ (Text (sf::Vector2f(0, 0), txt, Resources::font.Unifont, chsize))
    {
        body_ .setSize            (sf::Vector2f(35, 35));
        body_ .setPosition        (pos);
        body_ .setFillColor       (c);
        body_ .setOutlineColor    (sf::Color(c.r+20, c.g+20, c.b+20));
        body_ .setOutlineThickness(5);

        text_ .setPosition        (sf::Vector2f(pos.x+45, pos.y+body_.getSize().y/2-text_.getSize().y));

        image_.setParentComponent (this);
        text_ .setParentComponent (this);
    }

    void
    Checkbox::check(bool b)
    {
        checked_ = b;
    }

    void
    Checkbox::setPosition(sf::Vector2f pos)
    {
        body_ .setPosition(pos);
        text_ .setPosition(sf::Vector2f(pos.x+45, pos.y+body_.getSize().y/2-text_.getSize().y));
        image_.setPosition(pos);
    }


    void
    Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body_ , states);
        if (  checked_
            ) target.draw(image_, states);
        target.draw(text_ , states);
    }

    bool
    Checkbox::containsMouseCursor(sf::RenderWindow& rw)
    {
        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw)))
        {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool
    Checkbox::isPressed(sf::RenderWindow& rw, sf::Event& e)
    {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
        {
            held_ = true;
            return true;
        }
        if (  e.type == sf::Event::MouseButtonReleased
            ) held_ = false;
        return false;
    }

}
