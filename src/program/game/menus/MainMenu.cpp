/**
 * @file src/program/game/menus/MainMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "menus.h"
#include "../../funcs/funcs.h"

#include <string>
#include <cstdlib>
#include <iostream>

extern std::map<std::string, sf::String> dictionary;
extern rr::Settings settings;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;

namespace rr {

    MainMenu::MainMenu(sf::RenderWindow& rw) {
        #define dict(s) dictionary[s]

        title = new Text(nullptr, sf::Vector2f(0, 0), L"PAhAom", font_Pixel, 100, sf::Color::Yellow);
            title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

            wMenu = new Window(nullptr, L"", sf::Vector2f(233, 454), sf::Vector2f(25, rw.getSize().y/2-225));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 5), dict("button.newgame"), 52));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 80), dict("button.load"), 52));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 155), dict("button.options"), 52));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 230), dict("button.help"), 52));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 305), dict("button.credits"), 52));
            wMenu->addComponent(new Button(wMenu, sf::Vector2f(5, 380), dict("button.quit"), 52));
        wMenu->setVisible(true);

        /*using the text for the header from a button just to save some space*/
        wOpts = new Window(nullptr, dict("button.options"), sf::Vector2f(330, 454), sf::Vector2f(rw.getSize().x-355, rw.getSize().y/2-225));
            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 30), dict("text.resolution"), font_Unifont, 20));

            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 60)));
                wOpts->getComponent<Switch>(0)->addOption(L"1280x720");
                wOpts->getComponent<Switch>(0)->addOption(L"1440x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1600x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1920x1080");
                wOpts->getComponent<Switch>(0)->setCurrentOption(std::to_wstring(settings.resolution.x)+L"x"+std::to_wstring(settings.resolution.y));

            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 170), dict("checkbox.fullscreen"), 15));
                wOpts->getComponent<Checkbox>(0)->check(settings.fullscreen);
            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 120), dict("checkbox.vsync"), 15));
                wOpts->getComponent<Checkbox>(1)->check(settings.vsync);

            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 220), dict("text.language"), font_Unifont, 20));

            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 250)));
                wOpts->getComponent<Switch>(1)->addOption(L"ENGLISH");
                wOpts->getComponent<Switch>(1)->addOption(L"POLSKI");
                wOpts->getComponent<Switch>(1)->addOption(L"DNQUBIÑHBI");
                if (settings.language=="en")
                    wOpts->getComponent<Switch>(1)->setCurrentOption(L"ENGLISH");
                else if (settings.language=="pl")
                    wOpts->getComponent<Switch>(1)->setCurrentOption(L"POLSKI");
                else if (settings.language=="fc")
                    wOpts->getComponent<Switch>(1)->setCurrentOption(L"DNQUBIÑHBI");


            wOpts->addComponent(new Text(wOpts, sf::Vector2f(20, 295), L"ANTIALIASING", font_Unifont, 20));

            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 325)));
                wOpts->getComponent<Switch>(2)->addOption(L"NONE");
                wOpts->getComponent<Switch>(2)->addOption(L"x2");
                wOpts->getComponent<Switch>(2)->addOption(L"x4");
                wOpts->getComponent<Switch>(2)->addOption(L"x8");
                if (settings.csettings.antialiasingLevel==0)
                    wOpts->getComponent<Switch>(2)->setCurrentOption(L"NONE");
                else
                    wOpts->getComponent<Switch>(2)->setCurrentOption(L"x"+std::to_wstring(settings.csettings.antialiasingLevel));


            wOpts->addComponent(new Button(wOpts, sf::Vector2f(10, 395), dict("button.save"), 30));
                wOpts->getComponent<Button>(0)->setPosition(wOpts->getPosition()+sf::Vector2f(165-wOpts->getComponent<Button>(0)->getSize().x, 395));
            wOpts->addComponent(new Button(wOpts, sf::Vector2f(170, 395), dict("button.quit"), 30));
                wOpts->getComponent<Button>(1)->setPosition(wOpts->getPosition()+sf::Vector2f(170, 395));
        wOpts->setVisible(false);


        wHelp = new Window(nullptr, dict("button.help"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wHelp->addComponent(new Text(wHelp, sf::Vector2f(20, 25), L"Protip:", font_Unifont, 30, sf::Color::Yellow));
            wHelp->addComponent(new Text(wHelp, sf::Vector2f(20, 55), dict("text.killurslf"), font_Unifont, 30, sf::Color::Red));

            wHelp->addComponent(new Button(wHelp, sf::Vector2f(20, 365), dict("button.quit"), 52));
        wHelp->setVisible(false);

        if (settings.language=="en")
            wCred = new Window(nullptr, dict("button.credits"), sf::Vector2f(325, 300), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-150));
        else
            wCred = new Window(nullptr, dict("button.credits"), sf::Vector2f(375, 300), sf::Vector2f(rw.getSize().x-400, rw.getSize().y/2-150));
            wCred->addComponent(new Text(wCred, sf::Vector2f(20, 20), dict("text.wholegame"), font_Unifont, 30));
            wCred->addComponent(new Text(wCred, sf::Vector2f(0, 50), L"\tAdam 'Adanos' Gąsior", font_Unifont, 25, sf::Color::Yellow));
            wCred->addComponent(new Text(wCred, sf::Vector2f(20, 80), dict("text.usedlib"), font_Unifont, 30));
            wCred->addComponent(new Text(wCred, sf::Vector2f(0, 110), L"\tSFML 2.3.2", font_Unifont, 25, sf::Color::Yellow));

            wCred->addComponent(new Button(wCred, sf::Vector2f(20, 210), dict("button.quit"), 52));
        wCred->setVisible(false);

        #undef dict
    }

    MainMenu::~MainMenu() {
        delete title;
        delete wMenu;
        delete wOpts;
        delete wHelp;
        delete wCred;
    }

    void MainMenu::buttonEvents(sf::RenderWindow& rw, Game* g) {
        #define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)
        #define cmc(w, c, x) w->getComponent<c>(x)->containsMouseCursor(rw)

        if (wMenu->isVisible() && !wOpts->isVisible() && !wHelp->isVisible() && !wCred->isVisible()) {
            if (cmc(wMenu, Button, 0) && isMLBPressed) if (g->loadNewGame()) g->start(true);
            if (cmc(wMenu, Button, 1) && isMLBPressed) if (g->load()) g->start(true);
            if (cmc(wMenu, Button, 2) && isMLBPressed) wOpts->setVisible(true);
            if (cmc(wMenu, Button, 3) && isMLBPressed) wHelp->setVisible(true);
            if (cmc(wMenu, Button, 4) && isMLBPressed) wCred->setVisible(true);
            if (cmc(wMenu, Button, 5) && isMLBPressed) rw.close();
        } else if (wOpts->isVisible()) {
            wOpts->getComponent<Switch>(0)->buttonEvents(rw);
            wOpts->getComponent<Switch>(1)->buttonEvents(rw);
            wOpts->getComponent<Switch>(2)->buttonEvents(rw);

            for (unsigned i=0; i<2; i++) {
                if (cmc(wOpts, Checkbox, i) && isMLBPressed) {
                    if (!wOpts->getComponent<Checkbox>(i)->isChecked())
                        wOpts->getComponent<Checkbox>(i)->check(true);
                    else
                        wOpts->getComponent<Checkbox>(i)->check(false);
                }
            }

            if (cmc(wOpts, Button, 0) && isMLBPressed) {
                puts(">Saving the settings...");
                std::vector<std::string> splitted = split(wtoa(wOpts->getComponent<Switch>(0)->getCurrentOption()), 'x');

                settings.resolution = sf::Vector2u(atoi(splitted[0].c_str()), atoi(splitted[1].c_str()));
                settings.fullscreen = wOpts->getComponent<Checkbox>(0)->isChecked();
                settings.vsync = wOpts->getComponent<Checkbox>(1)->isChecked();

                if (wOpts->getComponent<Switch>(1)->getCurrentOption()==L"ENGLISH")
                    settings.language = "en";
                else if (wOpts->getComponent<Switch>(1)->getCurrentOption()==L"POLSKI")
                    settings.language = "pl";
                else if (wOpts->getComponent<Switch>(1)->getCurrentOption()==L"DNQUBIÑHBI")
                    settings.language = "fc";

                if (wOpts->getComponent<Switch>(2)->getCurrentOption()==L"x2")
                    settings.csettings.antialiasingLevel = 2;
                else if (wOpts->getComponent<Switch>(2)->getCurrentOption()==L"x4")
                    settings.csettings.antialiasingLevel = 4;
                else if (wOpts->getComponent<Switch>(2)->getCurrentOption()==L"x8")
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
        } else if (wCred->isVisible()) {
            if (cmc(wCred, Button, 0) && isMLBPressed)
                wCred->setVisible(false);
        }

        #undef isMLBPressed
        #undef cmc
    }

    void MainMenu::draw(sf::RenderWindow& rw, sf::View& v) {
        rw.setView(rw.getDefaultView());
        title->draw(rw);
        wMenu->draw(rw);
        wOpts->draw(rw);
        wHelp->draw(rw);
        wCred->draw(rw);
        rw.setView(v);
    }
}
