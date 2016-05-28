/**
 * @file src/program/game/item/item_Spell.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Spell.hpp"
#include "../../../program.hpp"

#include <iostream>

extern rr::Resources resources;
extern int           spellSymbols[11];

namespace rr {

    Spell::Spell(Type type, int am, sf::Vector2i pos)
    : Item(),
      type_  (type) {

        amount_     = am;
        disposable_ = true;
        stackable_  = true;
        ID_         = 39+type_;
        iconIndex_  = 64;

        switch (spellSymbols[type_]) {
            case  0: name_ = resources.dictionary["item.spell.symbol.shcha"]; break;
            case  1: name_ = resources.dictionary["item.spell.symbol.jus"  ]; break;
            case  2: name_ = resources.dictionary["item.spell.symbol.jes"  ]; break;
            case  3: name_ = resources.dictionary["item.spell.symbol.ef"   ]; break;
            case  4: name_ = resources.dictionary["item.spell.symbol.ju"   ]; break;
            case  5: name_ = resources.dictionary["item.spell.symbol.psi"  ]; break;
            case  6: name_ = resources.dictionary["item.spell.symbol.de"   ]; break;
            case  7: name_ = resources.dictionary["item.spell.symbol.omega"]; break;
            case  8: name_ = resources.dictionary["item.spell.symbol.je"   ]; break;
            case  9: name_ = resources.dictionary["item.spell.symbol.zhe"  ]; break;
            case 10: name_ = resources.dictionary["item.spell.symbol.be"   ]; break;
        }
        description_ = resources.dictionary["item.spell.description.unknown"];

        int tu = iconIndex_%16;
        int tv = iconIndex_/16;

        body_.resize(8);
        body_.setPrimitiveType(sf::Quads);

     // setting the vertices of the stone
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

     // setting the vertices of the rune
        body_[4].position  = body_[0].position;
        body_[5].position  = body_[1].position;
        body_[6].position  = body_[2].position;
        body_[7].position  = body_[3].position;

        body_[4].texCoords = body_[0].texCoords+sf::Vector2f((spellSymbols[type_]+1)*16, 0);
        body_[5].texCoords = body_[1].texCoords+sf::Vector2f((spellSymbols[type_]+1)*16, 0);
        body_[6].texCoords = body_[2].texCoords+sf::Vector2f((spellSymbols[type_]+1)*16, 0);
        body_[7].texCoords = body_[3].texCoords+sf::Vector2f((spellSymbols[type_]+1)*16, 0);
    }

    void Spell::reveal() {
        discovered_  = true;
        name_        = discoveredName_;
        description_ = discoveredDescription_;
    }

    void Spell::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Spell::setPosition(sf::Vector2i pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Spell::setRealPosition(sf::Vector2f pos) {
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
