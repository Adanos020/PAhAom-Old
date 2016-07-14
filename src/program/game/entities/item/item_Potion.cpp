/**
 * @file src/program/game/item/item_Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "item_Potion.hpp"
#include "../../../program.hpp"
#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern rr::Resources resources;
extern sf::Color     itemColors[9];

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2i pos)
    : Discoverable( ),
      effect_     (e),
      size_       (s) {

        amount_     = am;
        
        initialize();
        setPosition(pos);
    }

    Potion::Potion(Potion const& potion)
    : Discoverable(              ),
      effect_     (potion.effect_) {

        amount_                = potion.amount_;
        disposable_            = potion.disposable_;
        stackable_             = potion.stackable_;
        ID_                    = potion.ID_;
        iconIndex_             = potion.iconIndex_;
        name_                  = potion.name_;
        description_           = potion.description_;
        discoveredName_        = potion.discoveredName_;
        discoveredDescription_ = potion.discoveredDescription_;
        body_                  = potion.body_;
    }

    void Potion::initialize() {
        disposable_ = true;
        stackable_  = true;
        ID_         = 100 + size_*10 + effect_;
        iconIndex_  = size_+1;

             if (itemColors[effect_] == sf::Color::Red)           name_ = resources.dictionary["item.potion.color.red"     ];
        else if (itemColors[effect_] == sf::Color::Blue)          name_ = resources.dictionary["item.potion.color.blue"    ];
        else if (itemColors[effect_] == sf::Color(32, 32, 0))     name_ = resources.dictionary["item.potion.color.brown"   ];
        else if (itemColors[effect_] == sf::Color::Green)         name_ = resources.dictionary["item.potion.color.green"   ];
        else if (itemColors[effect_] == sf::Color::Cyan)          name_ = resources.dictionary["item.potion.color.cyan"    ];
        else if (itemColors[effect_] == sf::Color(255, 172, 172)) name_ = resources.dictionary["item.potion.color.pink"    ];
        else if (itemColors[effect_] == sf::Color::Magenta)       name_ = resources.dictionary["item.potion.color.magenta" ];
        else if (itemColors[effect_] == sf::Color::Yellow)        name_ = resources.dictionary["item.potion.color.yellow"  ];
        else if (itemColors[effect_] == sf::Color::White)         name_ = resources.dictionary["item.potion.color.white"   ];
        description_ = resources.dictionary["item.potion.description.unknown"];

        switch (effect_) {
        case HEALING:
            discoveredName_        = resources.dictionary["item.potion.effect.healing"          ];
            discoveredDescription_ = resources.dictionary["item.potion.description.healing"     ];
            break;

        case MAGIC:
            discoveredName_        = resources.dictionary["item.potion.effect.magic"            ];
            discoveredDescription_ = resources.dictionary["item.potion.description.magic"       ];
            break;

        case STRENGTH:
            discoveredName_        = resources.dictionary["item.potion.effect.strength"         ];
            discoveredDescription_ = resources.dictionary["item.potion.description.strength"    ];
            break;

        case DEXTERITY:
            discoveredName_        = resources.dictionary["item.potion.effect.dexterity"        ];
            discoveredDescription_ = resources.dictionary["item.potion.description.dexterity"   ];
            break;
            
        case SPEED:
            discoveredName_        = resources.dictionary["item.potion.effect.speed"            ];
            discoveredDescription_ = resources.dictionary["item.potion.description.speed"       ];
            break;

        case REGENERATION:
            discoveredName_        = resources.dictionary["item.potion.effect.regeneration"     ];
            discoveredDescription_ = resources.dictionary["item.potion.description.regeneration"];
            break;

        case POISON:
            discoveredName_        = resources.dictionary["item.potion.effect.poison"           ];
            discoveredDescription_ = resources.dictionary["item.potion.description.poison"      ];
            break;

        case SLOWNESS:
            discoveredName_        = resources.dictionary["item.potion.effect.slowness"         ];
            discoveredDescription_ = resources.dictionary["item.potion.description.slowness"    ];
            break;

        case WEAKNESS:
            discoveredName_        = resources.dictionary["item.potion.effect.weakness"         ];
            discoveredDescription_ = resources.dictionary["item.potion.description.weakness"    ];
            break;
        }

        if (discovered_) {
            name_        = discoveredName_;
            description_ = discoveredDescription_;
        }

        int icons[] = { (int)iconIndex_, (int)iconIndex_+16 };

        setIcon    (body_, 2, icons);
        setColor   (body_, 1, itemColors[effect_]);
    }

    void Potion::reveal() {
        discovered_  = true;
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

    std::ifstream& Potion::operator<<(std::ifstream& file) {
        sf::Vector2i position;
        int effect, size;

        try {
            readFile <int>  (file, position.x);
            readFile <int>  (file, position.y);
            readFile <int>  (file, amount_);
            readFile <bool> (file, discovered_);
            readFile <int>  (file, effect);
            readFile <int>  (file, size);
        }
        catch (std::exception ex) {
            std::cerr << ex.what() << '\n';
        }

        effect_ = (Effect) effect;
        size_   = (Size)   size;

        initialize();
        setPosition(position);

        return file;
    }

    std::ofstream& Potion::operator>>(std::ofstream& file) {
        file << 6                           << ' '
             << (int)body_[0].position.x/80 << ' '
             << (int)body_[0].position.y/80 << ' '
             << amount_                     << ' '
             << discovered_                 << ' '
             << effect_                     << ' '
             << size_;

        return file;
    }

}
