#include "menus.h"

namespace rr {

    extern std::map<std::string, std::wstring> dictionary;

    MainMenu::MainMenu(sf::RenderWindow& rw) {
        #define dict(s) dictionary[(std::string)s]

        title = new Text("PAhAom", 100, sf::Color::Yellow);
        title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        wMenu = new Window("", sf::Vector2f(325, 454), sf::Vector2f(25, rw.getSize().y/2-225));
            wMenu->addComponent(new Button(sf::Vector2f(5, 5), dict("button.newgame"), 52));
            wMenu->addComponent(new Button(sf::Vector2f(5, 80), dict("button.load"), 52));
            wMenu->addComponent(new Button(sf::Vector2f(5, 155), dict("button.options"), 52));
            wMenu->addComponent(new Button(sf::Vector2f(5, 230), dict("button.help"), 52));
            wMenu->addComponent(new Button(sf::Vector2f(5, 305), dict("button.credits"), 52));
            wMenu->addComponent(new Button(sf::Vector2f(5, 380), dict("button.quit"), 52));
        wMenu->setVisible(true);

        /*using the text for the header from a button just to save some space*/
        wOpts = new Window(dict("button.options"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wOpts->addComponent(new Text(dict("text.resolution"), sf::Vector2f(20, 30), 20));
            wOpts->addComponent(new Switch("<", ">", sf::Vector2f(220, 25), sf::Vector2f(20, 60)));

            wOpts->getComponent<Switch>(0)->addOption(L"800x420");
            wOpts->getComponent<Switch>(0)->addOption(L"1280x720");
            wOpts->getComponent<Switch>(0)->addOption(L"1440x900");
            wOpts->getComponent<Switch>(0)->addOption(L"1600x900");
            wOpts->getComponent<Switch>(0)->addOption(L"1920x1080");

            wOpts->addComponent(new Checkbox(sf::Vector2f(20, 120), dict("checkbox.vsync"), 15));
            wOpts->addComponent(new Checkbox(sf::Vector2f(20, 170), dict("checkbox.fullscreen"), 15));

            wOpts->addComponent(new Text(dict("text.language"), sf::Vector2f(20, 220), 20));

            wOpts->addComponent(new Switch("<", ">", sf::Vector2f(220, 25), sf::Vector2f(20, 250)));
                wOpts->getComponent<Switch>(1)->addOption(L"ENGLISH");
                wOpts->getComponent<Switch>(1)->addOption(L"POLSKI");
                wOpts->getComponent<Switch>(1)->addOption(L"DNQUBIÑHBI");

            wOpts->addComponent(new Button(sf::Vector2f(35, 395), dict("button.apply"), 30));
            wOpts->addComponent(new Button(sf::Vector2f(180, 395), dict("button.quit"), 30));
        wOpts->setVisible(false);


        wHelp = new Window(dict("button.help"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wHelp->addComponent(new Text("Protip:", sf::Vector2f(20, 25), 30, sf::Color::Yellow));
            wHelp->addComponent(new Text(dict("text.killurslf"), sf::Vector2f(20, 55), 30, sf::Color::Red));

            wHelp->addComponent(new Button(sf::Vector2f(20, 365), dict("button.quit"), 52));
        wHelp->setVisible(false);


        wCred = new Window(dict("button.credits"), sf::Vector2f(325, 300), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-150));
            wCred->addComponent(new Text(dict("text.wholegame"), sf::Vector2f(20, 20), 30));
            wCred->addComponent(new Text(L"\tAdam 'Adanos' Gąsior", sf::Vector2f(0, 50), 25, sf::Color::Yellow));
            wCred->addComponent(new Text(dict("text.usedlib"), sf::Vector2f(20, 80), 30));
            wCred->addComponent(new Text("\tSFML 2.3.2", sf::Vector2f(0, 110), 25, sf::Color::Yellow));

            wCred->addComponent(new Button(sf::Vector2f(20, 210), dict("button.quit"), 52));
        wCred->setVisible(false);

        #undef dict
    }

    MainMenu::~MainMenu() {
        delete wMenu;
        delete wOpts;
        delete wHelp;
        delete wCred;
    }

    void MainMenu::buttonEvents(sf::RenderWindow& rw, Game* g) {
        #define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)

        if (wMenu->isVisible() && !wOpts->isVisible() && !wHelp->isVisible() && !wCred->isVisible()) {
            if (wMenu->getComponent<Button>(0)->containsMouseCursor(rw) && isMLBPressed) if (g->loadNewGame()) g->start(true);
            if (wMenu->getComponent<Button>(1)->containsMouseCursor(rw) && isMLBPressed) if (g->load()) g->start(true);
            if (wMenu->getComponent<Button>(2)->containsMouseCursor(rw) && isMLBPressed) wOpts->setVisible(true);
            if (wMenu->getComponent<Button>(3)->containsMouseCursor(rw) && isMLBPressed) wHelp->setVisible(true);
            if (wMenu->getComponent<Button>(4)->containsMouseCursor(rw) && isMLBPressed) wCred->setVisible(true);
            if (wMenu->getComponent<Button>(5)->containsMouseCursor(rw) && isMLBPressed) rw.close();
        }
        else if (wOpts->isVisible()) {
            wOpts->getComponent<Switch>(0)->buttonEvents(rw);
            wOpts->getComponent<Switch>(1)->buttonEvents(rw);

            if (wOpts->getComponent<Button>(1)->containsMouseCursor(rw) && isMLBPressed) wOpts->setVisible(false);

            for (unsigned i=0; i<3; i++)
                if (wOpts->getComponent<Checkbox>(i)->containsMouseCursor(rw) && isMLBPressed) {
                    if (!wOpts->getComponent<Checkbox>(i)->isChecked()) wOpts->getComponent<Checkbox>(i)->check(true);
                    else wOpts->getComponent<Checkbox>(i)->check(false);
                }
        }
        else if (wHelp->isVisible()) {
            if (wHelp->getComponent<Button>(0)->containsMouseCursor(rw) && isMLBPressed) wHelp->setVisible(false);
        }
        else if (wCred->isVisible()) {
            if (wCred->getComponent<Button>(0)->containsMouseCursor(rw) && isMLBPressed) wCred->setVisible(false);
        }

        #undef isMLBPressed
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
