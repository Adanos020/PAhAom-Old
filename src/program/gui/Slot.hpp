/**
 * @file src/program/gui/Slot.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef GUI_SLOT_HPP
#define GUI_SLOT_HPP

#include "Component.hpp"
#include "Image.hpp"
#include "Text.hpp"

#include "../game/entity/Item.hpp"

namespace rr
{

    class Slot : public Component
    {
    private: sf::RectangleShape m_body;
             Image              m_image;
             Text               m_text;
             Item*              m_item;
             bool               m_hollow;
             bool               m_held;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the slot on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Slot(sf::Vector2f size, sf::Vector2f pos, int icon = 0);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Slot();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an item to the slot.
             ////////////////////////////////////////////////////////////////////////
             bool addItem(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes a given amount of the item from the slot.
             ////////////////////////////////////////////////////////////////////////
             void removeItem(int, bool deleteFromMemory = true);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes the item from the slot.
             ////////////////////////////////////////////////////////////////////////
             void removeItem(bool deleteFromMemory = true);
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Swaps the items between the slots.
             ////////////////////////////////////////////////////////////////////////
             void swapItems(Slot*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Clears the slot.
             ////////////////////////////////////////////////////////////////////////
             void clear();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the slot's body's position.
             ////////////////////////////////////////////////////////////////////////
             void setPosition(sf::Vector2f) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the slot's body's position.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getPosition() const override { return m_body.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the slot's body's size.
             ////////////////////////////////////////////////////////////////////////
             void setSize(sf::Vector2f size) override { m_body.setSize(size); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the slot's body's size.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2f getSize() const override { return m_body.getSize(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the string of the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             void setText(sf::String s) { m_text.setString(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the text displayed on the scroll bar.
             ////////////////////////////////////////////////////////////////////////
             Text getText() const { return m_text; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the slot is touched by a mouse cursor.
             ////////////////////////////////////////////////////////////////////////
             bool containsMouseCursor(sf::RenderWindow&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the slot is clicked.
             ////////////////////////////////////////////////////////////////////////
             bool isPressed(sf::RenderWindow&, sf::Event&, sf::Mouse::Button = sf::Mouse::Left);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the slot is being held.
             ////////////////////////////////////////////////////////////////////////
             bool isHeld() const { return m_held; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the item contained in the slot.
             ////////////////////////////////////////////////////////////////////////
             Item* getItem() const;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Method telling if the slot is empty.
             ////////////////////////////////////////////////////////////////////////
             bool isEmpty() const { return m_hollow; }
    };

}

#endif // GUI_SLOT_HPP
