/**
 * @file src/program/game/menu/BookOfSpells.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef MENU_INVENTORY_HPP
#define MENU_INVENTORY_HPP

#include <SFML/Graphics.hpp>

#include "../Game.hpp"
#include "../../observer/Observer.hpp"

#include "../../gui/Window.hpp"
#include "../../gui/Slot.hpp"

#include "../entity/Entity.hpp"
#include "../entity/Player.hpp"

namespace rr {

    class Game;

/// Class for the player inventory
    class Inventory : public Observer {
    private: sf::RectangleShape shadow_;
     
             Window             wInve_;
             Slot*              sCarryOn_[5];
             Player*            player_;
         
             short              bronze_;
             short              silver_;
             short              gold_;
         
             void sort();
    
    public:  Inventory(Player*);
            ~Inventory();
         
         /// Adds an item to the inventory
             bool addItem     (Item*);
         /// Tells if there is such an item in the inventory
             bool contains    (Item*);
         /// Opens the inventory window
             void open        ();
         /// Closes the inventory window
             void close       ();
         /// Clears the inventory
             void clear       ();
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Draws the inventory components
             void draw        (sf::RenderWindow&);
         /// Tells if the inventory is open
             bool isOpen      ();
         
             std::ifstream& operator<<(std::ifstream&);
             std::ofstream& operator>>(std::ofstream&);
         
             virtual void onNotify(Event, Entity*) override;
    };

}

#endif
