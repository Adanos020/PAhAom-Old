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
        hollow_ = true;

        body_.setSize(size);
        body_.setPosition(pos);
        body_.setFillColor(c);
        body_.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
        body_.setOutlineThickness(5);

        image_    = new Image(pos, resources.texture.gui, 14, icon);
        text_     = new Text (sf::Vector2f(pos.x+5, pos.y+55), "", resources.font.Pixel, 202);

        image_   ->setParentComponent(this);
        text_    ->setParentComponent(this);
    }

    Slot::~Slot() {
        if (!hollow_)
            delete item_;
    }

    void Slot::setPosition(sf::Vector2f pos) {
        body_     .setPosition(pos);
        image_   ->setPosition(pos);
        text_    ->setPosition(sf::Vector2f(pos.x+5, pos.y+55));
    }

    void Slot::draw(sf::RenderWindow& rw) {
        rw.draw(body_);

        if (hollow_)
            image_->draw(rw);
        else {
            item_    ->setRealPosition(body_.getPosition());
            item_->draw(rw);
            if (item_->getAmount()>1)
                text_->draw(rw);
        }
    }

    bool Slot::addItem(double id, int amount) {
        if (!hollow_) {
            if (id == item_->getID()) {
                item_->setAmount(item_->getAmount()+amount);
                text_->setString(std::to_wstring(item_->getAmount()));
                text_->setCharacterSize(20);
                return true;
            }
            return false;
        }
        item_ = getItemFromID(id, amount);
        item_->setRealPosition(body_.getPosition());
        text_->setString(std::to_string(item_->getAmount()));
        text_->setCharacterSize(20);

        hollow_ = false;
        return true;
    }

    void Slot::removeItem(int x) {
        if (!hollow_) {
            item_->setAmount(item_->getAmount()-x);
            text_->setString(std::to_string(item_->getAmount()));
            text_->setCharacterSize(20);
            if (item_->getAmount() == 0) {
                hollow_ = true;
                delete item_;
            }
        }
    }

    bool Slot::containsMouseCursor(sf::RenderWindow& rw) {
        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool Slot::isPressed(sf::RenderWindow& rw, sf::Event& e) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            held_ = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            held_ = false;
        return false;
    }

}
