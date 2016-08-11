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

    class Inventory : public Observer, public sf::Drawable {
    private: sf::RectangleShape shadow_;

             Window             wInve_;
             Slot*              sCarryOn_[5];
             Player*            player_;

             short              bronze_;
             short              silver_;
             short              gold_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sorts the items in the backpack.
             ////////////////////////////////////////////////////////////////////////
             void sort();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Inventory(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
             ~Inventory();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reacts to a specific event. It can either do something with
             /// a given entity or just ignore it.
             ////////////////////////////////////////////////////////////////////////
     virtual void onNotify(Event, Entity*) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an item to the inventory.
             ////////////////////////////////////////////////////////////////////////
             bool addItem(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if there is such an item in the inventory.
             ////////////////////////////////////////////////////////////////////////
             bool contains(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Clears the inventory.
             ////////////////////////////////////////////////////////////////////////
             void clear();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the inventory window.
             ////////////////////////////////////////////////////////////////////////
             void open();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the inventory window.
             ////////////////////////////////////////////////////////////////////////
             void close();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the inventory is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return wInve_.isVisible(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the inventory from a file.
             ////////////////////////////////////////////////////////////////////////
             std::ifstream& operator<<(std::ifstream&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the inventory to a file.
             ////////////////////////////////////////////////////////////////////////
             std::ofstream& operator>>(std::ofstream&);
    };

}

#include "../Game.hpp"

#endif // UI_INVENTORY_HPP
