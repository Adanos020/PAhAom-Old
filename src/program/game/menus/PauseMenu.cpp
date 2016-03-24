#include "menus.h"

extern std::map<std::string, std::wstring> dictionary;

namespace rr {

    PauseMenu::PauseMenu(sf::RenderWindow& rw, Settings settings) {
        #define dict(s) dictionary[(std::string)s]

        title = new Text(nullptr, "PAhAom", 100, sf::Color::Yellow);
            title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        wMenu = new Window(nullptr, "", sf::Vector2f(325, 454), sf::Vector2f(25, rw.getSize().y/2-225));
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
            wOpts->addComponent(new Switch(wOpts, "<", ">", sf::Vector2f(220, 25), sf::Vector2f(20, 60)));
                wOpts->getComponent<Switch>(0)->addOption(L"800x420");
                wOpts->getComponent<Switch>(0)->addOption(L"1280x720");
                wOpts->getComponent<Switch>(0)->addOption(L"1440x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1600x900");
                wOpts->getComponent<Switch>(0)->addOption(L"1920x1080");
                wOpts->getComponent<Switch>(0)->setCurrentOption(std::to_wstring(settings.resolution.x)+L"x"+std::to_wstring(settings.resolution.y));

            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 120), dict("checkbox.vsync"), 15));
                wOpts->getComponent<Checkbox>(0)->check(settings.vsync);
            wOpts->addComponent(new Checkbox(wOpts, sf::Vector2f(15, 170), dict("checkbox.fullscreen"), 15));
                wOpts->getComponent<Checkbox>(1)->check(settings.fullscreen);

            wOpts->addComponent(new Text(wOpts, dict("text.language"), sf::Vector2f(20, 220), 20));

            wOpts->addComponent(new Switch(wOpts, "<", ">", sf::Vector2f(220, 25), sf::Vector2f(20, 250)));
                wOpts->getComponent<Switch>(1)->addOption(L"ENGLISH");
                wOpts->getComponent<Switch>(1)->addOption(L"POLSKI");
                wOpts->getComponent<Switch>(1)->addOption(L"DNQUBIÑHBI");

            wOpts->addComponent(new Button(wOpts, sf::Vector2f(35, 395), dict("button.apply"), 30));
            wOpts->addComponent(new Button(wOpts, sf::Vector2f(180, 395), dict("button.quit"), 30));
        wOpts->setVisible(false);


        wHelp = new Window(nullptr, dict("button.help"), sf::Vector2f(325, 454), sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225));
            wHelp->addComponent(new Text(wHelp, "Protip:", sf::Vector2f(20, 25), 30, sf::Color::Yellow));
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

        if (wMenu->isVisible() && !wOpts->isVisible() && !wHelp->isVisible()) {
            if (wMenu->getComponent<Button>(0)->containsMouseCursor(rw) && isMLBPressed) g->pause(false);
            if (wMenu->getComponent<Button>(1)->containsMouseCursor(rw) && isMLBPressed) g->save();
            if (wMenu->getComponent<Button>(2)->containsMouseCursor(rw) && isMLBPressed) if (g->load()) g->pause(false);
            if (wMenu->getComponent<Button>(3)->containsMouseCursor(rw) && isMLBPressed) wOpts->setVisible(true);
            if (wMenu->getComponent<Button>(4)->containsMouseCursor(rw) && isMLBPressed) wHelp->setVisible(true);
            if (wMenu->getComponent<Button>(5)->containsMouseCursor(rw) && isMLBPressed) g->start(false);
        } else if (wOpts->isVisible()) {
            wOpts->getComponent<Switch>(0)->buttonEvents(rw);
            wOpts->getComponent<Switch>(1)->buttonEvents(rw);

            if (wOpts->getComponent<Button>(1)->containsMouseCursor(rw) && isMLBPressed) wOpts->setVisible(false);

            for (unsigned i=0; i<3; i++)
                if (wOpts->getComponent<Checkbox>(i)->containsMouseCursor(rw) && isMLBPressed) {
                    if (!wOpts->getComponent<Checkbox>(i)->isChecked()) wOpts->getComponent<Checkbox>(i)->check(true);
                    else wOpts->getComponent<Checkbox>(i)->check(false);
                }
        } else if (wHelp->isVisible()) {
            if (wHelp->getComponent<Button>(1)->containsMouseCursor(rw) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) wHelp->setVisible(false);
        }

        #undef isMLBPressed
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
