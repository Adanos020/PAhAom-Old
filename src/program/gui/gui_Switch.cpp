/**
 * @file src/program/gui/gui_Switch.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Switch::Switch(sf::Vector2f size, sf::Vector2f pos) {
        _body.setSize(size);
        _body.setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        _body.setFillColor(sf::Color(128, 128, 128, 128));
        _body.setOutlineColor(sf::Color(108, 108, 108));
        _body.setOutlineThickness(5);

        _left  = new Button(pos, "<", 30);
        _right = new Button(sf::Vector2f(_body.getPosition().x+_body.getSize().x+24, pos.y), ">", 30);
        _text  = new Text(sf::Vector2f(0, 0), L">TE'EM 'ECTEM", resources.font.Unifont, size.y);

        _left ->setParentComponent(this);
        _right->setParentComponent(this);
        _text ->setParentComponent(this);

        _counter = 0;
    }

    Switch::~Switch() {
        delete _left;
        delete _right;
        delete _text;
    }

    void Switch::setPosition(sf::Vector2f pos) {
        _left ->setPosition(pos);
        _body  .setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        _text ->setPosition(sf::Vector2f(_body.getPosition().x+10, pos.y-4));
        _right->setPosition(sf::Vector2f(pos.x+_body.getSize().x+_body.getSize().y+24, pos.y));
    }

    void Switch::setSize(sf::Vector2f s) {
        _body.setSize(s);
        _right->setPosition(sf::Vector2f(s.x+s.x+s.y+11, s.y));
    }

    void Switch::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        if (_left->isPressed(rw, e)) {
            if (_counter > 0)
                _counter--;
            else
                _counter = _options.size()-1;
            _text->setString(_options[_counter]);
            _text->setPosition(sf::Vector2f(_body.getPosition().x+_body.getSize().x/2-_text->getSize().x/2, _body.getPosition().y-4));
        } else if (_right->isPressed(rw, e)) {
            if (_counter<_options.size()-1)
                _counter++;
            else
                _counter = 0;
            _text->setString(_options[_counter]);
            _text->setPosition(sf::Vector2f(_body.getPosition().x+_body.getSize().x/2-_text->getSize().x/2, _body.getPosition().y-4));
        }
    }

    void Switch::addOption(sf::String opt) {
        _options.push_back(opt);
        if (_options.size() == 1) {
            _text->setString(_options[_counter]);
            _text->setPosition(sf::Vector2f(_body.getPosition().x+_body.getSize().x/2-_text->getSize().x/2, _body.getPosition().y-4));
        }
    }

    void Switch::setCurrentOption(sf::String o) {
        int i = 0;
        for (auto x : _options) {
            if (x == o)
                break;
            i++;
        }
        _counter = i;
        _text->setString(_options[_counter]);
        _text->setPosition(sf::Vector2f(_body.getPosition().x+_body.getSize().x/2-_text->getSize().x/2, _body.getPosition().y-4));
    }

    void Switch::draw(sf::RenderWindow& rw) {
        rw.draw(_body);
        _left ->draw(rw);
        _right->draw(rw);
        _text ->draw(rw);
    }

}
