/**
 * @file src/program/game/item/item_Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Potion.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color     potionColors[9];

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2i pos) {
        name_       = "";
        amount_     = am;
        effect_     = e;
        size_       = s;
        disposable_ = true;
        discovered_ = false;
        ID_         = 100 + size_*10 + effect_;
        iconIndex_  = size_+1;

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

     // setting the vertices of the liquID_
        body_[4].position  = body_[0].position;
        body_[5].position  = body_[1].position;
        body_[6].position  = body_[2].position;
        body_[7].position  = body_[3].position;

        body_[4].texCoords = body_[0].texCoords+sf::Vector2f(0, 16);
        body_[5].texCoords = body_[1].texCoords+sf::Vector2f(0, 16);
        body_[6].texCoords = body_[2].texCoords+sf::Vector2f(0, 16);
        body_[7].texCoords = body_[3].texCoords+sf::Vector2f(0, 16);

        body_[4].color     = potionColors[effect_];
        body_[5].color     = potionColors[effect_];
        body_[6].color     = potionColors[effect_];
        body_[7].color     = potionColors[effect_];
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        discovered_ = true;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Potion::update() {}

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
