/**
 * @file src/program/game/item/item_Book.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Book.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color itemColors[9];

namespace rr {

    Book::Book(Type type, int am, sf::Vector2i pos)
        : Item() {

        type_       = type;
        amount_     = am;
        ID_         = type_+10;
        disposable_ = true;
        stackable_  = false;
        iconIndex_  = 16;

        switch (type_) {
        case CRAFTING:
            name_        = resources.dictionary["item.book.type.crafting"];
            description_ = resources.dictionary["item.book.description.crafting"];
            break;
        case ALCHEMY:
            name_        = resources.dictionary["item.book.type.alchemy"];
            description_ = resources.dictionary["item.book.description.alchemy"];
            break;
        case COLD_WEAPON_MASTERY:
            name_        = resources.dictionary["item.book.type.cold_weapon_mastery"];
            description_ = resources.dictionary["item.book.description.cold_weapon_mastery"];
            break;
        case RANGED_WEAPON_MASTERY:
            name_        = resources.dictionary["item.book.type.ranged_weapon_mastery"];
            description_ = resources.dictionary["item.book.description.ranged_weapon_mastery"];
            break;
        case EAGLE_EYE:
            name_        = resources.dictionary["item.book.type.eagle_eye"];
            description_ = resources.dictionary["item.book.description.eagle_eye"];
            break;
        case MANA_REGEN:
            name_        = resources.dictionary["item.book.type.mana_regen"];
            description_ = resources.dictionary["item.book.description.mana_regen"];
            break;
        case HEALTH_REGEN:
            name_        = resources.dictionary["item.book.type.health_regen"];
            description_ = resources.dictionary["item.book.description.health_regen"];
            break;
        case FASTER_LEARNING:
            name_        = resources.dictionary["item.book.type.faster_learning"];
            description_ = resources.dictionary["item.book.description.faster_learning"];
            break;
        case SPELLS_BOOK:
            name_        = resources.dictionary["item.book.type.spells_book"];
            description_ = resources.dictionary["item.book.description.spells_book"];
            disposable_  = false;
            break;
        }

        body_.resize(8);
        body_.setPrimitiveType(sf::Quads);

        int tu = iconIndex_%16;
        int tv = iconIndex_/16;

     // the book's cover
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

        for (int i=0; i<4; i++) {
            body_[i].color = sf::Color(itemColors[type_].r + (255-itemColors[type_].r)/2,
                                       itemColors[type_].g + (255-itemColors[type_].g)/2,
                                       itemColors[type_].b + (255-itemColors[type_].b)/2);
        }

     // the book's pages
        body_[4].position  = body_[0].position;
        body_[5].position  = body_[1].position;
        body_[6].position  = body_[2].position;
        body_[7].position  = body_[3].position;

        body_[4].texCoords = body_[0].texCoords+sf::Vector2f(0, 16);
        body_[5].texCoords = body_[1].texCoords+sf::Vector2f(0, 16);
        body_[6].texCoords = body_[2].texCoords+sf::Vector2f(0, 16);
        body_[7].texCoords = body_[3].texCoords+sf::Vector2f(0, 16);
    }

    void Book::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Book::setPosition(sf::Vector2i pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Book::setRealPosition(sf::Vector2f pos) {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

}
