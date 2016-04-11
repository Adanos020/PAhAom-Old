/**
 * @file src/program/gui/Slider.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Slider::Slider(Plain p, sf::Vector2f position, sf::Vector2f size, sf::Vector2f min_max) {
        valueLimit = min_max;
        value      = valueLimit.x;
        plain      = p;
        bLeft      = new Button(position, "<", 30);
        bRight     = new Button(position+sf::Vector2f(size.x+20, 0), ">", 30);
        indicator  = new Button(position+sf::Vector2f(10, 5), "|", 30);
        label      = new Text  (sf::Vector2f(0, 0), "", resources.font.Unifont);

        border.setPosition(bLeft->getPosition()+sf::Vector2f(bLeft->getSize().x+10, 5));
        border.setOutlineThickness(5);
        border.setOutlineColor(sf::Color(128, 128, 128, 128));
        border.setFillColor(sf::Color(128, 128, 128, 128));
        border.setSize(size);

        label->setPosition(border.getPosition()+sf::Vector2f(border.getSize().x/2-label->getSize().x/2, -5));
    }

    Slider::~Slider() {
        delete indicator;
        delete bLeft;
        delete bRight;
        delete label;
    }

    void Slider::setPosition(sf::Vector2f pos) {
        bLeft    ->setPosition(pos);
        border    .setPosition(bLeft ->getPosition()+sf::Vector2f(bLeft->getSize().x+10, 5));
        bRight   ->setPosition(border .getPosition()+sf::Vector2f(border.getSize().x+10, -5));
        indicator->setPosition(border .getPosition()+sf::Vector2f(-5, -5));
        label    ->setPosition(bRight->getPosition()+sf::Vector2f(10, 0));
    }

    void Slider::setSize(sf::Vector2f siz) {
        border .setSize(siz);
        bRight->setPosition(border .getPosition()+sf::Vector2f(border.getSize().x+10, 0));
        label ->setPosition(bRight->getPosition()+sf::Vector2f(10, 0));
    }

    void Slider::setValue(int val) {
        value = val;
        if (value < valueLimit.x)
            value = valueLimit.x;
        else if (value > valueLimit.y)
            value = valueLimit.y;
        indicator->setPosition(border.getPosition()+sf::Vector2f((border.getSize().x-indicator->getSize().x+6)*(val-valueLimit.x)/valueLimit.y-3, -5));
        label->setString(std::to_string((int)value));
        label->setPosition(border.getPosition()+sf::Vector2f(border.getSize().x/2-label->getSize().x/2, -5));
    }

    void Slider::draw(sf::RenderWindow& rw) {
        rw.draw(border);
        bLeft    ->draw(rw);
        bRight   ->draw(rw);
        indicator->draw(rw);
        label    ->draw(rw);
    }

    void Slider::buttonEvents(sf::RenderWindow& rw) {
#define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define mousePosition sf::Mouse::getPosition(rw)

        if (indicator->containsMouseCursor(rw) && isMLBPressed) {
            if (mousePosition.x >= border.getPosition().x+5 && mousePosition.x <= border.getPosition().x+border.getSize().x-indicator->getSize().x+17) {
                indicator->setPosition(sf::Vector2f(mousePosition.x-5, indicator->getPosition().y));
                setValue((valueLimit.y*(indicator->getPosition().x-border.getPosition().x-3))/(border.getSize().x-indicator->getSize().x+6)+valueLimit.x);
            }
        }
        if (bLeft->containsMouseCursor(rw) && isMLBPressed) {
            setValue(getValue()-1);
        }
        if (bRight->containsMouseCursor(rw) && isMLBPressed) {
            setValue(getValue()+1);
        }

#undef isMLBPressed
#undef mousePosition
    }

}
