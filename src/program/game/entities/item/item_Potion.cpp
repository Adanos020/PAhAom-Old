/**
 * @file src/program/game/item/item_Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Potion.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color     itemColors[9];

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2i pos) {
        amount_     = am;
        effect_     = e;
        size_       = s;
        equipable_  = false;
        disposable_ = true;
        stackable_  = true;
        ID_         = 100 + size_*10 + effect_;
        iconIndex_  = size_+1;

             if (itemColors[effect_] == sf::Color::Red)           name_ = resources.dictionary["item.potion.color.red"     ]+" ";
        else if (itemColors[effect_] == sf::Color::Blue)          name_ = resources.dictionary["item.potion.color.blue"    ]+" ";
        else if (itemColors[effect_] == sf::Color(32, 32, 0))     name_ = resources.dictionary["item.potion.color.brown"   ]+" ";
        else if (itemColors[effect_] == sf::Color::Green)         name_ = resources.dictionary["item.potion.color.green"   ]+" ";
        else if (itemColors[effect_] == sf::Color::Cyan)          name_ = resources.dictionary["item.potion.color.cyan"    ]+" ";
        else if (itemColors[effect_] == sf::Color(255, 172, 172)) name_ = resources.dictionary["item.potion.color.pink"    ]+" ";
        else if (itemColors[effect_] == sf::Color::Magenta)       name_ = resources.dictionary["item.potion.color.magenta" ]+" ";
        else if (itemColors[effect_] == sf::Color::Yellow)        name_ = resources.dictionary["item.potion.color.yellow"  ]+" ";
        else if (itemColors[effect_] == sf::Color::White)         name_ = resources.dictionary["item.potion.color.white"   ]+" ";
        description_ = resources.dictionary["item.potion.description.unknown"];

        switch (effect_) {
        case HEALING:
            discoveredName_        = resources.dictionary["item.potion.effect.healing"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.healing"];
            break;
        case MAGIC:
            discoveredName_        = resources.dictionary["item.potion.effect.magic"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.magic"];
            break;
        case STRENGTH:
            discoveredName_        = resources.dictionary["item.potion.effect.strength"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.strength"];
            break;
        case DEXTERITY:
            discoveredName_        = resources.dictionary["item.potion.effect.dexterity"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.dexterity"];
            break;
        case SPEED:
            discoveredName_        = resources.dictionary["item.potion.effect.speed"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.speed"];
            break;
        case REGENERATION:
            discoveredName_        = resources.dictionary["item.potion.effect.regeneration"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.regeneration"];
            break;
        case POISON:
            discoveredName_        = resources.dictionary["item.potion.effect.poison"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.poison"];
            break;
        case SLOWNESS:
            discoveredName_        = resources.dictionary["item.potion.effect.slowness"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.slowness"];
            break;
        case WEAKNESS:
            discoveredName_        = resources.dictionary["item.potion.effect.weakness"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.weakness"];
            break;
        }

        int tu = iconIndex_%16;
        int tv = iconIndex_/16;

        body_.resize(8);
        body_.setPrimitiveType(sf::Quads);

     // setting the vertices of the flask
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

     // setting the vertices of the liquid
        body_[4].position  = body_[0].position;
        body_[5].position  = body_[1].position;
        body_[6].position  = body_[2].position;
        body_[7].position  = body_[3].position;

        body_[4].texCoords = body_[0].texCoords+sf::Vector2f(0, 16);
        body_[5].texCoords = body_[1].texCoords+sf::Vector2f(0, 16);
        body_[6].texCoords = body_[2].texCoords+sf::Vector2f(0, 16);
        body_[7].texCoords = body_[3].texCoords+sf::Vector2f(0, 16);

        body_[4].color     = itemColors[effect_];
        body_[5].color     = itemColors[effect_];
        body_[6].color     = itemColors[effect_];
        body_[7].color     = itemColors[effect_];
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        name_        = discoveredName_;
        description_ = discoveredDescription_;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Potion::setPosition(sf::Vector2i pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Potion::setRealPosition(sf::Vector2f pos) {
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
