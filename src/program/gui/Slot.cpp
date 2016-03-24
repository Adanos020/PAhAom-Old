#include "gui.h"
#include "../game/item/item.h"
#include "../game/item/item_funcs.h"

namespace rr {

    Slot::Slot(sf::Vector2f size, sf::Vector2f pos, int icon, sf::Color c) :Button(pos, "", icon) {
        hollow = true;

        body.setSize(size);
        body.setPosition(pos);
        body.setFillColor(c);
        body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body.setOutlineThickness(5);

        image = new Image(pos, 14, "data/graphics/gui.png", icon);
        itemSkin = new Image(pos, 14, "data/graphics/items.png", 0);

        text = new Text("", sf::Vector2f(pos.x+5, pos.y+45), 202);
    }

    Slot::~Slot() {
        if (!hollow) delete item;
    }

    Item* Slot::getItem() {
        if (!hollow) return item;
        return nullptr;
    }

    void Slot::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
        image->setPosition(pos);
        itemSkin->setPosition(pos);
        text->setPosition(sf::Vector2f(pos.x+5, pos.y+35));
    }

    void Slot::draw(sf::RenderWindow& rw) {
        rw.draw(body);

        itemSkin->setPosition(body.getPosition());
        if (hollow) image->draw(rw);
        else {
            itemSkin->draw(rw);
            if (item->getAmount()>1) text->draw(rw);
        }
    }

    bool Slot::addItem(double id, int amount) {
        if (!hollow) {
            if (id == item->getID()) {
                item->editAmount(item->getAmount()+amount);
                text->setString(std::to_string(item->getAmount()));
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
            item->editAmount(item->getAmount() - x);
            text->setString(std::to_string(item->getAmount()));
            text->setCharacterSize(20);
            if (item->getAmount() == 0) {
                hollow = true;
                delete item;
            }
        }
    }

    bool Slot::isEmpty() {
        return hollow;
    }
}
