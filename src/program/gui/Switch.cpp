/**
 * @file src/program/gui/Switch.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Switch.hpp"

#include "../Program.hpp"

namespace rr
{

    Switch::Switch(sf::Vector2f size, sf::Vector2f pos) :
      left_ (Button(pos, "<", 30)),
      right_(Button(sf::Vector2f(body_.getPosition().x + body_.getSize().x+24, pos.y), ">", 30)),
      text_ (Text  (sf::Vector2f(0, 0), L"QYTA CLOHJÉR", Resources::font.Unifont, size.y))
    {
        body_ .setSize            (size);
        body_ .setPosition        (sf::Vector2f(pos.x+44, pos.y+5));
        body_ .setFillColor       (sf::Color(128, 128, 128, 128));
        body_ .setOutlineColor    (sf::Color(108, 108, 108));
        body_ .setOutlineThickness(5);

        left_ .setParentComponent (this);
        right_.setParentComponent (this);
        text_ .setParentComponent (this);

        setPosition(pos);

        counter_ = 0;
    }

    void
    Switch::setPosition(sf::Vector2f pos)
    {
        left_ .setPosition(pos);
        body_ .setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        text_ .setPosition(sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2, body_.getPosition().y-4));
        right_.setPosition(sf::Vector2f(pos.x+body_.getSize().x + body_.getSize().y+21, pos.y));
    }

    void
    Switch::setSize(sf::Vector2f s)
    {
        body_ .setSize(s);
        right_.setPosition(sf::Vector2f(s.x+s.x+s.y+11, s.y));
    }

    void
    Switch::buttonEvents(sf::RenderWindow& rw, sf::Event& e)
    {
        if (left_.isPressed(rw, e))
        {
            if (  counter_ > 0
                ) counter_--;
            else  counter_ = options_.size()-1;
            
            text_.setString  (options_[counter_]);
            text_.setPosition(sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2, body_.getPosition().y-4));
        }
        else if (right_.isPressed(rw, e))
        {
            if (  counter_<options_.size()-1
                ) counter_++;
            else  counter_ = 0;
            
            text_.setString  (options_[counter_]);
            text_.setPosition(sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2, body_.getPosition().y-4));
        }
    }

    void
    Switch::addOption(sf::String opt)
    {
        options_.push_back(opt);
        if (options_.size() == 1)
        {
            text_.setString  (options_[counter_]);
            text_.setPosition(sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2, body_.getPosition().y-4));
        }
    }

    void
    Switch::setCurrentOption(sf::String o)
    {
        int i = 0;
        for (auto x : options_)
        {
            if (  x == o
                ) break;
            ++i;
        }
        counter_ = i;
        text_.setString  (options_[counter_]);
        text_.setPosition(sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2, body_.getPosition().y-4));
    }

    void
    Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body_ , states);
        target.draw(left_ , states);
        target.draw(right_, states);
        target.draw(text_ , states);
    }

}
