/**
 * @file src/program/game/item/item.h
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef item_h
#define item_h

#include <SFML/Graphics.hpp>

namespace rr {

    class Item {
      protected:
        sf::FloatRect boundBox;
        sf::Texture skin;
        sf::VertexArray body;

        int amount;
        double ID;
        bool equipable;
        bool disposable;
        sf::String name;
        sf::String description;
        sf::String effects;
        sf::String requirements;
      public:
        virtual ~Item() = default;
        virtual void draw(sf::RenderWindow&) = 0;
        virtual void editAmount(int) = 0;
        virtual void update() = 0;

        virtual double getID()                  { return ID; }
        virtual int getAmount()                 { return amount; }
        virtual bool isDisposable()             { return disposable; }
        virtual bool isEquipable()              { return equipable; }
        virtual sf::String getName()            { return name; }
        virtual sf::String getDescription()     { return description; }
        virtual sf::Texture getSkin()           { return skin; }
        virtual sf::VertexArray getBody()       { return body; }
    };

    class Discoverable {
      protected:
          bool discovered;
      public:
        virtual ~Discoverable() {}
        virtual void reveal() = 0;
    };

    class Potion;

    class Spell;

    class ColdWeapon;

    class RangedWeapon;

    class Food;

    class Cash;

}

#endif
