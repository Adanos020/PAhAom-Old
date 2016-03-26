#include "gui.h"

namespace rr {

    Button::Button(Component* parentComponent, sf::Vector2f position, std::wstring str, unsigned chsize, sf::Color c) :Component() {
        parent = parentComponent;
        text = new Text(this, str, chsize, c);
        text->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        image = new Image(this, position, 14, "data/graphics/gui.png", 0);

        body.setPosition(position);
        body.setSize(sf::Vector2f(text->getSize().x+20, text->getSize().y*2.1));
        body.setFillColor(sf::Color(0, 0, 0));
    }

    inline Button::Component::~Component() {}
    Button::~Button() {
        delete image;
        delete text;
    }

    bool Button::containsMouseCursor(sf::RenderWindow& rw) {
        if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    void Button::setPosition(sf::Vector2f position) {
        body.setPosition(position);
        text->setPosition(sf::Vector2f(position.x+10, position.y-0.5));
        image->setPosition(position);
    }

    void Button::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        text->draw(rw);
    }

}
