/**
 * @file src/program/gui/Slot.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "gui.hpp"
#include "../game/item/item.hpp"
#include "../funcs/items.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Slot::Slot(sf::Vector2f size, sf::Vector2f pos, int icon, sf::Color c) {
        hollow = true;

        body.setSize(size);
        body.setPosition(pos);
        body.setFillColor(c);
        body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body.setOutlineThickness(5);

        image = new Image(pos, 14, resources.texture.gui, icon);
        itemSkin = new Image(pos, 14, resources.texture.gui, 0);
        text = new Text(sf::Vector2f(pos.x+5, pos.y+45), "", resources.font.Pixel, 202);

        itemSkin->setParentComponent(this);
        image   ->setParentComponent(this);
        text    ->setParentComponent(this);
    }

    Slot::~Slot() {
        if (!hollow)
            delete item;
    }

    void Slot::setPosition(sf::Vector2f pos) {
        body     .setPosition(pos);
        image   ->setPosition(pos);
        itemSkin->setPosition(pos);
        text    ->setPosition(sf::Vector2f(pos.x+5, pos.y+35));
    }

    void Slot::draw(sf::RenderWindow& rw) {
        rw.draw(body);

        itemSkin->setPosition(body.getPosition());
        if (hollow)
            image->draw(rw);
        else {
            itemSkin->draw(rw);
            if (item->getAmount()>1)
                text->draw(rw);
        }
    }

    bool Slot::addItem(double id, int amount) {
        if (!hollow) {
            if (id == item->getID()) {
                item->editAmount(item->getAmount()+amount);
                text->setString(std::to_wstring(item->getAmount()));
                text->setCharacterSize(20);
                return true;
            }
            return false;
        }
        item = getItemFromID(id, amount, position);
        itemSkin->change(item->getBody(), item->getSkin());
        text->setString(std::to_string(item->getAmount()));
        text->setCharacterSize(20);
        hollow = false;
        return true;
    }

    void Slot::removeItem(int x) {
        if (!hollow) {
            item->editAmount(item->getAmount()-x);
            text->setString(std::to_string(item->getAmount()));
            text->setCharacterSize(20);
            if (item->getAmount() == 0) {
                hollow = true;
                delete item;
            }
        }
    }

    bool Slot::containsMouseCursor(sf::RenderWindow& rw) {
        if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

}
