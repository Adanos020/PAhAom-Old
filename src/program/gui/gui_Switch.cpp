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
        body.setSize(size);
        body.setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        body.setFillColor(sf::Color(128, 128, 128, 128));
        body.setOutlineColor(sf::Color(108, 108, 108));
        body.setOutlineThickness(5);

        left  = new Button(pos, "<", 30);
        right = new Button(sf::Vector2f(body.getPosition().x+body.getSize().x+24, pos.y), ">", 30);
        text  = new Text(sf::Vector2f(0, 0), L">TE'EM 'ECTEM", resources.font.Unifont, size.y);

        left ->setParentComponent(this);
        right->setParentComponent(this);
        text ->setParentComponent(this);

        counter = 0;
    }

    Switch::~Switch() {
        delete left;
        delete right;
        delete text;
    }

    void Switch::setPosition(sf::Vector2f pos) {
        left ->setPosition(pos);
        body  .setPosition(sf::Vector2f(pos.x+44, pos.y+5));
        text ->setPosition(sf::Vector2f(body.getPosition().x+10, pos.y-4));
        right->setPosition(sf::Vector2f(pos.x+body.getSize().x+body.getSize().y+24, pos.y));
    }

    void Switch::setSize(sf::Vector2f s) {
        body.setSize(s);
        right->setPosition(sf::Vector2f(s.x+s.x+s.y+11, s.y));
    }

    void Switch::buttonEvents(sf::RenderWindow& rw, sf::Event& e) {
        if (left->isPressed(rw, e)) {
            if (counter > 0)
                counter--;
            else
                counter = options.size()-1;
            text->setString(options[counter]);
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        } else if (left->isPressed(rw, e)) {
            if (counter<options.size()-1)
                counter++;
            else
                counter = 0;
            text->setString(options[counter]);
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        }
    }

    void Switch::addOption(sf::String opt) {
        options.push_back(opt);
        if (options.size() == 1) {
            text->setString(options[counter]);
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        }
    }

    void Switch::setCurrentOption(sf::String o) {
        int i = 0;
        for (auto x : options) {
            if (x == o)
                break;
            i++;
        }
        counter = i;
        text->setString(options[counter]);
        text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
    }

    void Switch::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        left ->draw(rw);
        right->draw(rw);
        text ->draw(rw);
    }

}
