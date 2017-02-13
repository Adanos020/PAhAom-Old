/**
 * @file src/program/game/ui/Inventory.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Inventory.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Image.hpp"
#include "../../gui/Menu.hpp"
#include "../../gui/Text.hpp"

#include "../../Resources.hpp"
#include "../../Settings.hpp"

#include "../../funcs/files.hpp"

extern rr::Subject subject;

namespace rr
{

    Inventory::Inventory(Player* p) :
      m_player(p),
      m_bronze(0),
      m_silver(0),
      m_gold  (0)
    {
        reset();
    }

    void
    Inventory::reset()
    {
        m_wInve.clear();

        m_wInve = Window(Resources::dictionary["gui.window.inventory"], sf::Vector2f(765, 470),
                         (sf::Vector2f) (Settings::graphics.resolution / 2u - sf::Vector2u(382, 225)));

        m_shadow.setSize((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition(sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 172));

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                m_wInve += new Slot(sf::Vector2f(80, 80), sf::Vector2f(10 + j*95, 30 + i*95));
            }
        }

        m_wInve += new Image(sf::Vector2f(0  , 390), Resources::texture.items, 16, 33);
        m_wInve += new Image(sf::Vector2f(150, 390), Resources::texture.items, 16, 34);
        m_wInve += new Image(sf::Vector2f(300, 390), Resources::texture.items, 16, 35);

        m_wInve += new Text(sf::Vector2f(70 , 415), "GOLD", Resources::font.Pixel, 30);
        m_wInve += new Text(sf::Vector2f(220, 415), "SILV", Resources::font.Pixel, 30);
        m_wInve += new Text(sf::Vector2f(370, 415), "BRON", Resources::font.Pixel, 30);

        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(m_wInve.getSize().x - bQuit->getSize().x - 15, 
                                             m_wInve.getSize().y - bQuit->getSize().y -  5));

        auto wInfo = new Window("", sf::Vector2f(410, 40), sf::Vector2f(0, 0));
        {
            auto tDescription = new Text(sf::Vector2f(5, 20), "", Resources::font.Unifont, 20);
                 tDescription->setStyle(sf::Text::Regular);
                 tDescription->setOutlineColor(sf::Color(0x40, 0x40, 0x40));
            *wInfo += tDescription;
        }
        auto wOpts = new Window("", sf::Vector2f(142, 143), sf::Vector2f(0, 0));
        {
             auto mOpts = new Menu(sf::Vector2f(5, 25));
                  mOpts->addOption(Resources::dictionary["gui.menu.use"            ]);
                  mOpts->addOption(Resources::dictionary["gui.menu.move_to_carryon"]);
                  mOpts->addOption(Resources::dictionary["gui.menu.drop"           ]);
             *wOpts += mOpts;
        }

        ((m_wInve |= wInfo) |= wOpts) += bQuit;

        for (int i = 0; i < 5; ++i)
        {
            m_sHotbar[i] = new Slot(sf::Vector2f(80, 80),
                                    sf::Vector2f(Settings::graphics.resolution.x / 2 - 250 + i * 95, 10));
        }
    }

    Inventory::~Inventory()
    {
        for (auto slot : m_sHotbar)
        {
            delete slot;
        }
    }

    void
    Inventory::clear()
    {
        for (int i = 0; i < 32; ++i)
        {
            m_wInve.getComponent <Slot> (i)->clear();
        }
        for (auto slot : m_sHotbar)
        {
            slot->clear();
        }
        m_gold   = 0;
        m_silver = 0;
        m_bronze = 0;
    }

    void
    Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* game)
    {

#define component(w, c, i) w.getComponent<c>(i)
#define wInfo (*component(m_wInve, Window, 0))
#define wOpts (*component(m_wInve, Window, 1))
;
        if (m_wInve.isVisible())
        {
            if (wOpts.isVisible()) // ITEM OPTIONS WINDOW IS OPEN
            {
                sf::String chosenOption = component(wOpts, Menu, 0)->getChosenOption(rw, e);
                if (chosenOption == Resources::dictionary["gui.menu.use"])
                {
                    Item* item = ((Slot*) wOpts.getParentComponent())->getItem();

                    if (instanceof <Equipable, Item> (item))
                    {
                        bool equip = !((Equipable*) item)->isEquipped();

                        if (m_player->equipItem((Equipable*) item, equip))
                            ((Equipable*) item)->equip(equip);

                        if (instanceof <MeleeWeapon, Item> (item))
                        {
                            for (int i = 0; i < 32; ++i)
                            {
                                if (instanceof <MeleeWeapon, Item> (component(m_wInve, Slot, i)->getItem()))
                                {
                                    ((Equipable*) component(m_wInve, Slot, i)->getItem())->equip(false);
                                }
                            }
                        }
                    }
                    else
                    {
                        game->getPlayer()->useItem(item);
                        if (item->isDisposable())
                        {
                            ((Slot*) wOpts.getParentComponent())->removeItem(1);
                            sort();
                        }
                    }
                }
                else if (chosenOption == Resources::dictionary["gui.menu.drop"])
                {
                    Item* item = ((Slot*) wOpts.getParentComponent())->getItem();
                    item->setGridPosition(m_player->getGridPosition());

                    if (instanceof <Equipable, Item> (item) && ((Equipable*) item)->isEquipped())
                        ((Equipable*) item)->equip(false);

                    subject.notify(Observer::ITEM_DROPPED, item);

                    ((Slot*) wOpts.getParentComponent())->removeItem(false);
                    sort();
                }
                else if (chosenOption == Resources::dictionary["gui.menu.to_carryon"])
                {

                }

                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button != sf::Mouse::Middle)
                {
                    wOpts.setParentComponent(nullptr);
                    wOpts.setVisible(false);
                }
            }
            else // ITEM OPTIONS WINDOW IS NOT OPEN
            {
                if (component(m_wInve, Button, 0)->isPressed(rw, e))
                    game->pause(false);

                bool slotPointed = false;
                /* BACKPACK */
                for (int i = 0; i < 32; ++i)
                {
                    if (component(m_wInve, Slot, i)->containsMouseCursor(rw) && !component(m_wInve, Slot, i)->isEmpty())
                    {
                        // SLOT WAS LEFT-CLICKED
                        if (component(m_wInve, Slot, i)->isPressed(rw, e) && !component(m_wInve, Slot, i)->isEmpty())
                        {
                            if (instanceof <Equipable, Item> (component(m_wInve, Slot, i)->getItem()))
                            {
                                bool equip = !((Equipable*)component(m_wInve, Slot, i)->getItem())->isEquipped(); 
                                
                                if (m_player->equipItem((Equipable*) component(m_wInve, Slot, i)->getItem(), equip))
                                    ((Equipable*)component(m_wInve, Slot, i)->getItem())->equip(equip);

                                if (instanceof <MeleeWeapon, Item> (component(m_wInve, Slot, i)->getItem()))
                                {
                                    for (int j = 0; j < 32; ++j)
                                    {
                                        if (j != i && instanceof <MeleeWeapon, Item> (component(m_wInve, Slot, j)->getItem()))
                                        {
                                            ((Equipable*) component(m_wInve, Slot, j)->getItem())->equip(false);
                                        }
                                    }
                                }

                                if (instanceof <RangedWeapon, Item> (component(m_wInve, Slot, i)->getItem()))
                                {
                                    for (int j = 0; j < 32; ++j)
                                    {
                                        if (j != i && instanceof <RangedWeapon, Item> (component(m_wInve, Slot, j)->getItem()))
                                        {
                                            ((Equipable*) component(m_wInve, Slot, j)->getItem())->equip(false);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                game->getPlayer()->useItem(component(m_wInve, Slot, i)->getItem());
                                if (component(m_wInve, Slot, i)->getItem()->isDisposable())
                                {
                                    component(m_wInve, Slot, i)->removeItem(1);
                                    sort();
                                }
                            }
                        }
                        // SLOT WAS RIGHT-CLICKED
                        else if (component(m_wInve, Slot, i)->isPressed(rw, e, sf::Mouse::Right) && !component(m_wInve, Slot, i)->isEmpty())
                        {
                            wOpts.setPosition(component(m_wInve, Slot, i)->getPosition()
                                             +component(m_wInve, Slot, i)->getSize());

                            if (wOpts.getParentComponent() != component(m_wInve, Slot, i))
                            {
                                wOpts.setParentComponent(component(m_wInve, Slot, i));

                                Item* item = ((Slot*)wOpts.getParentComponent())->getItem();

                                if      (instanceof <Equipable, Item> (item)) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.equip"]);
                                else if (instanceof <Potion   , Item> (item)) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.drink"]);
                                else if (instanceof <Food     , Item> (item)) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.eat"  ]);
                                else if (instanceof <Book     , Item> (item)) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.read" ]);
                                else                                        component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.use"  ]);

                                wOpts.setHeader(item->getName());
                                if (wOpts.getHeader().getSize().x+10 >= 142)
                                    wOpts.setSize(sf::Vector2f(wOpts.getHeader().getSize().x+10, 143));
                                else
                                    wOpts.setSize(sf::Vector2f(142, 143));
                                wOpts.setVisible(true);
                            }
                            else
                            {
                                wOpts.setParentComponent(nullptr);
                                wOpts.setVisible(false);
                            }
                        }
                        else
                        {
                            wInfo.setParentComponent(component(m_wInve, Slot, i));
                            slotPointed = true;
                        }
                    }
                }
                /* CARRY-ON */
                for (int i = 0; i < 5; ++i)
                {
                    if (m_sHotbar[i]->containsMouseCursor(rw) && !m_sHotbar[i]->isEmpty())
                    {
                        if (m_sHotbar[i]->isPressed(rw, e) && !m_sHotbar[i]->isEmpty())
                        {
                            game->getPlayer()->useItem(m_sHotbar[i]->getItem());
                            if (m_sHotbar[i]->getItem()->isDisposable())
                            {
                                m_sHotbar[i]->removeItem(1);
                                sort();
                            }
                        }
                        else
                        {
                            wInfo.setParentComponent(m_sHotbar[i]);
                            slotPointed = true;
                        }
                    }
                }

                // HANDLING THE ITEM INFO WINDOW
                if (!wOpts.isVisible() && slotPointed)
                {
                    component(wInfo, Text, 0)->setString(((Slot*) wInfo.getParentComponent())->getItem()->getDescription());
                    component(wInfo, Text, 0)->wrap     ((wInfo.getHeader().getSize().x >= 300.f) ? wInfo.getHeader().getSize().x + 10 : 300.f);

                    wInfo.setHeader(((Slot*) wInfo.getParentComponent())->getItem()->getName());
                    if (wInfo.getHeader().getSize().x > component(wInfo, Text, 0)->getSize().x)
                    {
                        wInfo.setSize(wInfo.getHeader().getSize() + sf::Vector2f(10, 10 + component(wInfo, Text, 0)->getSize().y));
                    }
                    else
                    {
                        wInfo.setSize(component(wInfo, Text, 0)->getSize() + sf::Vector2f(10, 30));
                    }
                    wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw) + sf::Vector2f(5, 5));

                    if (wInfo.getPosition().x+wInfo.getSize().x+5 > (float) rw.getSize().x)
                        wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw)
                                          -sf::Vector2f(wInfo.getPosition().x + wInfo.getSize().x - (float) rw.getSize().x, -5));
                                            
                    if (wInfo.getPosition().y+wInfo.getSize().y+5 > (float) rw.getSize().y)
                        wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw)
                                          -sf::Vector2f(-5, wInfo.getPosition().y + wInfo.getSize().y - (float) rw.getSize().y));

                    wInfo.setVisible(true);
                }
                else
                    wInfo.setVisible(false);
            }
        }

