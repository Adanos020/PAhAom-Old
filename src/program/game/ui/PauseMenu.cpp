/**
 * @file src/program/game/ui/PauseMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "PauseMenu.hpp"

#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"
#include "../../Program.hpp"

#include "../../funcs/strings.hpp"

namespace rr
{

    PauseMenu::PauseMenu() :
      m_title  (Text  (sf::Vector2f(0, 0), "PAhAom"             , Resources::font.Pixel       , 100, sf::Color::Yellow)),
      m_version(Text  (sf::Vector2f(0, 0), Program::getVersion(), Resources::font.FinalFantasy,  50, sf::Color::Yellow)),
      m_wMenu  (Window("", sf::Vector2f(244, 230), sf::Vector2f(25, Settings::graphics.resolution.y/2-153))            )
    {
        m_shadow.setSize((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition(sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 172));

        m_title  .setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-m_title  .getSize().x/2,  10));
        m_version.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-m_version.getSize().x/2, 100));

        m_wMenu += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.resume" ], 52);
        m_wMenu += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.help"   ], 52);
        m_wMenu += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"   ], 52);
        for (int i = 0; i < 3; i++)
        {
            m_wMenu.getComponent <Button> (i)->setPosition(m_wMenu.getPosition() + sf::Vector2f(m_wMenu.getSize().x/2 - m_wMenu.getComponent <Button> (i)->getSize().x/2,
                                                        5 + i*75));
        }

        auto wHelp = new Window(Resources::dictionary["gui.button.help"], sf::Vector2f(325, 454), sf::Vector2f(Settings::graphics.resolution.x   - 350,
                                                                                                               Settings::graphics.resolution.y/2 - 225));
        {
            *wHelp += new Text(sf::Vector2f(20, 25), "Pro tip:",                                  Resources::font.Unifont, 30, sf::Color::Yellow);
            *wHelp += new Text(sf::Vector2f(20, 55), Resources::dictionary["gui.text.killurslf"], Resources::font.Unifont, 30, sf::Color::Red);

            auto bQuit = new Button(sf::Vector2f(5, 380), Resources::dictionary["gui.button.quit"], 30);
            bQuit->setPosition(sf::Vector2f(wHelp->getSize().x/2 - bQuit->getSize().x/2,
                                            wHelp->getSize().y   - bQuit->getSize().y-10));

            *wHelp += bQuit;
        }
        m_wMenu |= wHelp;
    }

    void
    PauseMenu::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        auto wHelp = m_wMenu.getComponent <Window> (0);

        if (m_wMenu.isVisible())
        {
            if (!wHelp->isVisible())
            {
                if (m_wMenu.getComponent <Button> (0)->isPressed(rw, e)) g->pause(false);
                if (m_wMenu.getComponent <Button> (1)->isPressed(rw, e)) wHelp->setVisible(true);
                if (m_wMenu.getComponent <Button> (2)->isPressed(rw, e))
                {
                    g->save();
                    g->pause(false);
                    g->start(false);
                    close();
                }
            }

            else if (wHelp->isVisible())
            {
                if (wHelp->getComponent <Button> (0)->isPressed(rw, e))
                    wHelp->setVisible(false);
            }
        }
    }

    void
    PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(m_shadow , states);
            target.draw(m_title  , states);
            target.draw(m_version, states);
            target.draw(m_wMenu  , states);
        }
    }

    void
    PauseMenu::close()
    {
        auto wHelp = m_wMenu.getComponent <Window> (0);
        m_wMenu.setVisible(false);
        wHelp->setVisible(false);
    }

}
