#include "menus.h"
#include <iostream>

extern std::map<std::string, std::wstring> dictionary;
extern rr::Settings settings;

namespace rr {

    PauseMenu::PauseMenu(sf::RenderWindow& rw, Settings settings) {
        #define dict(s) dictionary[s]

        title = new Text(nullptr, L"PAhAom", 100, sf::Color::Yellow);
            title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        wMenu = new Window(nullptr, L"", sf::Vector2f(325, 454), sf::Vector2f(25, rw.getSize().y/2-225));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 5), dict("button.resume"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 80), dict("button.save"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 155), dict("button.load"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 230), dict("button.options"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 305), dict("button.help"), 52));
            wMenu->addComponent(new Button(wOpts, sf::Vector2f(5, 380), dict("button.quit"), 52));
        wMenu->setVisible(true);

        /*using the text for the header from a button just to save some space*/
        wOpts = new Window(nullptr, dict("button.options"), sf::Vector2f(330, 454), sf::Vector2f(rw.getSize().x-355, rw.getSize().y/2-220));
            wOpts->addComponent(new Text(wOpts, dict("text.resolution"), sf::Vector2f(20, 30), 20));
            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 60)));
                wOpts->getComponent<Switch>(0)->addOption(L"800x420");
                wOpts->getComponent<Switch>(0)->addOption(L"1280x720");
                wOpts->getComponent<Switch>(0)->addOption(L"1440x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1600x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1920x1080");
                wOpts->getComponent<Switch>(0)->setCurrentOption(std::to_wstring(settings.resolution.x)+L"x"+std::to_wstring(settings.resolution.y));

            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 170), dict("checkbox.fullscreen"), 15));
                wOpts->getComponent<Checkbox>(0)->check(settings.fullscreen);
            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 120), dict("checkbox.vsync"), 15));
                wOpts->getComponent<Checkbox>(1)->check(settings.vsync);

            wOpts->addComponent(new Text(wOpts, dict("text.language"), sf::Vector2f(20, 220), 20));

            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 250)));
                wOpts->getComponent<Switch>(1)->addOption(L"ENGLISH");
                wOpts->getComponent<Switch>(1)->addOption(L"POLSKI");
                wOpts->getComponent<Switch>(1)->addOption(L"DNQUBIÑHBI");


            wOpts->addComponent(new Text(wOpts, L"ANTIALIASING", sf::Vector2f(20, 295), 20));

            wOpts->addComponent(new Switch(wOpts, L"<", L">", sf::Vector2f(220, 25), sf::Vector2f(20, 325)));
                wOpts->getComponent<Switch>(2)->addOption(L"NONE");
                wOpts->getComponent<Switch>(2)->addOption(L"x2");
                wOpts->getComponent<Switch>(2)->addOption(L"x4");
                wOpts->getComponent<Switch>(2)->addOption(L"x8");
                if (settings.csettings.antialiasingLevel==0)
                    wOpts->getComponent<Switch>(2)->setCurrentOption(L"NONE");
                else
                    wOpts->getComponent<Switch>(2)->setCurrentOption(L"x"+std::to_wstring(settings.csettings.antialiasingLevel));


            wOpts->addComponent(new Button(wOpts, sf::Vector2f(35, 395), dict("button.apply"), 30));
            wOpts->addComponent(new Button(wOpts, sf::Vector2f(180, 395), dict("button.quit"), 30));
        wOpts->setVisible(false);


        wHelp = new Window(nullptr, dict("button.help"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wHelp->addComponent(new Text(wHelp, L"Protip:", sf::Vector2f(20, 25), 30, sf::Color::Yellow));
            wHelp->addComponent(new Text(wHelp, dict("text.killurslf"), sf::Vector2f(20, 55), 30, sf::Color::Red));

            wHelp->addComponent(new Button(wHelp, sf::Vector2f(20, 365), dict("button.quit"), 52));
        wHelp->setVisible(false);

        #undef dict
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

        if (wMenu->isVisible() && !wOpts->isVisible() && !wHelp->isVisible()) {
            if (cmc(wMenu, Button, 0) && isMLBPressed) g->pause(false);
            if (cmc(wMenu, Button, 1) && isMLBPressed) g->save();
            if (cmc(wMenu, Button, 2) && isMLBPressed) if (g->load()) g->pause(false);
            if (cmc(wMenu, Button, 3) && isMLBPressed) wOpts->setVisible(true);
            if (cmc(wMenu, Button, 4) && isMLBPressed) wHelp->setVisible(true);
            if (cmc(wMenu, Button, 5) && isMLBPressed) g->start(false);
        } else if (wOpts->isVisible()) {
            wOpts->getComponent<Switch>(0)->buttonEvents(rw);
            wOpts->getComponent<Switch>(1)->buttonEvents(rw);
            wOpts->getComponent<Switch>(2)->buttonEvents(rw);

            for (unsigned i=0; i<2; i++)
                if (cmc(wOpts, Checkbox, i) && isMLBPressed) {
                    if (!wOpts->getComponent<Checkbox>(i)->isChecked())
                        wOpts->getComponent<Checkbox>(i)->check(true);
                    else
                        wOpts->getComponent<Checkbox>(i)->check(false);
                }

            if (cmc(wOpts, Button, 0) && isMLBPressed) {
                std::vector<std::string> splitted = split(wtoa(wOpts->getComponent<Switch>(0)->getCurrentOption()), 'x');

                settings.resolution = sf::Vector2u(atoi(splitted[0].c_str()), atoi(splitted[1].c_str()));
                settings.fullscreen = wOpts->getComponent<Checkbox>(0)->isChecked();
                settings.vsync = wOpts->getComponent<Checkbox>(1)->isChecked();

                if (wOpts->getComponent<Switch>(1)->getCurrentOption()==L"ENGLISH")
                    settings.language = "en";
                else if (wOpts->getComponent<Switch>(1)->getCurrentOption()==L"POLISH")
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
                wOpts->setVisible(false);
            }
            if (cmc(wOpts, Button, 1) && isMLBPressed)
                wOpts->setVisible(false);
        } else if (wHelp->isVisible()) {
            if (cmc(wHelp, Button, 1) && isMLBPressed)
                wHelp->setVisible(false);
        }

        #undef isMLBPressed
        #undef cmc
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
