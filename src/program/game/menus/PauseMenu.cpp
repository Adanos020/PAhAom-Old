/**
 * @file src/program/game/menus/PauseMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "menus.h"
#include <iostream>

extern std::map<std::string, sf::String> dictionary;
extern rr::Settings settings;
extern sf::Font font_Unifont;
extern sf::Font font_Pixel;

namespace rr {

    PauseMenu::PauseMenu(sf::RenderWindow& rw) {
        #define dict(s) dictionary[s]
        #define component(w, c, i) w->getComponent<c>(i)

        title = new Text(nullptr, sf::Vector2f(0, 0), L"PAhAom", font_Pixel, 100, sf::Color::Yellow);
            title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        if (settings.language=="fc")
            wMenu = new Window(nullptr, L"", sf::Vector2f(182, 304), sf::Vector2f(25, rw.getSize().y/2-152));
        else if (settings.language=="pl")
            wMenu = new Window(nullptr, L"", sf::Vector2f(165, 304), sf::Vector2f(25, rw.getSize().y/2-152));
        else if (settings.language=="en")
            wMenu = new Window(nullptr, L"", sf::Vector2f(218, 304), sf::Vector2f(25, rw.getSize().y/2-152));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(0, 5), dict("button.resume"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(0, 80), dict("button.options"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(0, 155), dict("button.help"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(0, 230), dict("button.quit"), 52));
            for (int i=0; i<4; i++)
                component(wMenu, Button, i)->setPosition(wMenu->getPosition()+sf::Vector2f(wMenu->getSize().x/2-component(wMenu, Button, i)->getSize().x/2, 5+i*75));

        wMenu->setVisible(true);

        /*using the text for the header from a button just to save some space*/
        wOpts = new Window(nullptr, dict("button.options"), sf::Vector2f(330, 454), sf::Vector2f(rw.getSize().x-355, rw.getSize().y/2-220));
            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 30), dict("text.resolution"), font_Unifont, 20));
            wOpts->addComponent(new Switch(wOpts, sf::Vector2f(220, 25), sf::Vector2f(20, 60)));
                component(wOpts, Switch, 0)->addOption(L"1280x720");
                component(wOpts, Switch, 0)->addOption(L"1440x900");
                component(wOpts, Switch, 0)->addOption(L"1600x900");
                component(wOpts, Switch, 0)->addOption(L"1920x1080");
                component(wOpts, Switch, 0)->setCurrentOption(std::to_wstring(settings.resolution.x)+L"x"+std::to_wstring(settings.resolution.y));

            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 170), dict("checkbox.fullscreen"), 15));
                component(wOpts, Checkbox, 0)->check(settings.fullscreen);
            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 120), dict("checkbox.vsync"), 15));
                component(wOpts, Checkbox, 1)->check(settings.vsync);

            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 220), dict("text.language"), font_Unifont, 20));

            wOpts->addComponent(new Switch(wOpts, sf::Vector2f(220, 25), sf::Vector2f(20, 250)));
                component(wOpts, Switch, 1)->addOption(L"ENGLISH");
                component(wOpts, Switch, 1)->addOption(L"POLSKI");
                component(wOpts, Switch, 1)->addOption(L"DNQUBIÑHBI");
                if (settings.language=="en")
                    component(wOpts, Switch, 1)->setCurrentOption(L"ENGLISH");
                else if (settings.language=="pl")
                    component(wOpts, Switch, 1)->setCurrentOption(L"POLSKI");
                else if (settings.language=="fc")
                    component(wOpts, Switch, 1)->setCurrentOption(L"DNQUBIÑHBI");

            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 295), L"ANTIALIASING", font_Unifont, 20));

            wOpts->addComponent(new Switch(wOpts, sf::Vector2f(220, 25), sf::Vector2f(20, 325)));
                component(wOpts, Switch, 2)->addOption(L"NONE");
                component(wOpts, Switch, 2)->addOption(L"x2");
                component(wOpts, Switch, 2)->addOption(L"x4");
                component(wOpts, Switch, 2)->addOption(L"x8");
                if (settings.csettings.antialiasingLevel==0)
                    component(wOpts, Switch, 2)->setCurrentOption(L"NONE");
                else
                    component(wOpts, Switch, 2)->setCurrentOption(L"x"+std::to_wstring(settings.csettings.antialiasingLevel));

            wOpts->addComponent(new Button(wOpts, sf::Vector2f(10, 395), dict("button.save"), 30));
            wOpts->addComponent(new Button(wOpts, sf::Vector2f(170, 395), dict("button.quit"), 30));
                component(wOpts, Button, 0)->setPosition(wOpts->getPosition()+sf::Vector2f(165-(component(wOpts, Button, 0)->getSize().x+component(wOpts, Button, 1)->getSize().x)/2, 395));
                component(wOpts, Button, 1)->setPosition(component(wOpts, Button, 0)->getPosition()+sf::Vector2f(component(wOpts, Button, 0)->getSize().x+5, 0));
        wOpts->setVisible(false);


        wHelp = new Window(nullptr, dict("button.help"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wHelp->addComponent(new Text(wHelp, sf::Vector2f(20, 25), L"Protip:", font_Unifont, 30, sf::Color::Yellow));
            wHelp->addComponent(new Text(wHelp, sf::Vector2f(20, 55), dict("text.killurslf"), font_Unifont, 30, sf::Color::Red));

            wHelp->addComponent(new Button(wHelp, sf::Vector2f(5, 380), dict("button.quit"), 52));
                component(wHelp, Button, 0)->setPosition(wHelp->getPosition()+sf::Vector2f(wHelp->getSize().x/2-component(wHelp, Button, 0)->getSize().x/2, 379));
        wHelp->setVisible(false);

        #undef dict
        #undef component
    }

    PauseMenu::~PauseMenu() {
        delete title;
        delete wMenu;
        delete wOpts;
        delete wHelp;
    }

    void PauseMenu::buttonEvents(sf::RenderWindow& rw, Game* g) {
        #define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)
        #define cmc(w, c, x) w->getComponent<c>(x)->containsMouseCursor(rw)
        #define component(w, c, i) w->getComponent<c>(i)

        if (wMenu->isVisible() && !wOpts->isVisible() && !wHelp->isVisible()) {
            if (cmc(wMenu, Button, 0) && isMLBPressed) g->pause(false);
            if (cmc(wMenu, Button, 1) && isMLBPressed) wOpts->setVisible(true);
            if (cmc(wMenu, Button, 2) && isMLBPressed) wHelp->setVisible(true);
            if (cmc(wMenu, Button, 3) && isMLBPressed) g->start(false);
        } else if (wOpts->isVisible()) {
            component(wOpts, Switch, 0)->buttonEvents(rw);
            component(wOpts, Switch, 1)->buttonEvents(rw);
            component(wOpts, Switch, 2)->buttonEvents(rw);

            for (unsigned i=0; i<2; i++)
                if (cmc(wOpts, Checkbox, i) && isMLBPressed) {
                    if (!component(wOpts, Checkbox, i)->isChecked())
                        component(wOpts, Checkbox, i)->check(true);
                    else
                        component(wOpts, Checkbox, i)->check(false);
                }

            if (cmc(wOpts, Button, 0) && isMLBPressed) {
                puts(">Saving the settings...");
                std::vector<std::string> splitted = split(wtoa(component(wOpts, Switch, 0)->getCurrentOption()), 'x');

                settings.resolution = sf::Vector2u(atoi(splitted[0].c_str()), atoi(splitted[1].c_str()));
                settings.fullscreen = component(wOpts, Checkbox, 0)->isChecked();
                settings.vsync = component(wOpts, Checkbox, 1)->isChecked();

                if (component(wOpts, Switch, 1)->getCurrentOption()==L"ENGLISH")
                    settings.language = "en";
                else if (component(wOpts, Switch, 1)->getCurrentOption()==L"POLSKI")
                    settings.language = "pl";
                else if (component(wOpts, Switch, 1)->getCurrentOption()==L"DNQUBIÑHBI")
                    settings.language = "fc";

                if (component(wOpts, Switch, 2)->getCurrentOption()==L"x2")
                    settings.csettings.antialiasingLevel = 2;
                else if (component(wOpts, Switch, 2)->getCurrentOption()==L"x4")
                    settings.csettings.antialiasingLevel = 4;
                else if (component(wOpts, Switch, 2)->getCurrentOption()==L"x8")
                    settings.csettings.antialiasingLevel = 8;
                else
                    settings.csettings.antialiasingLevel = 0;

                settings.print();
                puts(">Done.");
                wOpts->setVisible(false);
            }
            if (cmc(wOpts, Button, 1) && isMLBPressed)
                wOpts->setVisible(false);
        } else if (wHelp->isVisible()) {
            if (cmc(wHelp, Button, 0) && isMLBPressed)
                wHelp->setVisible(false);
        }

        #undef isMLBPressed
        #undef cmc
        #undef component
    }

    void PauseMenu::draw(sf::RenderWindow& rw, sf::View& v) {
        rw.setView(rw.getDefaultView());
        title->draw(rw);
        wMenu->draw(rw);
        wOpts->draw(rw);
        wHelp->draw(rw);
        rw.setView(v);
    }
}
