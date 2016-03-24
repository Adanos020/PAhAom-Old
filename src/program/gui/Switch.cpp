#include "gui.h"

namespace rr {

    Switch::Switch(Component* parentComponent, std::string lButton, std::string rButton, sf::Vector2f size, sf::Vector2f pos) {
        parent = parentComponent;

        body.setSize(size);
        body.setPosition(sf::Vector2f(pos.x+size.y+25, pos.y+5));
        body.setFillColor(sf::Color(128, 128, 128, 128));
        body.setOutlineColor(sf::Color(108, 108, 108));
        body.setOutlineThickness(5);

        left = new Button(this, pos, lButton, size.y-3);
        right = new Button(this, sf::Vector2f(body.getPosition().x+body.getSize().x+16, pos.y), rButton, size.y-3);
        text = new Text(this, L"", sf::Vector2f(body.getPosition().x+10, pos.y-4), size.y);

        counter = 0;
    }

    inline Switch::Component::~Component() {}
    Switch::~Switch() {
        delete left;
        delete right;
        delete text;
    }

    void Switch::setPosition(sf::Vector2f pos) {
        left->setPosition(pos);
        body.setPosition(sf::Vector2f(pos.x+body.getSize().y+10, pos.y));
        text->setPosition(sf::Vector2f(body.getPosition().x+10, pos.y-4));
        right->setPosition(sf::Vector2f(pos.x+body.getSize().x+body.getSize().y+16, pos.y));
    }

    void Switch::setSize(sf::Vector2f s) {
        body.setSize(s);
        right->setPosition(sf::Vector2f(s.x+s.x+s.y+11, s.y));
    }

    void Switch::buttonEvents(sf::RenderWindow& rw) {
        if (left->containsMouseCursor(rw) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (counter>0) counter--;
            else counter = options.size()-1;
            text->setString(options.at(counter));
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        } else if (right->containsMouseCursor(rw) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (counter<options.size()-1) counter++;
            else counter = 0;
            text->setString(options.at(counter));
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        }
    }

    void Switch::addOption(std::wstring opt) {
        options.push_back(opt);
        if (options.size()==1) {
            text->setString(options.at(counter));
            text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
        }
    }

    void Switch::setCurrentOption(std::wstring o) {
        int i=0;
        for (auto x : options) {
            if (x==o) break;
            i++;
        }
        counter = i;
        text->setString(options.at(counter));
        text->setPosition(sf::Vector2f(body.getPosition().x+body.getSize().x/2-text->getSize().x/2, body.getPosition().y-4));
    }

    void Switch::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        left->draw(rw);
        right->draw(rw);
        text->draw(rw);
    }

}
