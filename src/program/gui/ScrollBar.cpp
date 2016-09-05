/**
 * @file src/program/gui/ScrollBar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "ScrollBar.hpp"

#include "../Resources.hpp"

namespace rr
{

    ScrollBar::ScrollBar(Plain p, sf::Vector2f position, float length, sf::Vector2f min_max) :
      valueLimit_(min_max                                              ),
      indicator_ (Button(position+sf::Vector2f(10, 5), "|", 30)        ),
      bLeft_     (Button(position, "<", 30)                            ),
      bRight_    (Button(position+sf::Vector2f(length, 0), ">", 30)    ),
      label_     (Text(sf::Vector2f(0, 0), "", Resources::font.Unifont)),
      value_     (valueLimit_.x                                        ),
      plain_     (p                                                    )
    {
        if (p == VERTICAL)
        {
            bLeft_     = Button(position, L"∧", 30);
            bRight_    = Button(position+sf::Vector2f(0, length+20), L"∨", 30);
            indicator_ = Button(position+sf::Vector2f(0, 10), "_", 30);
            label_     = Text  (sf::Vector2f(0, 0), "", Resources::font.Unifont);

            border_.setPosition        (bLeft_.getPosition() + sf::Vector2f(bLeft_.getSize().x+10, 5));
            border_.setOutlineThickness(1);
            border_.setOutlineColor    (sf::Color::Black);
            border_.setFillColor       (sf::Color(128, 128, 128, 128));
            border_.setSize            (sf::Vector2f(33, length));

            label_ .setPosition        (border_.getPosition() + sf::Vector2f(-5, border_.getSize().y/2 - label_.getSize().y/2));
        }
        else
        {
            border_.setPosition        (bLeft_.getPosition() + sf::Vector2f(bLeft_.getSize().x+5, 5));
            border_.setOutlineThickness(1);
            border_.setOutlineColor    (sf::Color::Black);
            border_.setFillColor       (sf::Color(128, 128, 128, 128));
            border_.setSize            (sf::Vector2f(length, 40));

            label_.setPosition(border_.getPosition() + sf::Vector2f(border_.getSize().x/2 - label_.getSize().x/2, border_.getSize().y/2 - label_.getSize().y/2-10));
        }
    }

    void
    ScrollBar::setPosition(sf::Vector2f pos)
    {
        if (plain_ == HORIZONTAL)
        {
            bLeft_    .setPosition(pos);
            border_   .setPosition(bLeft_ .getPosition() + sf::Vector2f(bLeft_.getSize().x, 0));
            bRight_   .setPosition(border_.getPosition() + sf::Vector2f(border_.getSize().x, 0));
            indicator_.setPosition(border_.getPosition() + sf::Vector2f(-5, -5));
            label_    .setPosition(border_.getPosition()+sf::Vector2f(border_.getSize().x/2 - label_.getSize().x/2, border_.getSize().y/2 - label_.getSize().y/2-10));
        }
        else if (plain_ == VERTICAL)
        {
            bLeft_    .setPosition(pos);
            border_   .setPosition(bLeft_ .getPosition() + sf::Vector2f( 0, bLeft_.getSize().y));
            bRight_   .setPosition(border_.getPosition() + sf::Vector2f( 0, border_.getSize().y));
            indicator_.setPosition(border_.getPosition() + sf::Vector2f(-5, -5));
            label_    .setPosition(bRight_.getPosition() + sf::Vector2f(0, border_.getSize().y/2-label_.getSize().y/2));
        }
    }

    void
    ScrollBar::setSize(sf::Vector2f siz)
    {
        if (plain_ == HORIZONTAL)
        {
            border_.setSize    (sf::Vector2f(siz.x, 30));
            bRight_.setPosition(border_.getPosition() + sf::Vector2f(border_.getSize().x+10, 0));
            label_ .setPosition(bRight_.getPosition() + sf::Vector2f(10, 0));
        }
        else if (plain_ == VERTICAL)
        {
            border_.setSize    (sf::Vector2f(28, siz.y));
            bRight_.setPosition(border_.getPosition() + sf::Vector2f(0, border_.getSize().y+10));
            label_ .setPosition(border_.getPosition() + sf::Vector2f(border_.getSize().x/2 - label_.getSize().x/2-4, border_.getSize().y/2 - label_.getSize().y/2-5));
        }
    }

    void
    ScrollBar::setValue(int val)
    {
        value_ = val;
        if      (value_ < valueLimit_.x) value_ = valueLimit_.x;
        else if (value_ > valueLimit_.y) value_ = valueLimit_.y;

        label_.setString  (std::to_string((int) value_));
        label_.setPosition(border_.getPosition() + sf::Vector2f(border_.getSize().x/2 - label_.getSize().x/2,
                                                                border_.getSize().y/2 - label_.getSize().y/2-10));
    }

    void
    ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(border_   , states);
        target.draw(bLeft_    , states);
        target.draw(bRight_   , states);
        target.draw(indicator_, states);
        target.draw(label_    , states);
    }

    void
    ScrollBar::buttonEvents(sf::RenderWindow& rw, sf::Event& e)
    {
        auto mousePosition = sf::Mouse::getPosition(rw);

        if ((indicator_.isPressed(rw, e) || indicator_.isHeld()))
        {
            if (border_.getGlobalBounds().contains((sf::Vector2f) mousePosition))
            {
                if (plain_ == HORIZONTAL)
                {
                    indicator_.setPosition(sf::Vector2f(mousePosition.x-10, indicator_.getPosition().y));
                    setValue((valueLimit_.y * (indicator_.getPosition().x-border_.getPosition().x-3)) / (border_.getSize().x-indicator_.getSize().x+6) + valueLimit_.x);
                }
                else if (plain_ == VERTICAL)
                {
                    indicator_.setPosition(sf::Vector2f(indicator_.getPosition().x, mousePosition.y-10));
                    setValue((valueLimit_.y * (indicator_.getPosition().y-border_.getPosition().y-3)) / (border_.getSize().y-indicator_.getSize().y+6) + valueLimit_.x);
                }
            }
        }
        if (bLeft_ .isPressed(rw, e)) setValue(getValue()-1);
        if (bRight_.isPressed(rw, e)) setValue(getValue()+1);

        if (plain_ == HORIZONTAL)
            indicator_.setPosition(border_.getPosition() + sf::Vector2f((border_.getSize().x - indicator_.getSize().x) * (value_-valueLimit_.x)/valueLimit_.y, 0));
        else if (plain_ == VERTICAL)
            indicator_.setPosition(border_.getPosition() + sf::Vector2f(0, (border_.getSize().y - indicator_.getSize().y) * (value_-valueLimit_.x)/valueLimit_.y));
    }

}
