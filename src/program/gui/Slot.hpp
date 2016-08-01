/**
 * @file src/program/gui/Slot.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_SLOT_HPP
#define GUI_SLOT_HPP

#include "Component.hpp"
#include "Image.hpp"
#include "Text.hpp"

#include "../game/entity/item/Item.hpp"

namespace rr {

/// Class for a slot component which can contain any instance of the class Item
    class Slot : public Component {
    private: sf::RectangleShape body_;
             Image              image_;
             Item*              item_;
             Text               text_;
             bool               hollow_;
             bool               held_;

             virtual void draw        (sf::RenderTarget&,
                                       sf::RenderStates) const override;

    public:  Slot(sf::Vector2f size, sf::Vector2f pos, int icon = 0);
            ~Slot();

         /// Adds an item to the slot
             bool         addItem            (Item*);
         /// Removes the item from the slot
             void         removeItem         (int, bool deleteFromMemory = true);
             void         removeItem         (bool deleteFromMemory = true);
         /// Swaps the items between the slots
             void         swapItems          (Slot*);
         /// Clears the slot
             void         clear              ();

             void         setText            (sf::String s)               { text_.setString(s); }
             void         setPosition        (sf::Vector2f)      override;
             void         setSize            (sf::Vector2f size) override { body_.setSize(size); }

             bool         containsMouseCursor(sf::RenderWindow&);
             bool         isPressed          (sf::RenderWindow&, sf::Event&, sf::Mouse::Button = sf::Mouse::Left);
             bool         isHeld             () const                     { return held_; }
             Text         getText            () const                     { return text_; }
             sf::Vector2f getPosition        () const            override { return body_.getPosition(); }
             sf::Vector2f getSize            () const            override { return body_.getSize(); }

         /// Returns the item contained in the slot
             Item*        getItem            () const                     { if ( !hollow_
                                                                                ) return item_;
                                                                            return nullptr;
                                                                          }
         /// Method telling if the slot is empty
             bool         isEmpty            () const                     { return hollow_; }
    };

}

#endif // GUI_SLOT_HPP
