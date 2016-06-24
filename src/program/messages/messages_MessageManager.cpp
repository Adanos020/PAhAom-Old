/**
 * @file src/program/game/messages/messages_MessageManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "messages.hpp"
#include "../program.hpp"

#include <iostream>

extern rr::Settings settings;

namespace rr {

    MessageManager::MessageManager() {}

    void MessageManager::addMessage(Message message) {
        messages_.push_back(message);
        std::cout << message.getString().toAnsiString() << '\n';

        float mHeight = messages_.back().getSize().y;
        messages_.back().setPosition(sf::Vector2f(0, settings.graphics.resolution.y-40-mHeight));

        for (int i=messages_.size()-2; i>=0; i--) {
            mHeight = messages_[i].getSize().y;
            messages_[i].setPosition(messages_[i+1].getPosition()-sf::Vector2f(0, mHeight));
        }
    }

    void MessageManager::update(sf::Time timeStep) {
        for (auto i=messages_.begin(); i!=messages_.end(); i++) {
            (*i).update(timeStep);
            if ((*i).getColor().a < 10) {
                messages_.erase(i);
                break;
            }
        }
    }

    void MessageManager::draw(sf::RenderWindow& rw) {
        for (auto message : messages_) {
            message.draw(rw);
        }
    }

    void MessageManager::onNotify(Event event, Entity* entity) {
        switch (event) {
        case ITEM_DISCOVERED:
            addMessage(Message("It was a "+((Item*)entity)->getName().toAnsiString()+".", sf::Color::Yellow, sf::Text::Style::Bold));
            break;
        case ITEM_PICKED:
            addMessage(Message("You've picked up "+std::to_string(((Item*)entity)->getAmount())+"x "+((Item*)entity)->getName().toAnsiString()+"!"));
            break;
        case ITEM_USED:
            if (instanceof<Potion, Entity>((Item*)entity)) {
                switch (((Potion*)entity)->effect_) {
                case Potion::HEALING:
                    addMessage(Message("You feel a lot healthier now."));
                    break;
                case Potion::MAGIC:
                    addMessage(Message("You feel a gain in magical power now."));
                    break;
                case Potion::STRENGTH:
                    addMessage(Message("You feel a lot stronger now."));
                    break;
                case Potion::DEXTERITY:
                    addMessage(Message("You feel like you could nakurwiac salto."));
                    break;
                case Potion::SPEED:
                    addMessage(Message("You feel like you would overtake fucking Speedy Gonzales."));
                    break;
                case Potion::REGENERATION:
                    addMessage(Message("You feel like you get cured in a moment."));
                    break;
                case Potion::POISON:
                    addMessage(Message("You feel as if you were going to vomit now."));
                    break;
                case Potion::SLOWNESS:
                    addMessage(Message("You feel like you were carrying something really heavy."));
                    break;
                case Potion::WEAKNESS:
                    addMessage(Message("You feel like you lost your will to live."));
                    break;
                }
            }
            else if (instanceof<Book, Item>((Item*)entity)) {
                switch (((Book*)entity)->type_) {
                case Book::CRAFTING:
                    addMessage(Message("Now you know how to craft!"));
                    break;
                case Book::ALCHEMY:
                    addMessage(Message("Now you know how to brew potions!"));
                    break;
                case Book::COLD_WEAPON_MASTERY:
                    addMessage(Message("Now you know how to use the cold weapon!"));
                    break;
                case Book::RANGED_WEAPON_MASTERY:
                    addMessage(Message("Now you know how to use the ranged weapon!"));
                    break;
                case Book::EAGLE_EYE:
                    addMessage(Message("Now you can see better!"));
                    break;
                case Book::MANA_REGEN:
                    addMessage(Message("Now you can regenerate your mana!"));
                    break;
                case Book::HEALTH_REGEN:
                    addMessage(Message("Now you can regenerate your health!"));
                    break;
                case Book::FASTER_LEARNING:
                    addMessage(Message("Now you know how to learn faster!"));
                    break;
                case Book::SPELLS_BOOK:

                    break;
                }
            }
            else if (instanceof<Rune, Item>((Item*)entity)) {

            }
            else if (instanceof<ColdWeapon, Item>((Item*)entity)) {

            }
            break;
        default:
            break;
        }
    }

}
