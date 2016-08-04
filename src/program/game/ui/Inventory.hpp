/**
 * @file src/program/game/ui/BookOfSpells.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_INVENTORY_HPP
#define UI_INVENTORY_HPP

#include <SFML/Graphics.hpp>

#include "../../observer/Observer.hpp"

#include "../../gui/Window.hpp"
#include "../../gui/Slot.hpp"

#include "../entity/Entity.hpp"
#include "../entity/Player.hpp"

namespace rr {

    class Game;

/// Class for the player inventory
    class Inventory : public Observer, public sf::Drawable {
    private: sf::RectangleShape shadow_;
     
             Window             wInve_;
             Slot*              sCarryOn_[5];
             Player*            player_;
         
             short              bronze_;
             short              silver_;
             short              gold_;
         
             void sort();

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:  Inventory(Player*);
            ~Inventory();
         
         /// Adds an item to the inventory
             bool addItem     (Item*);
         /// Tells if there is such an item in the inventory
             bool contains    (Item*);
         /// Clears the inventory
             void clear       ();
         /// Handles the button events
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);
         /// Opens the inventory window
             void open        ();
         /// Closes the inventory window
             void close       ();
         /// Tells if the inventory is open
             bool isOpen      () const { return wInve_.isVisible(); }
         
             std::ifstream& operator<<(std::ifstream&);
             std::ofstream& operator>>(std::ofstream&);
         
             virtual void onNotify(Event, Entity*) override;
    };

}

#include "../Game.hpp"

#endif // UI_INVENTORY_HPP