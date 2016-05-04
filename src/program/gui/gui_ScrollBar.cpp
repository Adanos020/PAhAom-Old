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
        _valueLimit = min_max;
        _value      = _valueLimit.x;
        _plain      = p;

        if (p == HORIZONTAL) {
            _bLeft      = new Button(position, "<", 30);
            _bRight     = new Button(position+sf::Vector2f(length+20, 0), ">", 30);
            _indicator  = new Button(position+sf::Vector2f(10, 5), "|", 30);
            _label      = new Text  (sf::Vector2f(0, 0), "", resources.font.Unifont);

            _border.setPosition(_bLeft->getPosition()+sf::Vector2f(_bLeft->getSize().x+10, 5));
            _border.setOutlineThickness(5);
            _border.setOutlineColor(sf::Color(128, 128, 128, 128));
            _border.setFillColor(sf::Color(128, 128, 128, 128));
            _border.setSize(sf::Vector2f(length, 30));

            _label->setPosition(_border.getPosition()+sf::Vector2f(_border.getSize().x/2-_label->getSize().x/2, -5));
        }
        else if (p == VERTICAL) {
            _bLeft      = new Button(position, L"∧", 30);
            _bRight     = new Button(position+sf::Vector2f(0, length+20), L"∨", 30);
            _indicator  = new Button(position+sf::Vector2f(0, 10), "_", 30);
            _label      = new Text  (sf::Vector2f(0, 0), "", resources.font.Unifont);

            _border.setPosition(_bLeft->getPosition()+sf::Vector2f(_bLeft->getSize().x+10, 5));
            _border.setOutlineThickness(5);
            _border.setOutlineColor(sf::Color(128, 128, 128, 128));
            _border.setFillColor(sf::Color(128, 128, 128, 128));
            _border.setSize(sf::Vector2f(28, length));

            _label->setPosition(_border.getPosition()+sf::Vector2f(-5, _border.getSize().y/2-_label->getSize().y/2));
        }
    }

    ScrollBar::~ScrollBar() {
        delete _indicator;
        delete _bLeft;
        delete _bRight;
        delete _label;
    }

    void ScrollBar::setPosition(sf::Vector2f pos) {
        if (_plain == HORIZONTAL) {
            _bLeft    ->setPosition(pos);
            _border    .setPosition(_bLeft ->getPosition()+sf::Vector2f(_bLeft->getSize().x+10, 5));
            _bRight   ->setPosition(_border .getPosition()+sf::Vector2f(_border.getSize().x+10, -5));
            _indicator->setPosition(_border .getPosition()+sf::Vector2f(-5, -5));
            _label    ->setPosition(_bRight->getPosition()+sf::Vector2f(10, 0));
        }
        else if (_plain == VERTICAL) {
            _bLeft    ->setPosition(pos);
            _border    .setPosition(_bLeft ->getPosition()+sf::Vector2f( 5, _bLeft->getSize().y+10));
            _bRight   ->setPosition(_border .getPosition()+sf::Vector2f(-5, _border.getSize().y+10));
            _indicator->setPosition(_border .getPosition()+sf::Vector2f(-5, -5));
            _label    ->setPosition(_bRight->getPosition()+sf::Vector2f(0, _border.getSize().y/2-_label->getSize().y/2));
        }
    }

    void ScrollBar::setSize(sf::Vector2f siz) {
        if (_plain == HORIZONTAL) {
            _border .setSize(sf::Vector2f(siz.x, 30));
            _bRight->setPosition(_border .getPosition()+sf::Vector2f(_border.getSize().x+10, 0));
            _label ->setPosition(_bRight->getPosition()+sf::Vector2f(10, 0));
        }
        else if (_plain == VERTICAL) {
            _border .setSize(sf::Vector2f(28, siz.y));
            _bRight->setPosition(_border.getPosition()+sf::Vector2f(0, _border.getSize().y+10));
            _label ->setPosition(_border.getPosition()+sf::Vector2f(_border.getSize().x/2-_label->getSize().x/2-4, _border.getSize().y/2-_label->getSize().y/2-5));
        }
    }

    void ScrollBar::setValue(int val) {
        _value = val;
        if (_value < _valueLimit.x)
            _value = _valueLimit.x;
        else if (_value > _valueLimit.y)
            _value = _valueLimit.y;

        _label->setString(std::to_string((int)_value));
        _label->setPosition(_border.getPosition()+sf::Vector2f(_border.getSize().x/2-_label->getSize().x/2, _border.getSize().y/2-_label->getSize().y/2-10));
    }

    void ScrollBar::draw(sf::RenderWindow& rw) {
        rw.draw(_border);
        _bLeft    ->draw(rw);
        _bRight   ->draw(rw);
        _indicator->draw(rw);
        _label    ->draw(rw);
    }

    void ScrollBar::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {

#define mousePosition sf::Mouse::getPosition(rw)

        if ((_indicator->isPressed(rw, e) || _indicator->isHeld())) {
            if (_border.getGlobalBounds().contains((sf::Vector2f)mousePosition)) {
                if (_plain == HORIZONTAL) {
                    _indicator->setPosition(sf::Vector2f(mousePosition.x-10, _indicator->getPosition().y));
                    setValue((_valueLimit.y*(_indicator->getPosition().x-_border.getPosition().x-3))/(_border.getSize().x-_indicator->getSize().x+6)+_valueLimit.x);
                }
                else if (_plain == VERTICAL) {
                    _indicator->setPosition(sf::Vector2f(_indicator->getPosition().x, mousePosition.y-10));
                    setValue((_valueLimit.y*(_indicator->getPosition().y-_border.getPosition().y-3))/(_border.getSize().y-_indicator->getSize().y+6)+_valueLimit.x);
                }
            }
        }
        if (_bLeft->isPressed(rw, e))
            setValue(getValue()-1);
        if (_bRight->isPressed(rw, e))
            setValue(getValue()+1);

        if (_plain == HORIZONTAL)
            _indicator->setPosition(_border.getPosition()+sf::Vector2f((_border.getSize().x-_indicator->getSize().x+10)*(_value-_valueLimit.x)/_valueLimit.y-5, -5));
        else if (_plain == VERTICAL)
            _indicator->setPosition(_border.getPosition()+sf::Vector2f(-5, (_border.getSize().y-_indicator->getSize().y+10)*(_value-_valueLimit.x)/_valueLimit.y-5));

#undef mousePosition

    }

}
