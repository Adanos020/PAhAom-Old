/**
 * @file src/program/gui/Slot.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Slot.hpp"

#include "../funcs/items.hpp"
#include "../funcs/classes.hpp"

#include "../Resources.hpp"

namespace rr
{

    Slot::Slot(sf::Vector2f size, sf::Vector2f pos, int icon) :
      m_image (Image(pos, Resources::texture.gui, 14, icon)),
      m_text  (Text (sf::Vector2f(pos.x+5, pos.y+55), "", Resources::font.Pixel, 20)),
      m_item  (nullptr),
      m_hollow(true)
    {
        m_body.setSize            (size);
        m_body.setPosition        (pos);
        m_body.setFillColor       (sf::Color(110, 110, 110, 128));
        m_body.setOutlineColor    (sf::Color(130, 130, 130));
        m_body.setOutlineThickness(5);

        m_image.setParentComponent (this);
        m_text .setParentComponent (this);
    }

    Slot::~Slot()
    {
        if (!m_hollow)
            delete m_item;
    }

    void
    Slot::setPosition(sf::Vector2f pos)
    {
        m_body .setPosition(pos);
        m_image.setPosition(pos);
        m_text .setPosition(sf::Vector2f(pos.x+5, pos.y+55));
    }

    void
    Slot::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_body, states);

        if (m_hollow)
            target.draw(m_image, states);
        else
        {
            target.draw(*m_item, states);
            if (m_item->getAmount() > 1)
                target.draw(m_text, states);
        }
    }

    bool
    Slot::addItem(Item* item)
    {
        if (!m_hollow)
        {
            if (item->getID() == m_item->getID())
            {
                m_item->setAmount(m_item->getAmount()+item->getAmount());
                m_text.setString(std::to_wstring(m_item->getAmount()));
                return true;
            }
            return false;
        }
        m_item = getItemFromID(item->getID(), item->getAmount());

        if (instanceof<Discoverable, Item>(item) && ((Discoverable*) item)->isDiscovered())
            ((Discoverable*) m_item)->reveal();

        if (instanceof<Equipable, Item>(item))
            ((Equipable*) m_item)->equip(((Equipable*) item)->isEquipped());

        m_item->setPosition(m_body.getPosition());
        m_text.setString(std::to_string(m_item->getAmount()));

        m_hollow = false;
        return true;
    }

    void
    Slot::removeItem(int x, bool deleteFromMemory)
    {
        if (!m_hollow)
        {
            m_item->setAmount(m_item->getAmount()-x);
            m_text.setString(std::to_string(m_item->getAmount()));
            m_text.setCharacterSize(20);

            if (m_item->getAmount() == 0)
            {
                m_hollow = true;
                if (deleteFromMemory)
                    delete m_item;
                m_item = nullptr;
            }
        }
    }

    void
    Slot::removeItem(bool deleteFromMemory)
    {
        m_hollow = true;
        if (deleteFromMemory)
            delete m_item;
        m_item = nullptr;
    }

    void
    Slot::swapItems(Slot* slot)
    {
        Item* temp = m_item;
        m_item = slot->m_item;
        slot->m_item = temp ;
        
        if (m_hollow && !slot->m_hollow)
        {
                  m_hollow = false;
            slot->m_hollow = true;

            m_item->setPosition(m_body.getPosition());

            m_text.setString(std::to_string(m_item->getAmount()));
            m_text.setCharacterSize(20);
        }
        else if (!m_hollow && slot->m_hollow)
        {
                  m_hollow = true;
            slot->m_hollow = false;

            slot->m_item->setPosition(slot->m_body.getPosition());

            slot->m_text.setString(std::to_string(slot->m_item->getAmount()));
            slot->m_text.setCharacterSize(20);
        }
        else if (!m_hollow && !slot->m_hollow)
        {
                  m_item->setPosition(      m_body.getPosition());
            slot->m_item->setPosition(slot->m_body.getPosition());

                  m_text.setString(std::to_string(      m_item->getAmount()));
            slot->m_text.setString(std::to_string(slot->m_item->getAmount()));
                  m_text.setCharacterSize(20);
            slot->m_text.setCharacterSize(20);
        }
    }

    void
    Slot::clear()
    {
        if (!m_hollow)
        {
            m_hollow = true;
            delete m_item;
        }
    }

    bool
    Slot::containsMouseCursor(sf::RenderWindow& rw)
    {
        if (  !m_hollow
           && instanceof<Equipable, Item>(m_item)
           && ((Equipable*) m_item)->isEquipped()
            ) m_body.setOutlineColor(sf::Color(128, 128, 180));
        else  m_body.setOutlineColor(sf::Color(130, 130, 130));

        if (m_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw)))
        {
            m_body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        m_body.setFillColor(sf::Color(128, 128, 128, 128));
        
        return false;
    }

    bool
    Slot::isPressed(sf::RenderWindow& rw, sf::Event& e, sf::Mouse::Button button)
    {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == button)
        {
            m_held = true;
            return true;
        }
        if (e.type == sf::Event::MouseButtonReleased)
            m_held = false;
        return false;
    }

    Item*
    Slot::getItem() const
    {
        if (!m_hollow)
            return m_item;
        return nullptr;
    }

}
