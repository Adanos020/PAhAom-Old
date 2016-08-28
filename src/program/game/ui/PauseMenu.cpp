/**
 * @file src/program/game/ui/PauseMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
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
      title_  (Text  (sf::Vector2f(0, 0), "PAhAom"             , Resources::font.Pixel       , 100, sf::Color::Yellow)),
      version_(Text  (sf::Vector2f(0, 0), Program::getVersion(), Resources::font.FinalFantasy,  50, sf::Color::Yellow)),
      wMenu_  (Window("", sf::Vector2f(244, 230), sf::Vector2f(25, Settings::graphics.resolution.y/2-153))            )
    {
        shadow_.setSize((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

        title_  .setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-title_  .getSize().x/2,  10));
        version_.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-version_.getSize().x/2, 100));

        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.resume" ], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.help"   ], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"   ], 52);
        for (int i=0; i<3; i++)
        {
            wMenu_.getComponent<Button>(i)->setPosition(wMenu_.getPosition() + sf::Vector2f(wMenu_.getSize().x/2 - wMenu_.getComponent<Button>(i)->getSize().x/2, 5+i*75));
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
        wMenu_ |= wHelp;
    }

    void
    PauseMenu::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        auto wHelp = wMenu_.getComponent<Window>(0);

        if (wMenu_.isVisible())
        {
            if (!wHelp->isVisible())
            {
                if (  wMenu_.getComponent<Button>(0)->isPressed(rw, e)
                    ) g->pause(false);
                if (  wMenu_.getComponent<Button>(1)->isPressed(rw, e)
                    ) wHelp->setVisible(true);
                if (  wMenu_.getComponent<Button>(2)->isPressed(rw, e))
                {
                    g->save();
                    g->pause(false);
                    g->start(false);
                    close();
                }
            }

            else if (wHelp->isVisible())
            {
                if (  wHelp->getComponent<Button>(0)->isPressed(rw, e)
                    ) wHelp->setVisible(false);
            }
        }
    }

    void
    PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(shadow_ , states);
            target.draw(title_  , states);
            target.draw(version_, states);
            target.draw(wMenu_  , states);
        }
    }

    void
    PauseMenu::close()
    {
        auto wHelp = wMenu_.getComponent<Window>(0);
        wMenu_.setVisible(false);
        wHelp->setVisible(false);
    }

}
