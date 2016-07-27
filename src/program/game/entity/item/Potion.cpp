/**
 * @file src/program/game/item/Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Potion.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern sf::Color itemColors[9];

namespace rr {

    bool Potion::identified_[9] = { false, false, false, false, false, false, false, false, false };

    Potion::Potion(Effect e, Size s, int am, sf::Vector2i pos) :
      Discoverable( ),
      effect_     (e),
      size_       (s)
    {
        amount_     = am;
        
        initialize();
        setPosition(pos);
    }

    Potion::Potion(Potion const& potion) :
      Discoverable(              ),
      effect_     (potion.effect_)
    {
        amount_                = potion.amount_;
        disposable_            = potion.disposable_;
        stackable_             = potion.stackable_;
        ID_                    = potion.ID_;
        iconIndex_             = potion.iconIndex_;
        body_                  = potion.body_;
    }

    void Potion::initialize() {
        disposable_ = true;
        stackable_  = true;
        cursed_     = false;
        ID_         = 100 + effect_*10 + size_;
        iconIndex_  = 3-size_;

        int icons[] = { (int)iconIndex_, (int)iconIndex_+16 };

        setIcon (body_, 2, icons);
        setColor(body_, 1, itemColors[effect_]);
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &Resources::texture.items);
    }

    sf::String Potion::getName() const {
        if (!identified_[effect_]) {
                 if (itemColors[effect_] == sf::Color::Red          ) return Resources::dictionary["item.potion.color.red"     ];
            else if (itemColors[effect_] == sf::Color::Blue         ) return Resources::dictionary["item.potion.color.blue"    ];
            else if (itemColors[effect_] == sf::Color(32, 32, 0)    ) return Resources::dictionary["item.potion.color.brown"   ];
            else if (itemColors[effect_] == sf::Color::Green        ) return Resources::dictionary["item.potion.color.green"   ];
            else if (itemColors[effect_] == sf::Color::Cyan         ) return Resources::dictionary["item.potion.color.cyan"    ];
            else if (itemColors[effect_] == sf::Color(255, 172, 172)) return Resources::dictionary["item.potion.color.pink"    ];
            else if (itemColors[effect_] == sf::Color::Magenta      ) return Resources::dictionary["item.potion.color.magenta" ];
            else if (itemColors[effect_] == sf::Color::Yellow       ) return Resources::dictionary["item.potion.color.yellow"  ];
            else if (itemColors[effect_] == sf::Color::White        ) return Resources::dictionary["item.potion.color.white"   ];
        }
        else {
            switch (effect_) {
                case HEALING:      return Resources::dictionary["item.potion.effect.healing"     ];
                case MAGIC:        return Resources::dictionary["item.potion.effect.magic"       ];
                case STRENGTH:     return Resources::dictionary["item.potion.effect.strength"    ];
                case DEXTERITY:    return Resources::dictionary["item.potion.effect.dexterity"   ];
                case SPEED:        return Resources::dictionary["item.potion.effect.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.effect.regeneration"];
                case POISON:       return Resources::dictionary["item.potion.effect.poison"      ];
                case SLOWNESS:     return Resources::dictionary["item.potion.effect.slowness"    ];
                case WEAKNESS:     return Resources::dictionary["item.potion.effect.weakness"    ];
            }
        }
        return "";
    }

    sf::String Potion::getDescription() const {
        if ( !identified_[effect_]
            ) return Resources::dictionary["item.potion.description.unknown"];
        else {
            switch (effect_) {
                case HEALING     : return Resources::dictionary["item.potion.description.healing"     ];
                case MAGIC       : return Resources::dictionary["item.potion.description.magic"       ];
                case STRENGTH    : return Resources::dictionary["item.potion.description.strength"    ];
                case DEXTERITY   : return Resources::dictionary["item.potion.description.dexterity"   ];
                case SPEED       : return Resources::dictionary["item.potion.description.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.description.regeneration"];
                case POISON      : return Resources::dictionary["item.potion.description.poison"      ];
                case SLOWNESS    : return Resources::dictionary["item.potion.description.slowness"    ];
                case WEAKNESS    : return Resources::dictionary["item.potion.description.weakness"    ];
            }
        }
        return "";
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
            readFile <int>  (file, effect);
            readFile <int>  (file, size);
        }
        catch (std::invalid_argument ex) {
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
             << effect_                     << ' '
             << size_;

        return file;
    }

}
