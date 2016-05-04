/**
 * @file src/program/gui/gui_Slot.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"
#include "../game/entities/item/item.hpp"
#include "../funcs/items.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Slot::Slot(sf::Vector2f size, sf::Vector2f pos, int icon, sf::Color c) {
        _hollow = true;

        _body.setSize(size);
        _body.setPosition(pos);
        _body.setFillColor(c);
        _body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        _body.setOutlineThickness(5);

        _image    = new Image(pos, 14, icon);
        _itemSkin = new Image(pos, 14, 0);
        _text     = new Text (sf::Vector2f(pos.x+5, pos.y+45), "", resources.font.Pixel, 202);

        _itemSkin->setParentComponent(this);
        _image   ->setParentComponent(this);
        _text    ->setParentComponent(this);
    }

    Slot::~Slot() {
        if (!_hollow)
            delete _item;
    }

    void Slot::setPosition(sf::Vector2f pos) {
        _body     .setPosition(pos);
        _image   ->setPosition(pos);
        _itemSkin->setPosition(pos);
        _text    ->setPosition(sf::Vector2f(pos.x+5, pos.y+35));
    }

    void Slot::draw(sf::RenderWindow& rw) {
        rw.draw(_body);

        _itemSkin->setPosition(_body.getPosition());
        if (_hollow)
            _image->draw(rw);
        else {
            _itemSkin->draw(rw);
            if (_item->getAmount()>1)
                _text->draw(rw);
        }
    }

    bool Slot::addItem(double id, int amount) {
        if (!_hollow) {
            if (id == _item->getID()) {
                _item->setAmount(_item->getAmount()+amount);
                _text->setString(std::to_wstring(_item->getAmount()));
                _text->setCharacterSize(20);
                return true;
            }
            return false;
        }
        _item = getItemFromID(id, amount);
        _item->setPosition((sf::Vector2i)_body.getPosition());
        //_itemSkin->change(_item->get_body(), resources._texture._items);
        _text->setString(std::to_string(_item->getAmount()));
        _text->setCharacterSize(20);

        _hollow = false;
        return true;
    }

    void Slot::removeItem(int x) {
        if (!_hollow) {
            _item->setAmount(_item->getAmount()-x);
            _text->setString(std::to_string(_item->getAmount()));
            _text->setCharacterSize(20);
            if (_item->getAmount() == 0) {
                _hollow = true;
                delete _item;
            }
        }
    }

    bool Slot::containsMouseCursor(sf::RenderWindow& rw) {
        if (_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            _body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        _body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Slot::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            _held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            _held = false;
        return false;
    }

}
