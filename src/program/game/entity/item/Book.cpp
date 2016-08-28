/**
 * @file src/program/game/item/Book.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Book.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern sf::Color itemColors[9];

namespace rr
{

    Book::Book(Type type, int am, sf::Vector2i pos) {
        type_       = type;
        amount_     = am;

        initialize();
        setGridPosition(pos);
    }

    Book::Book(Book const& copy) :
      type_(copy.type_)
    {
        amount_      = copy.amount_;
        disposable_  = copy.disposable_;
        stackable_   = copy.stackable_;
        ID_          = copy.ID_;
        iconIndex_   = copy.iconIndex_;
        body_        = copy.body_;
    }

    void
    Book::initialize()
    {
        ID_         = type_+40;
        stackable_  = false;
        cursed_     = false;
        iconIndex_  = 16;

        disposable_ = type_ != SPELLS_BOOK;

        int icons[] = { (int)iconIndex_, icons[1] = (int)iconIndex_+16 };

        setIcon (body_, 2, icons);
        setColor(body_, 0, sf::Color(itemColors[type_].r + (255-itemColors[type_].r)/2,
                                     itemColors[type_].g + (255-itemColors[type_].g)/2,
                                     itemColors[type_].b + (255-itemColors[type_].b)/2));
    }

    sf::String
    Book::getName() const
    {
        switch (type_)
        {
            case CRAFTING:              return Resources::dictionary["item.book.type.crafting"             ];
            case ALCHEMY:               return Resources::dictionary["item.book.type.alchemy"              ];
            case COLD_WEAPON_MASTERY:   return Resources::dictionary["item.book.type.cold_weapon_mastery"  ];
            case RANGED_WEAPON_MASTERY: return Resources::dictionary["item.book.type.ranged_weapon_mastery"];
            case EAGLE_EYE:             return Resources::dictionary["item.book.type.eagle_eye"            ];
            case MANA_REGEN:            return Resources::dictionary["item.book.type.mana_regen"           ];
            case HEALTH_REGEN:          return Resources::dictionary["item.book.type.health_regen"         ];
            case FASTER_LEARNING:       return Resources::dictionary["item.book.type.faster_learning"      ];
            case SPELLS_BOOK:           return Resources::dictionary["item.book.type.spells_book"          ];
        }
        return "";
    }

    sf::String
    Book::getDescription() const
    {
        switch (type_)
        {
            case CRAFTING:              return Resources::dictionary["item.book.description.crafting"             ];
            case ALCHEMY:               return Resources::dictionary["item.book.description.alchemy"              ];
            case COLD_WEAPON_MASTERY:   return Resources::dictionary["item.book.description.cold_weapon_mastery"  ];
            case RANGED_WEAPON_MASTERY: return Resources::dictionary["item.book.description.ranged_weapon_mastery"];
            case EAGLE_EYE:             return Resources::dictionary["item.book.description.eagle_eye"            ];
            case MANA_REGEN:            return Resources::dictionary["item.book.description.mana_regen"           ];
            case HEALTH_REGEN:          return Resources::dictionary["item.book.description.health_regen"         ];
            case FASTER_LEARNING:       return Resources::dictionary["item.book.description.faster_learning"      ];
            case SPELLS_BOOK:           return Resources::dictionary["item.book.description.spells_book"          ];
        }
        return "";
    }

    void
    Book::setGridPosition(sf::Vector2i pos)
    {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void
    Book::setPosition(sf::Vector2f pos)
    {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    std::ifstream&
    Book::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, amount_);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Book::operator>>(std::ofstream& file)
    {
        file << 1                            << ' '
             << (int) body_[0].position.x/80 << ' '
             << (int) body_[0].position.y/80 << ' '
             << amount_                      << ' '
             << type_;

        return file;
    }

}
