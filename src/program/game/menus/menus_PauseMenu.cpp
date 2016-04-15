/**
 * @file src/program/game/menus/menus_PauseMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

extern rr::Settings   settings;
extern rr::Resources  resources;

namespace rr {

    PauseMenu::PauseMenu(sf::RenderWindow& rw) {
        shadow.setSize((sf::Vector2f)rw.getSize());
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        title = new Text(sf::Vector2f(0, 0), "PAhAom", resources.font.Pixel, 100, sf::Color::Yellow);
        title->setPosition(sf::Vector2f(rw.getSize().x/2-title->getSize().x/2, 10));

        wMenu = new Window("", sf::Vector2f(244, 306), sf::Vector2f(25, rw.getSize().y/2-153));
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.resume"],  52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.options"], 52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.help"],    52), true);
            wMenu->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"],    52), true);
            for (int i=0; i<4; i++)
                component(wMenu, Button, i)->setPosition(wMenu->getPosition()+sf::Vector2f(wMenu->getSize().x/2-component(wMenu, Button, i)->getSize().x/2, 5+i*75));

            wMenu->addComponent(new Window(resources.dictionary["gui.button.options"], sf::Vector2f(330, 405),
                                           sf::Vector2f(rw.getSize().x/2-165, rw.getSize().y/2-202.5)), false);

#define wOpts component(wMenu, Window, 0)

                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.game"],      52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.graphical"], 52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.sound"],     52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.controls"],  52), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.save"],      30), true);
                wOpts->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"],      30), true);
                for (int i=0; i<4; i++)
                    component(wOpts, Button, i)->setPosition(wOpts->getPosition()+sf::Vector2f(wOpts->getSize().x/2-component(wOpts, Button, i)->getSize().x/2, 30+i*75));
                component(wOpts, Button, 4)->setPosition(wOpts->getPosition()+sf::Vector2f(wOpts->getSize().x/2-(component(wOpts, Button, 4)->getSize().x+component(wOpts, Button, 5)->getSize().x+5)/2, 350));
                component(wOpts, Button, 5)->setPosition(component(wOpts, Button, 4)->getPosition()+sf::Vector2f(component(wOpts, Button, 4)->getSize().x+5, 0));

                wOpts->addComponent(new Window(resources.dictionary["gui.button.game"], sf::Vector2f(340, 354),
                                               sf::Vector2f(rw.getSize().x-365, rw.getSize().y/2-177)), false);

#define wGame component(wOpts, Window, 0)

                    wGame->addComponent(new Text(sf::Vector2f(10, 30), resources.dictionary["gui.text.language"], resources.font.Unifont, 20), true);

                    wGame->addComponent(new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 60)), true);
                        component(wGame, Switch, 0)->addOption("ENGLISH");
                        component(wGame, Switch, 0)->addOption("POLSKI");
                        component(wGame, Switch, 0)->addOption(L"DNQUBIÑHBI");
                        if      (settings.game.language == "en")
                            component(wGame, Switch, 0)->setCurrentOption("ENGLISH");
                        else if (settings.game.language == "pl")
                            component(wGame, Switch, 0)->setCurrentOption("POLSKI");
                        else if (settings.game.language == "fc")
                            component(wGame, Switch, 0)->setCurrentOption(L"DNQUBIÑHBI");

                    wGame->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
                    component(wGame, Button, 0)->setPosition(sf::Vector2f(wGame->getPosition().x+wGame->getSize().x/2-component(wGame, Button, 0)->getSize().x/2,
                                                                          wGame->getPosition().y+wGame->getSize().y-component(wGame, Button, 0)->getSize().y-10));

#undef wGame

                wOpts->addComponent(new Window(resources.dictionary["gui.button.graphical"], sf::Vector2f(340, 434),
                                               sf::Vector2f(rw.getSize().x-365, rw.getSize().y/2-217)), false);

#define wGrap component(wOpts, Window, 1)

                    wGrap->addComponent(new Text(sf::Vector2f(20, 30), resources.dictionary["gui.text.resolution"], resources.font.Unifont, 20), true);

                    wGrap->addComponent(new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 60)), true);
                        component(wGrap, Switch, 0)->addOption("1280x720");
                        component(wGrap, Switch, 0)->addOption("1440x900");
                        component(wGrap, Switch, 0)->addOption("1600x900");
                        component(wGrap, Switch, 0)->addOption("1920x1080");
                        component(wGrap, Switch, 0)->setCurrentOption(std::to_wstring(settings.graphics.resolution.x)+L"x"+std::to_wstring(settings.graphics.resolution.y));

                    wGrap->addComponent(new Checkbox(sf::Vector2f(15, 170), resources.dictionary["gui.checkbox.fullscreen"], 15), true);
                        component(wGrap, Checkbox, 0)->check(settings.graphics.fullscreen);

                    wGrap->addComponent(new Checkbox(sf::Vector2f(15, 120), resources.dictionary["gui.checkbox.vsync"], 15), true);
                        component(wGrap, Checkbox, 1)->check(settings.graphics.vsync);

                    wGrap->addComponent(new Text(sf::Vector2f(20, 295), "ANTIALIASING", resources.font.Unifont, 20), true);

                    wGrap->addComponent(new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 325)), true);
                        component(wGrap, Switch, 1)->addOption("NONE");
                        component(wGrap, Switch, 1)->addOption("x2");
                        component(wGrap, Switch, 1)->addOption("x4");
                        component(wGrap, Switch, 1)->addOption("x8");
                        if (settings.graphics.csettings.antialiasingLevel == 0)
                            component(wGrap, Switch, 1)->setCurrentOption("NONE");
                        else
                            component(wGrap, Switch, 1)->setCurrentOption("x"+std::to_string(settings.graphics.csettings.antialiasingLevel));

                    wGrap->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
                    component(wGrap, Button, 0)->setPosition(sf::Vector2f(wGrap->getPosition().x+wGrap->getSize().x/2-component(wGrap, Button, 0)->getSize().x/2,
                                                                          wGrap->getPosition().y+wGrap->getSize().y-component(wGrap, Button, 0)->getSize().y-10));

#undef wGrap

                wOpts->addComponent(new Window(resources.dictionary["gui.button.sound"], sf::Vector2f(300, 330),
                                               sf::Vector2f(rw.getSize().x-325, rw.getSize().y/2-165)), false);

#define wSoun component(wOpts, Window, 2)

                    wSoun->addComponent(new Text(sf::Vector2f(20, 40), resources.dictionary["gui.text.music"], resources.font.Unifont), true);
                    wSoun->addComponent(new ScrollBar(ScrollBar::HORIZONTAL, sf::Vector2f(20, 85), 175), true);
                    wSoun->addComponent(new Checkbox(sf::Vector2f(175, 40), resources.dictionary["gui.text.mute"], 20), true);
                    component(wSoun, Checkbox, 0)->check(settings.sound.music_muted);
                    component(wSoun, ScrollBar,   0)->setValue(settings.sound.music_volume);

                    wSoun->addComponent(new Text(sf::Vector2f(20, 160), resources.dictionary["gui.text.effects"], resources.font.Unifont), true);
                    wSoun->addComponent(new ScrollBar(ScrollBar::HORIZONTAL, sf::Vector2f(20, 205), 175), true);
                    wSoun->addComponent(new Checkbox(sf::Vector2f(175, 160), resources.dictionary["gui.text.mute"], 20), true);
                    component(wSoun, Checkbox, 1)->check(settings.sound.effects_muted);
                    component(wSoun, ScrollBar,   1)->setValue(settings.sound.effects_volume);

                    wSoun->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
                    component(wSoun, Button, 0)->setPosition(sf::Vector2f(wSoun->getPosition().x+wSoun->getSize().x/2-component(wSoun, Button, 0)->getSize().x/2,
                                                                          wSoun->getPosition().y+wSoun->getSize().y-component(wSoun, Button, 0)->getSize().y-10));

#undef wSoun

                wOpts->addComponent(new Window(resources.dictionary["gui.button.controls"], sf::Vector2f(400, 550),
                                               sf::Vector2f(rw.getSize().x-425, rw.getSize().y/2-275)), false);

#define wCont component(wOpts, Window, 3)

                    wCont->addComponent(new Text(sf::Vector2f(20, 25), resources.dictionary["gui.text.move_up"        ]+"\n"
                                                                      +resources.dictionary["gui.text.move_down"      ]+"\n"
                                                                      +resources.dictionary["gui.text.move_left"      ]+"\n"
                                                                      +resources.dictionary["gui.text.move_right"     ]+"\n"
                                                                      +resources.dictionary["gui.text.interact"       ]+"\n"
                                                                      +resources.dictionary["gui.text.attack"         ]+"\n"
                                                                      +resources.dictionary["gui.text.pickup"         ]+"\n"
                                                                      +resources.dictionary["gui.text.open_inventory" ]+"\n"
                                                                      +resources.dictionary["gui.text.open_attributes"]+"\n"
                                                                      +resources.dictionary["gui.text.open_quests"    ]+"\n"
                                                                      +resources.dictionary["gui.text.open_map"       ]+"\n"
                                                                      +resources.dictionary["gui.text.useslot_1"      ]+"\n"
                                                                      +resources.dictionary["gui.text.useslot_2"      ]+"\n"
                                                                      +resources.dictionary["gui.text.useslot_3"      ]+"\n"
                                                                      +resources.dictionary["gui.text.useslot_4"      ]+"\n"
                                                                      +resources.dictionary["gui.text.useslot_5"      ]+"\n", resources.font.Unifont, 25), true);
                    for (int i=0; i<16; i++)
                        wCont->addComponent(new Button(sf::Vector2f(300, 27*i+27.5f), "-", 20), true);
                    wCont->addComponent(new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30), true);
                    component(wCont, Button, 16)->setPosition(sf::Vector2f(wCont->getPosition().x+wCont->getSize().x/2-component(wCont, Button, 16)->getSize().x/2,
                                                                          wCont->getPosition().y+wCont->getSize().y-component(wCont, Button, 16)->getSize().y-10));

#undef wCont
#undef wOpts

            wMenu->addComponent(new Window(resources.dictionary["gui.button.help"], sf::Vector2f(325, 454),
                                           sf::Vector2f(rw.getSize().x-350, rw.getSize().y/2-225)), false);

#define wHelp component(wMenu, Window, 1)

                wHelp->addComponent(new Text(sf::Vector2f(20, 25), "Pro tip:",                    resources.font.Unifont, 30, sf::Color::Yellow), true);
                wHelp->addComponent(new Text(sf::Vector2f(20, 55), resources.dictionary["gui.text.killurslf"], resources.font.Unifont, 30, sf::Color::Red),    true);

                wHelp->addComponent(new Button(sf::Vector2f(5, 380), resources.dictionary["gui.button.quit"], 30), true);
                component(wHelp, Button, 0)->setPosition(sf::Vector2f(wHelp->getPosition().x+wHelp->getSize().x/2-component(wHelp, Button, 0)->getSize().x/2,
                                                                      wHelp->getPosition().y+wHelp->getSize().y-component(wHelp, Button, 0)->getSize().y-10));

#undef wHelp
#undef dict
#undef component

    }

    PauseMenu::~PauseMenu() {
        delete title;
        delete wMenu;
    }

    void PauseMenu::open() {
        wMenu->setVisible(true);
    }

    void PauseMenu::close() {

#define component(w, c, i) w->getComponent<c>(i)
#define wOpts component(wMenu, Window, 0)
#define wHelp component(wMenu, Window, 1)
#define wGame component(wOpts, Window, 0)
#define wGrap component(wOpts, Window, 1)
#define wSoun component(wOpts, Window, 2)
#define wCont component(wOpts, Window, 3)

        wMenu->setVisible(false);
        wOpts->setVisible(false);
        wGame->setVisible(false);
        wGrap->setVisible(false);
        wSoun->setVisible(false);
        wCont->setVisible(false);
        wHelp->setVisible(false);

#undef component
#undef wOpts
#undef wHelp
#undef wGame
#undef wGrap
#undef wSoun
#undef wCont

    }

    void PauseMenu::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)
#define wOpts component(wMenu, Window, 0)
#define wGame component(wOpts, Window, 0)
#define wGrap component(wOpts, Window, 1)
#define wSoun component(wOpts, Window, 2)
#define wCont component(wOpts, Window, 3)
#define wHelp component(wMenu, Window, 1)

        if (wMenu->isVisible()) {
            if (!wOpts->isVisible() && !wHelp->isVisible()) {
                if (component(wMenu, Button, 0)->isPressed(rw, e))
                    g->pause(false);
                if (component(wMenu, Button, 1)->isPressed(rw, e))
                    wOpts->setVisible(true);
                if (component(wMenu, Button, 2)->isPressed(rw, e))
                    wHelp->setVisible(true);
                if (component(wMenu, Button, 3)->isPressed(rw, e)) {
                    g->pause(false);
                    g->start(false);
                }
            }


            else if (wOpts->isVisible()) {
                if (!wGame->isVisible() && !wGrap->isVisible() && !wSoun->isVisible() && !wCont->isVisible()) {
                    if (component(wOpts, Button, 0)->isPressed(rw, e))
                        wGame->setVisible(true);

                    if (component(wOpts, Button, 1)->isPressed(rw, e))
                        wGrap->setVisible(true);

                    if (component(wOpts, Button, 2)->isPressed(rw, e))
                        wSoun->setVisible(true);

                    if (component(wOpts, Button, 3)->isPressed(rw, e))
                        wCont->setVisible(true);

                    if (component(wOpts, Button, 4)->isPressed(rw, e)) {
                        puts(">Saving the settings...");
                        if      (component(wGame, Switch, 0)->getCurrentOption() == "ENGLISH")
                            settings.game.language = "en";
                        else if (component(wGame, Switch, 0)->getCurrentOption() == "POLSKI")
                            settings.game.language = "pl";
                        else if (component(wGame, Switch, 0)->getCurrentOption() == L"DNQUBIÑHBI")
                            settings.game.language = "fc";

                        std::vector<std::string> splitted = split(component(wGrap, Switch, 0)->getCurrentOption(), 'x');

                        settings.graphics.resolution = sf::Vector2u(atoi(splitted[0].c_str()), atoi(splitted[1].c_str()));
                        settings.graphics.fullscreen = component(wGrap, Checkbox, 0)->isChecked();
                        settings.graphics.vsync      = component(wGrap, Checkbox, 1)->isChecked();

                        if      (component(wGrap, Switch, 1)->getCurrentOption() == "x2")
                            settings.graphics.csettings.antialiasingLevel = 2;
                        else if (component(wGrap, Switch, 1)->getCurrentOption() == "x4")
                            settings.graphics.csettings.antialiasingLevel = 4;
                        else if (component(wGrap, Switch, 1)->getCurrentOption() == "x8")
                            settings.graphics.csettings.antialiasingLevel = 8;
                        else
                            settings.graphics.csettings.antialiasingLevel = 0;

                        settings.sound.music_muted    = component(wSoun, Checkbox,  0)->isChecked();
                        settings.sound.music_volume   = component(wSoun, ScrollBar, 0)->getValue();
                        settings.sound.effects_muted  = component(wSoun, Checkbox,  1)->isChecked();
                        settings.sound.effects_volume = component(wSoun, ScrollBar, 1)->getValue();

                        settings.print();
                        settings.save ();
                        puts(">Done.");
                        wOpts->setVisible(false);
                    }
                    if (component(wOpts, Button, 5)->isPressed(rw, e)) {
                        if      (settings.game.language == "en")
                            component(wGame, Switch, 0)->setCurrentOption("ENGLISH");
                        else if (settings.game.language == "pl")
                            component(wGame, Switch, 0)->setCurrentOption("POLSKI");
                        else if (settings.game.language == "fc")
                            component(wGame, Switch, 0)->setCurrentOption(L"DNQUBIÑHBI");

                        component(wGrap, Switch, 0)->setCurrentOption(std::to_string(settings.graphics.resolution.x)+"x"+std::to_string(settings.graphics.resolution.y));
                        component(wGrap, Checkbox, 0)->check(settings.graphics.fullscreen);
                        component(wGrap, Checkbox, 1)->check(settings.graphics.vsync);
                        if (settings.graphics.csettings.antialiasingLevel == 0)
                            component(wGrap, Switch, 1)->setCurrentOption("NONE");
                        else
                            component(wGrap, Switch, 1)->setCurrentOption("x"+std::to_string(settings.graphics.csettings.antialiasingLevel));

                        component(wSoun, Checkbox,  0)->check(settings.sound.music_muted);
                        component(wSoun, ScrollBar, 0)->setValue(settings.sound.music_volume);
                        component(wSoun, Checkbox,  1)->check(settings.sound.effects_muted);
                        component(wSoun, ScrollBar, 1)->setValue(settings.sound.effects_volume);

                        wOpts->setVisible(false);
                    }
                }


                else if (wGame->isVisible()) {
                    component(wGame, Switch, 0)->buttonEvents(rw, e);
                    if (component(wGame, Button, 0)->isPressed(rw, e))
                        wGame->setVisible(false);
                }

                else if (wGrap->isVisible()) {
                    for (unsigned i=0; i<2; i++) {
                        if (component(wGrap, Checkbox, i)->isPressed(rw, e)) {
                            if (!component(wGrap, Checkbox, i)->isChecked())
                                component(wGrap, Checkbox, i)->check(true);
                            else
                                component(wGrap, Checkbox, i)->check(false);
                        }
                    }
                    component(wGrap, Switch, 0)->buttonEvents(rw, e);
                    component(wGrap, Switch, 1)->buttonEvents(rw, e);
                    if (component(wGrap, Button, 0)->isPressed(rw, e))
                        wGrap->setVisible(false);
                }

                else if (wSoun->isVisible()) {
                    for (int i=0; i<2; i++) {
                        if (component(wSoun, Checkbox, i)->isPressed(rw, e)) {
                            if (!component(wSoun, Checkbox, i)->isChecked())
                                component(wSoun, Checkbox, i)->check(true);
                            else
                                component(wSoun, Checkbox, i)->check(false);
                        }
                        component(wSoun, ScrollBar, 0)->buttonEvents(rw, e);
                        component(wSoun, ScrollBar, 1)->buttonEvents(rw, e);
                    }
                    if (component(wSoun, Button, 0)->isPressed(rw, e))
                        wSoun->setVisible(false);
                }

                else if (wCont->isVisible()) {
                    for (int i=0; i<16; i++) {
                        if (component(wCont, Button, i)->isPressed(rw, e)) {

                        }
                    }
                    if (component(wCont, Button, 16)->isPressed(rw, e))
                        wCont->setVisible(false);
                }

            }

            else if (wHelp->isVisible()) {
                if (component(wHelp, Button, 0)->isPressed(rw, e))
                    wHelp->setVisible(false);
            }
        }

#undef component
#undef wOpts
#undef wGame
#undef wGrap
#undef wSoun
#undef wCont
#undef wHelp

        }

    void PauseMenu::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        title->draw(rw);
        wMenu->draw(rw);
    }

    bool PauseMenu::isOpen() {
        return wMenu->isVisible();
    }

}
