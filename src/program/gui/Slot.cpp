/**
 * @file src/program/gui/Slot.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Slot.hpp"

#include "../funcs/items.hpp"
#include "../funcs/classes.hpp"

#include "../Resources.hpp"

namespace rr {

    Slot::Slot(sf::Vector2f size, sf::Vector2f pos, int icon) :
      Component(                                                                     ),
      image_   (Image(pos, Resources::texture.gui, 14, icon)                         ),
      item_    (nullptr                                                              ),
      text_    (Text (sf::Vector2f(pos.x+5, pos.y+55), "", Resources::font.Pixel, 20)),
      hollow_  (true                                                                 )
    {
        body_ .setSize            (size);
        body_ .setPosition        (pos);
        body_ .setFillColor       (sf::Color(110, 110, 110, 128));
        body_ .setOutlineColor    (sf::Color(130, 130, 130));
        body_ .setOutlineThickness(5);

        image_.setParentComponent (this);
        text_ .setParentComponent (this);
    }

    Slot::~Slot() {
        if ( !hollow_
            ) delete item_;
    }

    void Slot::setPosition(sf::Vector2f pos) {
        body_ .setPosition(pos);
        image_.setPosition(pos);
        text_ .setPosition(sf::Vector2f(pos.x+5, pos.y+55));
    }

    void Slot::draw(sf::RenderWindow& rw) {
        rw.draw(body_);

        if (  hollow_
            ) image_.draw(rw);
        else {
            item_->draw(rw);
            if (  item_->getAmount() > 1
                ) text_.draw(rw);
        }
    }

    bool Slot::addItem(Item* item) {
        if (!hollow_) {
            if (item->getID() == item_->getID()) {
                item_->setAmount(item_->getAmount()+item->getAmount());
                text_.setString(std::to_wstring(item_->getAmount()));
                return true;
            }
            return false;
        }
        item_ = getItemFromID(item->getID(), item->getAmount());

        if (  instanceof<Discoverable, Item>(item) && ((Discoverable*)item)->isDiscovered()
            ) ((Discoverable*)item_)->reveal();

        if (  instanceof<Equipable, Item>(item) && ((Equipable*)item)->isEquipped()
            ) ((Equipable*)item_)->equip(true);

        item_->setRealPosition(body_.getPosition());
        text_.setString(std::to_string(item_->getAmount()));

        hollow_ = false;
        return true;
    }

    void Slot::removeItem(int x, bool deleteFromMemory) {
        if (!hollow_) {
            item_->setAmount(item_->getAmount()-x);
            text_.setString(std::to_string(item_->getAmount()));
            text_.setCharacterSize(20);
            if (item_->getAmount() == 0) {
                hollow_ = true;
                if (  deleteFromMemory
                    ) delete item_;
                else  item_ = nullptr;
            }
        }
    }

    void Slot::removeItem(bool deleteFromMemory) {
        hollow_ = true;
        if (  deleteFromMemory
            ) delete item_;
        else  item_ = nullptr;
    }

    void Slot::swapItems(Slot* slot) {
        Item* temp = item_;
        item_ = slot->item_;
        slot->item_ = temp ;
        
        if (hollow_ && !slot->hollow_) {
                  hollow_ = false;
            slot->hollow_ = true;

            item_->setRealPosition(body_.getPosition());

            text_.setString(std::to_string(item_->getAmount()));
            text_.setCharacterSize(20);
        }
        else if (!hollow_ && slot->hollow_) {
                  hollow_ = true;
            slot->hollow_ = false;

            slot->item_->setRealPosition(slot->body_.getPosition());

            slot->text_.setString(std::to_string(slot->item_->getAmount()));
            slot->text_.setCharacterSize(20);
        }
        else if (!hollow_ && !slot->hollow_) {
                  item_->setRealPosition(      body_.getPosition());
            slot->item_->setRealPosition(slot->body_.getPosition());

                  text_.setString(std::to_string(      item_->getAmount()));
            slot->text_.setString(std::to_string(slot->item_->getAmount()));
                  text_.setCharacterSize(20);
            slot->text_.setCharacterSize(20);
        }
    }

    void Slot::clear() {
        if (!hollow_) {
            hollow_ = true;
            delete item_;
        }
    }

    bool Slot::containsMouseCursor(sf::RenderWindow& rw) {
        if (  !hollow_
           && instanceof<Equipable, Item>(item_)
           && ((Equipable*)item_)->isEquipped()
            ) body_.setOutlineColor(sf::Color(128, 128, 180));
        else  body_.setOutlineColor(sf::Color(130, 130, 130));

        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        
        return false;
    }

    bool Slot::isPressed(sf::RenderWindow& rw, sf::Event& e, sf::Mouse::Button button) {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == button) {
            held_ = true;
            return true;
        }
        if (  e.type == sf::Event::MouseButtonReleased
            ) held_ = false;
        return false;
    }

}
