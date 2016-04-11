/**
 * @file src/program/game/menus/MainMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../funcs/funcs.hpp"

#include <string>
#include <cstdlib>
#include <iostream>

extern rr::Dictionary dictionary;
extern rr::Settings   settings;
extern rr::Resources  resources;

namespace rr {

    MainMenu::MainMenu(sf::RenderWindow& rw) {

#define component(w, c, i) w->getComponent<c>(i)

        title = new Text(sf::Vector2f(0, 0), L"PAhAom", resources.font.Pixel, 100, sf::Color::Yellow);
        title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        wMenu = new Window(L"", sf::Vector2f(244, 454), sf::Vector2f(25, rw.getSize().y/2-225));
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.newgame, 52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.load,    52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.options, 52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.help,    52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.credits, 52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit,    52), true);
            for (int i=0; i<6; i++)
                component(wMenu, Button, i)->setPosition(wMenu->getPosition()+sf::Vector2f(wMenu->getSize().x/2-component(wMenu, Button, i)->getSize().x/2, 5+i*75));

            wMenu->addComponent(new Window(dictionary.gui.button.options, sf::Vector2f(330, 405),
                                           sf::Vector2f(rw.getSize().x/2-165, rw.getSize().y/2-202.5)), false);

#define wOpts component(wMenu, Window, 0)

                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.game,      52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.graphical, 52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.sound,     52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.controls,  52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.save,      30), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit,      30), true);
                for (int i=0; i<4; i++)
                    component(wOpts, Button, i)->setPosition(wOpts->getPosition()+sf::Vector2f(wOpts->getSize().x/2-component(wOpts, Button, i)->getSize().x/2, 30+i*75));
                component(wOpts, Button, 4)->setPosition(wOpts->getPosition()+sf::Vector2f(wOpts->getSize().x/2-(component(wOpts, Button, 4)->getSize().x+component(wOpts, Button, 5)->getSize().x+5)/2, 350));
                component(wOpts, Button, 5)->setPosition(component(wOpts, Button, 4)->getPosition()+sf::Vector2f(component(wOpts, Button, 4)->getSize().x+5, 0));

                wOpts->addComponent(new Window(dictionary.gui.button.game, sf::Vector2f(340, 354),
                                               sf::Vector2f(rw.getSize().x-365, rw.getSize().y/2-177)), false);

#define wGame component(wOpts, Window, 0)

                    wGame->addComponent(new Text(sf::Vector2f(10, 30), dictionary.gui.text.language, resources.font.Unifont), true);

                    wGame->addComponent(new Switch(sf::Vector2f(220, 25), sf::Vector2f(20, 80)), true);
                        component(wGame, Switch, 0)->addOption(L"ENGLISH");
                        component(wGame, Switch, 0)->addOption(L"POLSKI");
                        component(wGame, Switch, 0)->addOption(L"DNQUBIÑHBI");
                        if      (settings.game.language == "en")
                            component(wGame, Switch, 0)->setCurrentOption(L"ENGLISH");
                        else if (settings.game.language == "pl")
                            component(wGame, Switch, 0)->setCurrentOption(L"POLSKI");
                        else if (settings.game.language == "fc")
                            component(wGame, Switch, 0)->setCurrentOption(L"DNQUBIÑHBI");

                    wGame->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                    component(wGame, Button, 0)->setPosition(sf::Vector2f(wGame->getPosition().x+wGame->getSize().x/2-component(wGame, Button, 0)->getSize().x/2,
                                                                          wGame->getPosition().y+wGame->getSize().y-component(wGame, Button, 0)->getSize().y-10));

#undef wGame

                wOpts->addComponent(new Window(dictionary.gui.button.graphical, sf::Vector2f(340, 434),
                                               sf::Vector2f(rw.getSize().x-365, rw.getSize().y/2-217)), false);

#define wGrap component(wOpts, Window, 1)

                    wGrap->addComponent(new Text(sf::Vector2f(20, 30), dictionary.gui.text.resolution, resources.font.Unifont, 20), true);

                    wGrap->addComponent(new Switch(sf::Vector2f(220, 25), sf::Vector2f(20, 60)), true);
                        component(wGrap, Switch, 0)->addOption(L"1280x720");
                        component(wGrap, Switch, 0)->addOption(L"1440x900");
                        component(wGrap, Switch, 0)->addOption(L"1600x900");
                        component(wGrap, Switch, 0)->addOption(L"1920x1080");
                        component(wGrap, Switch, 0)->setCurrentOption(std::to_wstring(settings.graphics.resolution.x)+L"x"+std::to_wstring(settings.graphics.resolution.y));

                    wGrap->addComponent(new Checkbox(sf::Vector2f(15, 170), dictionary.gui.checkbox.fullscreen, 15), true);
                        component(wGrap, Checkbox, 0)->check(settings.graphics.fullscreen);

                    wGrap->addComponent(new Checkbox(sf::Vector2f(15, 120), dictionary.gui.checkbox.vsync, 15), true);
                        component(wGrap, Checkbox, 1)->check(settings.graphics.vsync);

                    wGrap->addComponent(new Text(sf::Vector2f(20, 295), L"ANTIALIASING", resources.font.Unifont, 20), true);

                    wGrap->addComponent(new Switch(sf::Vector2f(220, 25), sf::Vector2f(20, 325)), true);
                        component(wGrap, Switch, 1)->addOption(L"NONE");
                        component(wGrap, Switch, 1)->addOption(L"x2");
                        component(wGrap, Switch, 1)->addOption(L"x4");
                        component(wGrap, Switch, 1)->addOption(L"x8");
                        if (settings.graphics.csettings.antialiasingLevel == 0)
                            component(wGrap, Switch, 1)->setCurrentOption(L"NONE");
                        else
                            component(wGrap, Switch, 1)->setCurrentOption(L"x"+std::to_wstring(settings.graphics.csettings.antialiasingLevel));

                    wGrap->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                    component(wGrap, Button, 0)->setPosition(sf::Vector2f(wGrap->getPosition().x+wGrap->getSize().x/2-component(wGrap, Button, 0)->getSize().x/2,
                                                                          wGrap->getPosition().y+wGrap->getSize().y-component(wGrap, Button, 0)->getSize().y-10));

#undef wGrap

                wOpts->addComponent(new Window(dictionary.gui.button.sound, sf::Vector2f(300, 330),
                                               sf::Vector2f(rw.getSize().x-325, rw.getSize().y/2-165)), false);

#define wSoun component(wOpts, Window, 2)

                    wSoun->addComponent(new Text(sf::Vector2f(20, 40), dictionary.gui.text.music, resources.font.Unifont), true);
                    wSoun->addComponent(new Slider(Slider::HORIZONTAL, sf::Vector2f(20, 85), sf::Vector2f(175, 30)), true);
                    wSoun->addComponent(new Checkbox(sf::Vector2f(175, 40), dictionary.gui.text.mute, 20), true);
                    component(wSoun, Checkbox, 0)->check(settings.sound.music_muted);
                    component(wSoun, Slider,   0)->setValue(settings.sound.music_volume);

                    wSoun->addComponent(new Text(sf::Vector2f(20, 160), dictionary.gui.text.effects, resources.font.Unifont), true);
                    wSoun->addComponent(new Slider(Slider::HORIZONTAL, sf::Vector2f(20, 205), sf::Vector2f(175, 30)), true);
                    wSoun->addComponent(new Checkbox(sf::Vector2f(175, 160), dictionary.gui.text.mute, 20), true);
                    component(wSoun, Checkbox, 1)->check(settings.sound.effects_muted);
                    component(wSoun, Slider,   1)->setValue(settings.sound.effects_volume);

                    wSoun->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                    component(wSoun, Button, 0)->setPosition(sf::Vector2f(wSoun->getPosition().x+wSoun->getSize().x/2-component(wSoun, Button, 0)->getSize().x/2,
                                                                          wSoun->getPosition().y+wSoun->getSize().y-component(wSoun, Button, 0)->getSize().y-10));

#undef wSoun

                wOpts->addComponent(new Window(dictionary.gui.button.controls, sf::Vector2f(300, 454),
                                               sf::Vector2f(rw.getSize().x-325, rw.getSize().y/2-225)), false);

#define wCont component(wOpts, Window, 3)

                    wCont->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                    component(wCont, Button, 0)->setPosition(sf::Vector2f(wCont->getPosition().x+wCont->getSize().x/2-component(wCont, Button, 0)->getSize().x/2,
                                                                          wCont->getPosition().y+wCont->getSize().y-component(wCont, Button, 0)->getSize().y-10));

#undef wCont
#undef wOpts

            wMenu->addComponent(new Window(dictionary.gui.button.help, sf::Vector2f(325, 454),
                                           sf::Vector2f(rw.getSize().x/2-162.5, rw.getSize().y/2-225)), false);

#define wHelp component(wMenu, Window, 1)

                wHelp->addComponent(new Text(sf::Vector2f(20, 25), L"Pro tip:",                   resources.font.Unifont, 30, sf::Color::Yellow), true);
                wHelp->addComponent(new Text(sf::Vector2f(20, 55), dictionary.gui.text.killurslf, resources.font.Unifont, 30, sf::Color::Red),    true);

                wHelp->addComponent(new Button(sf::Vector2f(5, 380), dictionary.gui.button.quit, 52), true);
                component(wHelp, Button, 0)->setPosition(wHelp->getPosition()+sf::Vector2f(wHelp->getSize().x/2-component(wHelp, Button, 0)->getSize().x/2, 379));

#undef wHelp

            wMenu->addComponent(new Window(dictionary.gui.button.credits, sf::Vector2f(375, 300), sf::Vector2f(rw.getSize().x/2-187.5, rw.getSize().y/2-150)), false);
#define wCred component(wMenu, Window, 2)

                wCred->addComponent(new Text(sf::Vector2f(20, 20), dictionary.gui.text.wholegame, resources.font.Unifont, 30),                    true);
                wCred->addComponent(new Text(sf::Vector2f(0, 50),  L"\tAdam 'Adanos' Gąsior",     resources.font.Unifont, 25, sf::Color::Yellow), true);
                wCred->addComponent(new Text(sf::Vector2f(20, 80), dictionary.gui.text.usedlib,   resources.font.Unifont, 30),                    true);
                wCred->addComponent(new Text(sf::Vector2f(0, 110), L"\tSFML 2.3.2",               resources.font.Unifont, 25, sf::Color::Yellow), true);

                wCred->addComponent(new Button(sf::Vector2f(5, 225), dictionary.gui.button.quit, 52), true);
                    component(wCred, Button, 0)->setPosition(wCred->getPosition()+sf::Vector2f(wCred->getSize().x/2-component(wCred, Button, 0)->getSize().x/2, 225));

            wMenu->setVisible(true);

#undef wCred
#undef dict
#undef component

    }

    MainMenu::~MainMenu() {
        delete title;
        delete wMenu;
    }

    void MainMenu::buttonEvents(sf::RenderWindow& rw, Game* g) {

#define isMLBPressed sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define cmc(w, c, x) w->getComponent<c>(x)->containsMouseCursor(rw)
#define component(w, c, i) w->getComponent<c>(i)
#define wOpts component(wMenu, Window, 0)
#define wHelp component(wMenu, Window, 1)
#define wCred component(wMenu, Window, 2)
#define wGame component(wOpts, Window, 0)
#define wGrap component(wOpts, Window, 1)
#define wSoun component(wOpts, Window, 2)
#define wCont component(wOpts, Window, 3)

        if (wMenu->isVisible()) {
            if (!wOpts->isVisible() && !wHelp->isVisible() && !wCred->isVisible()) {
                if (cmc(wMenu, Button, 0) && isMLBPressed) if (g->loadNewGame()) {
                        g->start(true);
                        g->pause(false);
                    }
                if (cmc(wMenu, Button, 1) && isMLBPressed)
                    if (g->load()) g->start(true);
                if (cmc(wMenu, Button, 2) && isMLBPressed)
                    wOpts->setVisible(true);
                if (cmc(wMenu, Button, 3) && isMLBPressed)
                    wHelp->setVisible(true);
                if (cmc(wMenu, Button, 4) && isMLBPressed)
                    wCred->setVisible(true);
                if (cmc(wMenu, Button, 5) && isMLBPressed)
                    rw.close();
            }

            else if (wOpts->isVisible()) {
                if (!wGame->isVisible() && !wGrap->isVisible() && !wSoun->isVisible() && !wCont->isVisible()) {
                    if (cmc(wOpts, Button, 0) && isMLBPressed)
                        wGame->setVisible(true);
                    if (cmc(wOpts, Button, 1) && isMLBPressed)
                        wGrap->setVisible(true);
                    if (cmc(wOpts, Button, 2) && isMLBPressed)
                        wSoun->setVisible(true);
                    if (cmc(wOpts, Button, 3) && isMLBPressed)
                        wCont->setVisible(true);
                    if (cmc(wOpts, Button, 4) && isMLBPressed) {
                        puts(">Saving the settings...");
                        if      (component(wGame, Switch, 0)->getCurrentOption() == L"ENGLISH")
                            settings.game.language = "en";
                        else if (component(wGame, Switch, 0)->getCurrentOption() == L"POLSKI")
                            settings.game.language = "pl";
                        else if (component(wGame, Switch, 0)->getCurrentOption() == L"DNQUBIÑHBI")
                            settings.game.language = "fc";

                        std::vector<std::string> splitted = split(wtoa(component(wGrap, Switch, 0)->getCurrentOption()), 'x');

                        settings.graphics.resolution = sf::Vector2u(atoi(splitted[0].c_str()), atoi(splitted[1].c_str()));
                        settings.graphics.fullscreen = component(wGrap, Checkbox, 0)->isChecked();
                        settings.graphics.vsync      = component(wGrap, Checkbox, 1)->isChecked();

                        if      (component(wGrap, Switch, 1)->getCurrentOption() == L"x2")
                            settings.graphics.csettings.antialiasingLevel = 2;
                        else if (component(wGrap, Switch, 1)->getCurrentOption() == L"x4")
                            settings.graphics.csettings.antialiasingLevel = 4;
                        else if (component(wGrap, Switch, 1)->getCurrentOption() == L"x8")
                            settings.graphics.csettings.antialiasingLevel = 8;
                        else
                            settings.graphics.csettings.antialiasingLevel = 0;

                        settings.sound.music_muted    = component(wSoun, Checkbox, 0)->isChecked();
                        settings.sound.music_volume   = component(wSoun, Slider, 0)->getValue();
                        settings.sound.effects_muted  = component(wSoun, Checkbox, 1)->isChecked();
                        settings.sound.effects_volume = component(wSoun, Slider, 1)->getValue();

                        settings.print();
                        settings.save ();
                        puts(">Done.");
                        wOpts->setVisible(false);
                    }
                    if (cmc(wOpts, Button, 5) && isMLBPressed)
                        wOpts->setVisible(false);
                }

                else if (wGame->isVisible()) {
                    component(wGame, Switch, 0)->buttonEvents(rw);
                    if (cmc(wGame, Button, 0) && isMLBPressed)
                        wGame->setVisible(false);
                }

                else if (wGrap->isVisible()) {
                    for (unsigned i=0; i<2; i++) {
                        if (cmc(wGrap, Checkbox, i) && isMLBPressed) {
                            if (!component(wGrap, Checkbox, i)->isChecked())
                                component(wGrap, Checkbox, i)->check(true);
                            else
                                component(wGrap, Checkbox, i)->check(false);
                        }
                    }
                    component(wGrap, Switch, 0)->buttonEvents(rw);
                    component(wGrap, Switch, 1)->buttonEvents(rw);
                    if (cmc(wGrap, Button, 0) && isMLBPressed)
                        wGrap->setVisible(false);
                }
                else if (wSoun->isVisible()) {
                    for (int i=0; i<2; i++) {
                        if (cmc(wSoun, Checkbox, i) && isMLBPressed) {
                            if (!component(wSoun, Checkbox, i)->isChecked())
                                component(wSoun, Checkbox, i)->check(true);
                            else
                                component(wSoun, Checkbox, i)->check(false);
                        }
                        component(wSoun, Slider, 0)->buttonEvents(rw);
                        component(wSoun, Slider, 1)->buttonEvents(rw);
                    }
                    if (cmc(wSoun, Button, 0) && isMLBPressed)
                        wSoun->setVisible(false);
                }
                else if (wCont->isVisible()) {
                    if (cmc(wCont, Button, 0) && isMLBPressed)
                        wCont->setVisible(false);
                }
            }

            else if (wHelp->isVisible()) {
                if (cmc(wHelp, Button, 0) && isMLBPressed)
                    wHelp->setVisible(false);
            }

            else if (wCred->isVisible()) {
                if (cmc(wCred, Button, 0) && isMLBPressed)
                    wCred->setVisible(false);
            }
        }

#undef isMLBPressed
#undef cmc
#undef component
#undef wOpts
#undef wHelp
#undef wCred
#undef wGame
#undef wGrap
#undef wSoun
#undef wCont

    }

    void MainMenu::draw(sf::RenderWindow& rw) {
        title->draw(rw);
        wMenu->draw(rw);
    }

}
