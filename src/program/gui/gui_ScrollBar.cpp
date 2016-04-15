/**
 * @file src/program/gui/gui_ScrollBar.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    ScrollBar::ScrollBar(Plain p, sf::Vector2f position, float length, sf::Vector2f min_max) {
        valueLimit = min_max;
        value      = valueLimit.x;
        plain      = p;

        if (p == HORIZONTAL) {
            bLeft      = new Button(position, "<", 30);
            bRight     = new Button(position+sf::Vector2f(length+20, 0), ">", 30);
            indicator  = new Button(position+sf::Vector2f(10, 5), "|", 30);
            label      = new Text  (sf::Vector2f(0, 0), "", resources.font.Unifont);

            border.setPosition(bLeft->getPosition()+sf::Vector2f(bLeft->getSize().x+10, 5));
            border.setOutlineThickness(5);
            border.setOutlineColor(sf::Color(128, 128, 128, 128));
            border.setFillColor(sf::Color(128, 128, 128, 128));
            border.setSize(sf::Vector2f(length, 30));

            label->setPosition(border.getPosition()+sf::Vector2f(border.getSize().x/2-label->getSize().x/2, -5));
        }
        else if (p == VERTICAL) {
            bLeft      = new Button(position, L"∧", 30);
            bRight     = new Button(position+sf::Vector2f(0, length+20), L"∨", 30);
            indicator  = new Button(position+sf::Vector2f(0, 10), "_", 30);
            label      = new Text  (sf::Vector2f(0, 0), "", resources.font.Unifont);

            border.setPosition(bLeft->getPosition()+sf::Vector2f(bLeft->getSize().x+10, 5));
            border.setOutlineThickness(5);
            border.setOutlineColor(sf::Color(128, 128, 128, 128));
            border.setFillColor(sf::Color(128, 128, 128, 128));
            border.setSize(sf::Vector2f(28, length));

            label->setPosition(border.getPosition()+sf::Vector2f(-5, border.getSize().y/2-label->getSize().y/2));
        }
    }

    ScrollBar::~ScrollBar() {
        delete indicator;
        delete bLeft;
        delete bRight;
        delete label;
    }

    void ScrollBar::setPosition(sf::Vector2f pos) {
        if (plain == HORIZONTAL) {
            bLeft    ->setPosition(pos);
            border    .setPosition(bLeft ->getPosition()+sf::Vector2f(bLeft->getSize().x+10, 5));
            bRight   ->setPosition(border .getPosition()+sf::Vector2f(border.getSize().x+10, -5));
            indicator->setPosition(border .getPosition()+sf::Vector2f(-5, -5));
            label    ->setPosition(bRight->getPosition()+sf::Vector2f(10, 0));
        }
        else if (plain == VERTICAL) {
            bLeft    ->setPosition(pos);
            border    .setPosition(bLeft ->getPosition()+sf::Vector2f( 5, bLeft->getSize().y+10));
            bRight   ->setPosition(border .getPosition()+sf::Vector2f(-5, border.getSize().y+10));
            indicator->setPosition(border .getPosition()+sf::Vector2f(-5, -5));
            label    ->setPosition(bRight->getPosition()+sf::Vector2f(0, border.getSize().y/2-label->getSize().y/2));
        }
    }

    void ScrollBar::setSize(sf::Vector2f siz) {
        if (plain == HORIZONTAL) {
            border .setSize(sf::Vector2f(siz.x, 30));
            bRight->setPosition(border .getPosition()+sf::Vector2f(border.getSize().x+10, 0));
            label ->setPosition(bRight->getPosition()+sf::Vector2f(10, 0));
        }
        else if (plain == VERTICAL) {
            border .setSize(sf::Vector2f(28, siz.y));
            bRight->setPosition(border.getPosition()+sf::Vector2f(0, border.getSize().y+10));
            label ->setPosition(border.getPosition()+sf::Vector2f(border.getSize().x/2-label->getSize().x/2-4, border.getSize().y/2-label->getSize().y/2-5));
        }
    }

    void ScrollBar::setValue(int val) {
        value = val;
        if (value < valueLimit.x)
            value = valueLimit.x;
        else if (value > valueLimit.y)
            value = valueLimit.y;

        label->setString(std::to_string((int)value));
        label->setPosition(border.getPosition()+sf::Vector2f(border.getSize().x/2-label->getSize().x/2, border.getSize().y/2-label->getSize().y/2-10));
    }

    void ScrollBar::draw(sf::RenderWindow& rw) {
        rw.draw(border);
        bLeft    ->draw(rw);
        bRight   ->draw(rw);
        indicator->draw(rw);
        label    ->draw(rw);
    }

    void ScrollBar::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {

#define mousePosition sf::Mouse::getPosition(rw)

        if ((indicator->isPressed(rw, e) || indicator->isHeld())) {
            if (border.getGlobalBounds().contains((sf::Vector2f)mousePosition)) {
                if (plain == HORIZONTAL) {
                    indicator->setPosition(sf::Vector2f(mousePosition.x-10, indicator->getPosition().y));
                    setValue((valueLimit.y*(indicator->getPosition().x-border.getPosition().x-3))/(border.getSize().x-indicator->getSize().x+6)+valueLimit.x);
                }
                else if (plain == VERTICAL) {
                    indicator->setPosition(sf::Vector2f(indicator->getPosition().x, mousePosition.y-10));
                    setValue((valueLimit.y*(indicator->getPosition().y-border.getPosition().y-3))/(border.getSize().y-indicator->getSize().y+6)+valueLimit.x);
                }
            }
        }
        if (bLeft->isPressed(rw, e))
            setValue(getValue()-1);
        if (bRight->isPressed(rw, e))
            setValue(getValue()+1);

        if (plain == HORIZONTAL)
            indicator->setPosition(border.getPosition()+sf::Vector2f((border.getSize().x-indicator->getSize().x+10)*(value-valueLimit.x)/valueLimit.y-5, -5));
        else if (plain == VERTICAL)
            indicator->setPosition(border.getPosition()+sf::Vector2f(-5, (border.getSize().y-indicator->getSize().y+10)*(value-valueLimit.x)/valueLimit.y-5));

#undef mousePosition

    }

}
