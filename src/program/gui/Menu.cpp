/**
 * @file src/program/gui/Menu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Menu.hpp"

namespace rr
{

    Menu::Menu(sf::Vector2f position)
    {
        position_ = position;
    }

    Menu::~Menu()
    {
        options_.clear();
    }

    void
    Menu::addOption(sf::String option)
    {
        options_.push_back(Button(position_ + sf::Vector2f(0, options_.size()*40), option, 25));
    }

    void
    Menu::setOption(unsigned index, sf::String option)
    {
        options_[index].getText().setString(option);
    }

    void
    Menu::removeOption(unsigned index)
    {
        options_.erase(options_.begin()+index);
        for (int i=0; i<(int)options_.size(); ++i)
        {
            options_[i].setPosition(position_ + sf::Vector2f(0, i*40));
        }
    }

    sf::String
    Menu::getChosenOption(sf::RenderWindow& rw, sf::Event& event)
    {
        for (unsigned i=0; i<options_.size(); ++i) {
            if (  options_[i].isPressed(rw, event)
                ) return options_[i].getText().getString();
        }
        return "";
    }

    void
    Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto button : options_) {
            target.draw(button, states);
        }
    }

    void
    Menu::setPosition(sf::Vector2f position)
    {
        position_ = position;
        for (int i=0; i<(int)options_.size(); ++i)
        {
            options_[i].setPosition(position + sf::Vector2f(0, i*40));
        }
    }

}
