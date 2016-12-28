/**
 * @file src/program/game/ui/Journal.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../../funcs/classes.hpp"

#include "Journal.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Separator.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

extern sf::Color itemColors  [9];
extern int       spellSymbols[12];

namespace rr
{

    Journal::Journal()
    {
        reset();
    }

    void
    Journal::reset()
    {
        m_wJour.clear();

        m_wJour = Window(Resources::dictionary["gui.window.journal"], sf::Vector2f(725, 570),
                         sf::Vector2f(Settings::graphics.resolution.x/2-362.5, Settings::graphics.resolution.y/2-260));

        m_shadow.setSize((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition(sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 128));

        auto separator1 = new Separator(Separator::VERTICAL, 540);
             separator1->setPosition(sf::Vector2f(m_wJour.getSize().x/3, 15));
             
        auto separator2 = new Separator(Separator::VERTICAL, 540);
             separator2->setPosition(sf::Vector2f(2*m_wJour.getSize().x/3, 15));

        std::vector <Image*> images;
        std::vector <Text* > names;
        for (int i = 0; i < 9; ++i)
        {
            images.push_back(new Image(sf::Vector2f(10, 55 + i*55), Resources::texture.items, 16, 2));
            images.back()->scale(sf::Vector2f(0.5f, 0.5f));

            images.push_back(new Image(sf::Vector2f(10, 55 + i*55), Resources::texture.items, 16, 0));
            images.back()->scale(sf::Vector2f(0.5f, 0.5f));

            sf::String name = "";
            switch (i)
            {
                case 0: name = "item.potion.effect.healing";      break;
                case 1: name = "item.potion.effect.magic";        break;
                case 2: name = "item.potion.effect.strength";     break;
                case 3: name = "item.potion.effect.dexterity";    break;
                case 4: name = "item.potion.effect.speed";        break;
                case 5: name = "item.potion.effect.regeneration"; break;
                case 6: name = "item.potion.effect.poison";       break;
                case 7: name = "item.potion.effect.slowness";     break;
                case 8: name = "item.potion.effect.weakness";     break;
            }
            names.push_back(new Text(Resources::dictionary[name], Resources::font.Unifont, 20));
            names.back()->wrap(m_wJour.getSize().x/3 - 50);
            names.back()->setPosition(images.back()->getPosition() + sf::Vector2f(40, images.back()->getSize().y/2 - names.back()->getSize().y/1.75f));
        }

        for (int i = 0; i < 12; ++i)
        {
            images.push_back(new Image(sf::Vector2f(m_wJour.getSize().x/3 + 10, 55 + i*40.5f), Resources::texture.items, 16, 48));
            images.back()->scale(sf::Vector2f(0.5f, 0.5f));

            images.push_back(new Image(sf::Vector2f(m_wJour.getSize().x/3 + 10, 55 + i*40.5f), Resources::texture.items, 16, 0));
            images.back()->scale(sf::Vector2f(0.5f, 0.5f));

            sf::String name = "";
            switch (i)
            {
                case  0: name = "item.spell.type.heal";         break;
                case  1: name = "item.spell.type.firebolt";     break;
                case  2: name = "item.spell.type.lightning";    break;
                case  3: name = "item.spell.type.iceBullet";    break;
                case  4: name = "item.spell.type.teleport";     break;
                case  5: name = "item.spell.type.fireRain";     break;
                case  6: name = "item.spell.type.storm";        break;
                case  7: name = "item.spell.type.iceWave";      break;
                case  8: name = "item.spell.type.timeFreezing"; break;
                case  9: name = "item.spell.type.identify";     break;
                case 10: name = "item.spell.type.uncurse";      break;
                case 11: name = "item.spell.type.telekinesis";  break;
            }
            names.push_back(new Text(Resources::dictionary[name], Resources::font.Unifont, 20));
            names.back()->wrap(m_wJour.getSize().x/3 - 50);
            names.back()->setPosition(images.back()->getPosition() + sf::Vector2f(40, images.back()->getSize().y/2 - names.back()->getSize().y/1.75f));
        }

        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(m_wJour.getSize().x - bQuit->getSize().x - 15,
                                             m_wJour.getSize().y - bQuit->getSize().y - 5));

        auto tCreativity = new Text("CREATIVITY", Resources::font.Unifont);
             tCreativity->setPosition(sf::Vector2f(20, 15));

        auto tAction = new Text("ACTION", Resources::font.Unifont);
             tAction->setPosition(sf::Vector2f(20, 0) + separator1->getPosition());

        auto tService = new Text("SERVICE", Resources::font.Unifont);
             tService->setPosition(sf::Vector2f(20, 0) + separator2->getPosition());

        ((m_wJour += tCreativity) += tAction) += tService;
        ((m_wJour += bQuit) += separator1) += separator2;
        for (unsigned i = 0; i < images.size(); ++i)
        {
            m_wJour += images[i];
        }
        for (unsigned i = 0; i < names.size(); ++i)
        {
            m_wJour += names[i];
        }
    }

    void
    Journal::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        if (m_wJour.isVisible())
        {
            if (m_wJour.getComponent <Button> (0)->isPressed(rw, e))
                g->pause(false);
        }
    }

    void
    Journal::onNotify(Observer::Event event, Entity* entity, sf::String)
    {
        switch (event)
        {
            case ITEM_DISCOVERED:
            {
                if (instanceof <Item, Entity> (entity))
                {
                    if (instanceof <Potion, Item> ((Item*) entity))
                    {
                        auto img = m_wJour.getComponent <Image> (2 * ((Potion*) entity)->getType() + 1);

                        img->setIconIndex(18);
                        img->paint(itemColors[((Potion*) entity)->getType()]);
                    }
                    else if (instanceof <Rune, Item> ((Item*) entity))
                    {
                        auto img = m_wJour.getComponent <Image> (2 * ((Rune*) entity)->getType() + 19);

                        img->setIconIndex(64 + spellSymbols[((Rune*) entity)->getType()]);
                    }
                }
            }

            default: break;
        }
    }

    void
    Journal::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(m_shadow, states);
            target.draw(m_wJour , states);
        }
    }

}