#undef component
#undef wInfo
#undef wOpts

    }

    bool
    Inventory::addItem(Item* item)
    {
        if (item == nullptr)
            return false;

#define slot(i) m_wInve.getComponent <Slot> (i)

     // in the beginning we check if the picked item is a coin
        if (instanceof <Coin, Item> (item))
        {
         // first we recognize the coin type and size
            if (((Coin*)item)->getType() == Coin::BRONZE)
            {
                if (((Coin*)item)->getSize() == Coin::BIG)
                    m_bronze += item->getAmount()*5;
                else
                    m_bronze += item->getAmount();
            }
            else if (((Coin*)item)->getType() == Coin::SILVER)
            {
                if (((Coin*)item)->getSize() == Coin::BIG)
                    m_silver += item->getAmount()*5;
                else
                    m_silver += item->getAmount();
            }
            else if (((Coin*)item)->getType() == Coin::GOLDEN)
            {
                if (((Coin*)item)->getSize() == Coin::BIG)
                    m_gold += item->getAmount()*5;
                else
                    m_gold += item->getAmount();
            }

         // then we do the simple calculations: 1 gold = 100 silver, 1 silver = 100 bronze
            while (m_bronze >= 50)
            {
                m_bronze -= 50;
                m_silver++;
            }
            while (m_silver >= 50)
            {
                m_silver -= 50;
                m_gold++;
            }

         // and in the end we can just:
            return true;
        }

     // if the item we want to add is stackable then we check if any of the slots already contains it
        if (item->isStackable())
        {
            for (int i = 0; i < 32; ++i)
            {
                if (!slot(i)->isEmpty() && slot(i)->getItem()->getID() == item->getID())
                {
                    bool success = slot(i)->addItem(item);
                    sort();
                    return success;
                }
            }
        }

     // if not then we look for the first empty slot and add the item to it
        for (int i = 0; i < 32; ++i)
        {
            if (slot(i)->isEmpty())
            {
                bool success = slot(i)->addItem(item);
                sort();
                return success;
            }
        }

     // and if there is no empty slot, we just exit the function
        return false;
    }

    void
    Inventory::removeItem(Item* item, int amount)
    {
        if (instanceof <Coin, Item> (item))
        {
            auto coin = (Coin*) item;
            switch (coin->getType())
            {
                case Coin::GOLDEN: if (amount == 0)
                                       m_gold   = 0;
                                   else
                                       m_gold  -= amount;
                                   break;

                case Coin::SILVER: if (amount  == 0)
                                       m_silver  = 0;
                                   else
                                       m_silver -= amount;
                                   break;

                case Coin::BRONZE: if (amount  == 0)
                                       m_bronze  = 0;
                                   else
                                       m_bronze -= amount;
                                   break;
            }
        }
        else
        {
            for (int i = 0; i < 32; ++i)
            {
                if (!slot(i)->isEmpty() && slot(i)->getItem()->getID() == item->getID())
                {
                    if (amount == 0)
                        slot(i)->removeItem();
                    else
                        slot(i)->removeItem(amount);
                }
            }
        }
    }

    void
    Inventory::sort()
    {
        // just a simple bubble sort algorithm, there is no need for something
        // complex while there are so few elements to sort
        for (int i = 0; i < 31; ++i)
        {
            for (int j = 1; j < 32; ++j)
            {
                if ( (!slot(j-1)->isEmpty() && slot(j)->isEmpty())
                   ||( slot(j-1)->isEmpty() && slot(j)->isEmpty())
                    ) continue;
                if ( (slot(j-1)->isEmpty() && !slot(j)->isEmpty())
                   ||(slot(j-1)->getItem()->getID() > slot(j)->getItem()->getID())
                    ) slot(j-1)->swapItems(slot(j));
            }
        }
    }

    bool
    Inventory::contains(Item* sought)
    {
        for (int i = 0; i < 32; ++i)
        {
            if (!slot(i)->isEmpty() && slot(i)->getItem()->getID() == sought->getID())
                return true;
        }
        return false;
    }

    void
    Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(m_shadow, states);
            target.draw(m_wInve , states);
        }
        for (auto slot : m_sHotbar)
        {
            target.draw(*slot  , states);
        }
    }

    void Inventory::open()
    {
        m_wInve.getComponent <Text> (0)->setString(std::to_string((int) m_gold));
        m_wInve.getComponent <Text> (1)->setString(std::to_string((int) m_silver));
        m_wInve.getComponent <Text> (2)->setString(std::to_string((int) m_bronze));

        m_wInve.setVisible(true);
    }

    void Inventory::close()
    {
        m_wInve.getComponent <Window> (1)->setVisible(false);
        m_wInve.getComponent <Window> (1)->setParentComponent(nullptr);
        m_wInve.setVisible(false);
    }

    std::ifstream&
    Inventory::operator<<(std::ifstream& file)
    {
        try
        {
            readFile <short> (file, m_bronze);
            readFile <short> (file, m_silver);
            readFile <short> (file, m_gold);

            int itemsNumber;
            readFile <int> (file, itemsNumber);

            for (int i = 0; i < itemsNumber; ++i)
            {
                int itemType;
                readFile <int> (file, itemType);
                
                Item* item = nullptr;
                switch (itemType)
                {
                    case 0: item = new Ammunition  (); readEntity(file, item); break;
                    case 1: item = new Book        (); readEntity(file, item); break;
                    case 2: item = new Coin        (); readEntity(file, item); break;
                    case 3: item = new MeleeWeapon (); readEntity(file, item); break;
                    case 4: item = new Food        (); readEntity(file, item); break;
                    case 5: item = new Potion      (); readEntity(file, item); break;
                    case 6: item = new RangedWeapon(); readEntity(file, item); break;
                    case 7: item = new Rune        (); readEntity(file, item); break;
                }
                addItem(item);
            }
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream&
    Inventory::operator>>(std::ofstream& file)
    {
        file << m_bronze << ' '
             << m_silver << ' '
             << m_gold   << '\n';

        for (int i = 0; i < 32; ++i)
        {
            if (slot(i)->isEmpty())
            {
                file << i << '\n';
                break;
            }
        }

        for (int i = 0; i < 32; ++i)
        {
            if (slot(i)->isEmpty())
                break;
            *slot(i)->getItem() >> file << '\n';
        }

        return file;
    }

    void Inventory::onNotify(Event event, Entity* entity, sf::String)
    {
        switch (event)
        {
            default: break;
        }

#undef slot

    }

}
