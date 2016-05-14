/**
 * @file src/program/game/item/item_ColdWeapon.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_ColdWeapon.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    ColdWeapon::ColdWeapon(Type type, int amount, sf::Vector2i pos) {
        type_      = type;
        amount_    = amount;
        equipable_ = true;
        ID_        = 20 + type_;

        switch (type_) {
            case KNIFE         : damageDealt_ =  5; speed_ = 10; accuracy_ =  4; name_ = resources.dictionary["item.coldweapon.name.knife"         ]; iconIndex_ =  4; break;
            case DAGGER        : damageDealt_ =  7; speed_ =  8; accuracy_ =  5; name_ = resources.dictionary["item.coldweapon.name.dagger"        ]; iconIndex_ =  5; break;
            case SWORD         : damageDealt_ = 10; speed_ =  7; accuracy_ =  5; name_ = resources.dictionary["item.coldweapon.name.sword"         ]; iconIndex_ =  6; break;
            case SERRATED_SWORD: damageDealt_ = 19; speed_ =  7; accuracy_ =  8; name_ = resources.dictionary["item.coldweapon.name.serrated_sword"]; iconIndex_ =  7; break;
            case MACE          : damageDealt_ = 12; speed_ =  6; accuracy_ =  7; name_ = resources.dictionary["item.coldweapon.name.mace"          ]; iconIndex_ = 54; break;
            case AXE           : damageDealt_ = 15; speed_ =  7; accuracy_ =  5; name_ = resources.dictionary["item.coldweapon.name.axe"           ]; iconIndex_ = 20; break;
            case DOUBLE_AXE    : damageDealt_ = 15; speed_ =  6; accuracy_ =  5; name_ = resources.dictionary["item.coldweapon.name.double_axe"    ]; iconIndex_ = 21; break;
            case SPEAR         : damageDealt_ = 12; speed_ =  6; accuracy_ =  4; name_ = resources.dictionary["item.coldweapon.name.spear"         ]; iconIndex_ = 36; break;
            case HALBERD       : damageDealt_ = 16; speed_ =  4; accuracy_ =  5; name_ = resources.dictionary["item.coldweapon.name.halberd"       ]; iconIndex_ = 22; break;
            case LANCE         : damageDealt_ = 14; speed_ =  4; accuracy_ =  6; name_ = resources.dictionary["item.coldweapon.name.lance"         ]; iconIndex_ = 38; break;
            case PIQUE         : damageDealt_ =  9; speed_ =  7; accuracy_ =  7; name_ = resources.dictionary["item.coldweapon.name.pique"         ]; iconIndex_ = 52; break;
            case HAMMER        : damageDealt_ = 17; speed_ =  7; accuracy_ = 10; name_ = resources.dictionary["item.coldweapon.name.hammer"        ]; iconIndex_ = 55; break;
        }
        description_ = "";

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = iconIndex_%16;
        int tv = iconIndex_/16;

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
    }

    void ColdWeapon::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void ColdWeapon::enhance() {

    }

    void ColdWeapon::enchant() {

    }

}

