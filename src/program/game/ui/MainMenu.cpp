/**
 * @file src/program/game/ui/MainMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "MainMenu.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Checkbox.hpp"
#include "../../gui/Switch.hpp"
#include "../../gui/ScrollBar.hpp"
#include "../../gui/Text.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"
#include "../../Program.hpp"

#include "../../funcs/strings.hpp"
#include "../../funcs/keys.hpp"

namespace rr
{

    MainMenu::MainMenu() :
      title_  (Text  (sf::Vector2f(0, 0), "PAhAom"             , Resources::font.Pixel       , 100, sf::Color::Yellow)),
      version_(Text  (sf::Vector2f(0, 0), Program::getVersion(), Resources::font.FinalFantasy,  50, sf::Color::Yellow)),
      wMenu_  (Window("", sf::Vector2f(248, 454), sf::Vector2f(25, Settings::graphics.resolution.y/2-225)))
    {
        backTexture_.loadFromFile("data/graphics/menubkg.png");
        background_.setTexture(&backTexture_);
        background_.setSize(sf::Vector2f(Settings::graphics.resolution.y*(16.f/9.f),
                                         Settings::graphics.resolution.y));

        title_  .setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-title_  .getSize().x/2,  10));
        version_.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2-version_.getSize().x/2, 100));

        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.newgame"], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.load"   ], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.options"], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.help"   ], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.credits"], 52);
        wMenu_ += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"   ], 52);
        for (int i=0; i<6; i++)
        {
            wMenu_.getComponent<Button>(i)->setPosition(wMenu_.getPosition() + sf::Vector2f(wMenu_.getSize().x/2 - wMenu_.getComponent<Button>(i)->getSize().x/2, 5+i*75));
        }

        auto wOpts = new Window(Resources::dictionary["gui.button.options"], sf::Vector2f(330, 405), sf::Vector2f(Settings::graphics.resolution.x/2-165,
                                                                                                                  Settings::graphics.resolution.y/2-202.5));
        {
            *wOpts += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.game"     ], 52);
            *wOpts += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.graphical"], 52);
            *wOpts += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.sound"    ], 52);
            *wOpts += new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.controls" ], 52);
            for (int i=0; i<4; i++) {
                wOpts->getComponent<Button>(i)->setPosition(wOpts->getPosition()+sf::Vector2f(wOpts->getSize().x/2 - wOpts->getComponent<Button>(i)->getSize().x/2, 30+i*75));
            }

            auto bSave = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.save"], 30);
            auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                 bSave->setPosition(sf::Vector2f(wOpts->getSize().x/2 - (bSave->getSize().x + bQuit->getSize().x+5)/2, 350));
                 bQuit->setPosition(sf::Vector2f(bSave->getSize().x+5, 0) + bSave->getPosition());

            auto wGame = new Window(Resources::dictionary["gui.button.game"], sf::Vector2f(340, 354),
                                    sf::Vector2f(Settings::graphics.resolution.x-365, Settings::graphics.resolution.y/2-177));
            {
                 *wGame += new Text(sf::Vector2f(10, 30), Resources::dictionary["gui.text.language"], Resources::font.Unifont, 20);

                 auto swLanguage = new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 60));
                      swLanguage->addOption("ENGLISH");
                      swLanguage->addOption("POLSKI");
                      swLanguage->addOption(L"PAHAOMCÉQŨ");
                      if      (  Settings::game.language == "en"
                               ) swLanguage->setCurrentOption("ENGLISH");
                      else if (  Settings::game.language == "pl"
                               ) swLanguage->setCurrentOption("POLSKI");
                      else if (  Settings::game.language == "fc"
                               ) swLanguage->setCurrentOption(L"PAHAOMCÉQŨ");

                auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                     bQuit->setPosition(sf::Vector2f(wGame->getSize().x/2 - bQuit->getSize().x/2,
                                                     wGame->getSize().y   - bQuit->getSize().y-10));

                (*wGame += swLanguage) += bQuit;
            }

            auto wGrap = new Window(Resources::dictionary["gui.button.graphical"], sf::Vector2f(340, 434), sf::Vector2f(Settings::graphics.resolution.x   - 365,
                                                                                                                        Settings::graphics.resolution.y/2 - 217));
            {
                *wGrap += new Text(sf::Vector2f(20, 30), Resources::dictionary["gui.text.resolution"], Resources::font.Unifont, 20);

                auto swResolution = new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 60));
                     swResolution->addOption("1280x720");
                     swResolution->addOption("1280x1024");
                     swResolution->addOption("1366x768");
                     swResolution->addOption("1440x900");
                     swResolution->addOption("1600x900");
                     swResolution->addOption("1920x1080");
                     swResolution->addOption("4096x2160");
                     swResolution->setCurrentOption(std::to_string(Settings::graphics.resolution.x)+"x"+std::to_string(Settings::graphics.resolution.y));

                auto cFullscreen = new Checkbox(sf::Vector2f(15, 170), Resources::dictionary["gui.checkbox.fullscreen"], 15);
                     cFullscreen->check(Settings::graphics.fullscreen);

                auto cVSync = new Checkbox(sf::Vector2f(15, 120), Resources::dictionary["gui.checkbox.vsync"], 15);
                     cVSync->check(Settings::graphics.vsync);

                *wGrap += new Text(sf::Vector2f(20, 295), "ANTIALIASING", Resources::font.Unifont, 20);

                auto swAntialiasing = new Switch(sf::Vector2f(215, 30), sf::Vector2f(20, 325));
                     swAntialiasing->addOption("NONE");
                     swAntialiasing->addOption("x2");
                     swAntialiasing->addOption("x4");
                     swAntialiasing->addOption("x8");
                     if (  Settings::graphics.csettings.antialiasingLevel == 0
                         ) swAntialiasing->setCurrentOption("NONE");
                     else  swAntialiasing->setCurrentOption("x"+std::to_string(Settings::graphics.csettings.antialiasingLevel));

                auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                     bQuit->setPosition(sf::Vector2f(wGrap->getSize().x/2 - bQuit->getSize().x/2, 
                                                     wGrap->getSize().y   - bQuit->getSize().y-10));

                ((((*wGrap += swResolution) += cFullscreen) += cVSync) += swAntialiasing) += bQuit;
            }

            auto wSoun = new Window(Resources::dictionary["gui.button.sound"], sf::Vector2f(300, 330), sf::Vector2f(Settings::graphics.resolution.x   - 325,
                                                                                                                    Settings::graphics.resolution.y/2 - 165));
            {
                *wSoun += new Text(sf::Vector2f(20, 40), Resources::dictionary["gui.text.music"], Resources::font.Unifont);
                auto sbMusic = new ScrollBar(ScrollBar::HORIZONTAL, sf::Vector2f(20, 85), 175);
                     sbMusic->setValue(Settings::sound.music_volume);
                auto cbMusic = new Checkbox(sf::Vector2f(175, 40), Resources::dictionary["gui.text.mute"], 20);
                     cbMusic->check(Settings::sound.music_muted);

                *wSoun += new Text(sf::Vector2f(20, 160), Resources::dictionary["gui.text.effects"], Resources::font.Unifont);
                auto sbEffects = new ScrollBar(ScrollBar::HORIZONTAL, sf::Vector2f(20, 205), 175);
                     sbEffects->setValue(Settings::sound.effects_volume);
                auto cbEffects = new Checkbox(sf::Vector2f(175, 160), Resources::dictionary["gui.text.mute"], 20);
                     cbEffects->check(Settings::sound.effects_muted);

                auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                     bQuit->setPosition(sf::Vector2f(wSoun->getSize().x/2 - bQuit->getSize().x/2,
                                                     wSoun->getSize().y   - bQuit->getSize().y-10));

                ((((*wSoun += sbMusic) += cbMusic) += sbEffects) += cbEffects) += bQuit;
            }

            auto wCont = new Window(Resources::dictionary["gui.button.controls"], sf::Vector2f(400, 570), sf::Vector2f(Settings::graphics.resolution.x   - 425,
                                                                                                                       Settings::graphics.resolution.y/2 - 285));
            {
                *wCont += new Text(sf::Vector2f(20, 25), Resources::dictionary["gui.text.move_up"          ]+"\n"
                                                        +Resources::dictionary["gui.text.move_down"        ]+"\n"
                                                        +Resources::dictionary["gui.text.move_left"        ]+"\n"
                                                        +Resources::dictionary["gui.text.move_right"       ]+"\n"
                                                        +Resources::dictionary["gui.text.interact"         ]+"\n"
                                                        +Resources::dictionary["gui.text.attack"           ]+"\n"
                                                        +Resources::dictionary["gui.text.open_inventory"   ]+"\n"
                                                        +Resources::dictionary["gui.text.open_attributes"  ]+"\n"
                                                        +Resources::dictionary["gui.text.open_journal"     ]+"\n"
                                                        +Resources::dictionary["gui.text.open_map"         ]+"\n"
                                                        +Resources::dictionary["gui.text.open_bookOfSpells"]+"\n"
                                                        +Resources::dictionary["gui.text.useslot_1"        ]+"\n"
                                                        +Resources::dictionary["gui.text.useslot_2"        ]+"\n"
                                                        +Resources::dictionary["gui.text.useslot_3"        ]+"\n"
                                                        +Resources::dictionary["gui.text.useslot_4"        ]+"\n"
                                                        +Resources::dictionary["gui.text.useslot_5"        ]+"\n", Resources::font.Unifont, 28);

                *wCont += new Button(sf::Vector2f(320,  27.5f), getKeyName(Settings::keys.move_up          ), 20);
                *wCont += new Button(sf::Vector2f(320,  57.5f), getKeyName(Settings::keys.move_down        ), 20);
                *wCont += new Button(sf::Vector2f(320,  88.0f), getKeyName(Settings::keys.move_left        ), 20);
                *wCont += new Button(sf::Vector2f(320, 118.0f), getKeyName(Settings::keys.move_right       ), 20);
                *wCont += new Button(sf::Vector2f(320, 148.5f), getKeyName(Settings::keys.interact         ), 20);
                *wCont += new Button(sf::Vector2f(320, 178.5f), getKeyName(Settings::keys.attack           ), 20);
                *wCont += new Button(sf::Vector2f(320, 209.0f), getKeyName(Settings::keys.open_inventory   ), 20);
                *wCont += new Button(sf::Vector2f(320, 239.0f), getKeyName(Settings::keys.open_attributes  ), 20);
                *wCont += new Button(sf::Vector2f(320, 269.5f), getKeyName(Settings::keys.open_journal     ), 20);
                *wCont += new Button(sf::Vector2f(320, 299.5f), getKeyName(Settings::keys.open_map         ), 20);
                *wCont += new Button(sf::Vector2f(320, 330.5f), getKeyName(Settings::keys.open_bookOfSpells), 20);
                *wCont += new Button(sf::Vector2f(320, 360.0f), getKeyName(Settings::keys.useslot_1        ), 20);
                *wCont += new Button(sf::Vector2f(320, 390.0f), getKeyName(Settings::keys.useslot_2        ), 20);
                *wCont += new Button(sf::Vector2f(320, 420.5f), getKeyName(Settings::keys.useslot_3        ), 20);
                *wCont += new Button(sf::Vector2f(320, 450.5f), getKeyName(Settings::keys.useslot_4        ), 20);
                *wCont += new Button(sf::Vector2f(320, 480.5f), getKeyName(Settings::keys.useslot_5        ), 20);

                auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                     bQuit->setPosition(sf::Vector2f(wCont->getSize().x/2 - bQuit->getSize().x/2,
                                                     wCont->getSize().y   - bQuit->getSize().y-10));

                auto wWait = new Window("", sf::Vector2f(310, 50), (sf::Vector2f) (Settings::graphics.resolution/2u + sf::Vector2u(-155, 290)), sf::Color::Red);
                    *wWait += new Text(Resources::dictionary["gui.text.press_a_key"], Resources::font.Unifont, 30);

                (*wCont |= wWait) += bQuit;
            }
            (((((*wOpts |= wGame) |= wGrap) |= wSoun) |= wCont) += bSave) += bQuit;
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

        auto wCred = new Window(Resources::dictionary["gui.button.credits"], sf::Vector2f(485, 465), sf::Vector2f(Settings::graphics.resolution.x-510,
                                                                                                                  Settings::graphics.resolution.y/2-232.5f));
        {
            *wCred += new Text(sf::Vector2f(20,  20), Resources::dictionary["gui.text.programming"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0,  50),  L"\tAdam 'Adanos' Gąsior", Resources::font.Unifont, 25, sf::Color::Yellow);

            *wCred += new Text(sf::Vector2f(20,  80), Resources::dictionary["gui.button.graphical"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0, 110), "\tJan Lewandowski", Resources::font.Unifont, 25, sf::Color::Yellow);
            *wCred += new Text(sf::Vector2f( 0, 135), L"\tKamil 'Kwasior' Kwaśnik", Resources::font.Unifont, 25, sf::Color::Yellow);

            *wCred += new Text(sf::Vector2f(20, 165), Resources::dictionary["gui.text.soundtrack"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0, 195), L"\tKacper 'Kacepru' Smoleń", Resources::font.Unifont, 25, sf::Color::Yellow);

            *wCred += new Text(sf::Vector2f(20, 225), Resources::dictionary["gui.text.literary_support"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0, 255), "\tDominik 'Marco' Otmianowski", Resources::font.Unifont, 25, sf::Color::Yellow);

            *wCred += new Text(sf::Vector2f(20, 285), Resources::dictionary["gui.text.testers"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0, 315), "\tJakub Szewczyk", Resources::font.Unifont, 25, sf::Color::Yellow);

            *wCred += new Text(sf::Vector2f(20, 345), Resources::dictionary["gui.text.usedlib"], Resources::font.Unifont, 30);
            *wCred += new Text(sf::Vector2f( 0, 375), "\tSFML 2.3.2", Resources::font.Unifont, 25, sf::Color::Yellow);

            auto wQuit = new Button(sf::Vector2f(5, 255), Resources::dictionary["gui.button.quit"], 30);
                 wQuit->setPosition(sf::Vector2f(wCred->getSize().x/2 - wQuit->getSize().x/2,
                                                 wCred->getSize().y   - wQuit->getSize().y-10));

            *wCred += wQuit;
        }

        ((wMenu_ |= wOpts) |= wHelp) |= wCred;
        wMenu_.setVisible(true);
    }

    void
    MainMenu::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        auto wOpts = wMenu_.getComponent<Window>(0);
        auto wGame = wOpts->getComponent<Window>(0);
        auto wGrap = wOpts->getComponent<Window>(1);
        auto wSoun = wOpts->getComponent<Window>(2);
        auto wCont = wOpts->getComponent<Window>(3);
        auto wWait = wCont->getComponent<Window>(0);
        auto wHelp = wMenu_.getComponent<Window>(1);
        auto wCred = wMenu_.getComponent<Window>(2);

        if (wMenu_.isVisible())
        {
            if (!wOpts->isVisible() && !wHelp->isVisible() && !wCred->isVisible())
            {
                if (  wMenu_.getComponent<Button>(0)->isPressed(rw, e)
                    ) g->loadNewGame();
                if (  wMenu_.getComponent<Button>(1)->isPressed(rw, e)
                    ) if (g->load()) g->start(true);
                if (  wMenu_.getComponent<Button>(2)->isPressed(rw, e)
                    ) wOpts->setVisible(true);
                if (  wMenu_.getComponent<Button>(3)->isPressed(rw, e)
                    ) wHelp->setVisible(true);
                if (  wMenu_.getComponent<Button>(4)->isPressed(rw, e)
                    ) wCred->setVisible(true);
                if (  wMenu_.getComponent<Button>(5)->isPressed(rw, e)
                    ) rw.close();
            }

            else if (wOpts->isVisible())
            {
                if (!wGame->isVisible() && !wGrap->isVisible() && !wSoun->isVisible() && !wCont->isVisible())
                {
                    if (  wOpts->getComponent<Button>(0)->isPressed(rw, e)
                        ) wGame->setVisible(true);
                    if (  wOpts->getComponent<Button>(1)->isPressed(rw, e)
                        ) wGrap->setVisible(true);
                    if (  wOpts->getComponent<Button>(2)->isPressed(rw, e)
                        ) wSoun->setVisible(true);
                    if (  wOpts->getComponent<Button>(3)->isPressed(rw, e)
                        ) wCont->setVisible(true);
                    if (wOpts->getComponent<Button>(4)->isPressed(rw, e))
                    {
                        puts(">Saving the settings...");
                        if      (  wGame->getComponent<Switch>(0)->getCurrentOption() == "ENGLISH"
                                 ) Settings::game.language = "en";
                        else if (  wGame->getComponent<Switch>(0)->getCurrentOption() == "POLSKI"
                                 ) Settings::game.language = "pl";
                        else if (  wGame->getComponent<Switch>(0)->getCurrentOption() == L"PAHAOMCÉQŨ"
                                 ) Settings::game.language = "fc";

                        std::vector<std::string> splitted = split(wtoa(wGrap->getComponent<Switch>(0)->getCurrentOption()), 'x');

                        Settings::graphics.resolution = sf::Vector2u(stoi(splitted[0]), stoi(splitted[1]));
                        Settings::graphics.fullscreen = wGrap->getComponent<Checkbox>(0)->isChecked();
                        Settings::graphics.vsync      = wGrap->getComponent<Checkbox>(1)->isChecked();

                        if      (  wGrap->getComponent<Switch>(1)->getCurrentOption() == "x2"
                                 ) Settings::graphics.csettings.antialiasingLevel = 2;
                        else if (  wGrap->getComponent<Switch>(1)->getCurrentOption() == "x4"
                                 ) Settings::graphics.csettings.antialiasingLevel = 4;
                        else if (  wGrap->getComponent<Switch>(1)->getCurrentOption() == "x8"
                                 ) Settings::graphics.csettings.antialiasingLevel = 8;
                        else       Settings::graphics.csettings.antialiasingLevel = 0;

                        Settings::sound.music_muted    = wSoun->getComponent<Checkbox >(0)->isChecked();
                        Settings::sound.music_volume   = wSoun->getComponent<ScrollBar>(0)->getValue();
                        Settings::sound.effects_muted  = wSoun->getComponent<Checkbox >(1)->isChecked();
                        Settings::sound.effects_volume = wSoun->getComponent<ScrollBar>(1)->getValue();

                        g->getAudioManager()->setMusicVolume(Settings::sound.music_muted ? 0
                                                                                         : Settings::sound.music_volume);

                        Settings::keys.move_up           = getKeyCode(wCont->getComponent<Button>( 0)->getText().getString());
                        Settings::keys.move_down         = getKeyCode(wCont->getComponent<Button>( 1)->getText().getString());
                        Settings::keys.move_left         = getKeyCode(wCont->getComponent<Button>( 2)->getText().getString());
                        Settings::keys.move_right        = getKeyCode(wCont->getComponent<Button>( 3)->getText().getString());
                        Settings::keys.interact          = getKeyCode(wCont->getComponent<Button>( 4)->getText().getString());
                        Settings::keys.attack            = getKeyCode(wCont->getComponent<Button>( 5)->getText().getString());
                        Settings::keys.open_inventory    = getKeyCode(wCont->getComponent<Button>( 6)->getText().getString());
                        Settings::keys.open_attributes   = getKeyCode(wCont->getComponent<Button>( 7)->getText().getString());
                        Settings::keys.open_journal      = getKeyCode(wCont->getComponent<Button>( 8)->getText().getString());
                        Settings::keys.open_map          = getKeyCode(wCont->getComponent<Button>( 9)->getText().getString());
                        Settings::keys.open_bookOfSpells = getKeyCode(wCont->getComponent<Button>(10)->getText().getString());
                        Settings::keys.useslot_1         = getKeyCode(wCont->getComponent<Button>(11)->getText().getString());
                        Settings::keys.useslot_2         = getKeyCode(wCont->getComponent<Button>(12)->getText().getString());
                        Settings::keys.useslot_3         = getKeyCode(wCont->getComponent<Button>(13)->getText().getString());
                        Settings::keys.useslot_4         = getKeyCode(wCont->getComponent<Button>(14)->getText().getString());
                        Settings::keys.useslot_5         = getKeyCode(wCont->getComponent<Button>(15)->getText().getString());

                        Settings::save();

                        puts(">Done.");
                        wOpts->setVisible(false);
                    }

                    if (wOpts->getComponent<Button>(5)->isPressed(rw, e))
                    {
                        if      (  Settings::game.language == "en"
                                 ) wGame->getComponent<Switch>(0)->setCurrentOption("ENGLISH");
                        else if (  Settings::game.language == "pl"
                                 ) wGame->getComponent<Switch>(0)->setCurrentOption("POLSKI");
                        else if (  Settings::game.language == "fc"
                                 ) wGame->getComponent<Switch>(0)->setCurrentOption(L"PAHAOMCÉQŨ");

                        wGrap->getComponent<Switch>(0)->setCurrentOption(std::to_string(Settings::graphics.resolution.x)+"x"+std::to_string(Settings::graphics.resolution.y));
                        wGrap->getComponent<Checkbox>(0)->check(Settings::graphics.fullscreen);
                        wGrap->getComponent<Checkbox>(1)->check(Settings::graphics.vsync);
                        if (  Settings::graphics.csettings.antialiasingLevel == 0
                            ) wGrap->getComponent<Switch>(1)->setCurrentOption("NONE");
                        else  wGrap->getComponent<Switch>(1)->setCurrentOption("x"+std::to_string(Settings::graphics.csettings.antialiasingLevel));

                        wSoun->getComponent<Checkbox >(0)->check   (Settings::sound.music_muted);
                        wSoun->getComponent<ScrollBar>(0)->setValue(Settings::sound.music_volume);
                        wSoun->getComponent<Checkbox >(1)->check   (Settings::sound.effects_muted);
                        wSoun->getComponent<ScrollBar>(1)->setValue(Settings::sound.effects_volume);

                        g->getAudioManager()->setMusicVolume(Settings::sound.music_muted ? 0
                                                                                         : Settings::sound.music_volume);

                        wCont->getComponent<Button>( 0)->getText().setString(getKeyName(Settings::keys.move_up));
                        wCont->getComponent<Button>( 1)->getText().setString(getKeyName(Settings::keys.move_down));
                        wCont->getComponent<Button>( 2)->getText().setString(getKeyName(Settings::keys.move_left));
                        wCont->getComponent<Button>( 3)->getText().setString(getKeyName(Settings::keys.move_right));
                        wCont->getComponent<Button>( 4)->getText().setString(getKeyName(Settings::keys.interact));
                        wCont->getComponent<Button>( 5)->getText().setString(getKeyName(Settings::keys.attack));
                        wCont->getComponent<Button>( 6)->getText().setString(getKeyName(Settings::keys.open_inventory));
                        wCont->getComponent<Button>( 7)->getText().setString(getKeyName(Settings::keys.open_attributes));
                        wCont->getComponent<Button>( 8)->getText().setString(getKeyName(Settings::keys.open_journal));
                        wCont->getComponent<Button>( 9)->getText().setString(getKeyName(Settings::keys.open_map));
                        wCont->getComponent<Button>(10)->getText().setString(getKeyName(Settings::keys.open_bookOfSpells));
                        wCont->getComponent<Button>(11)->getText().setString(getKeyName(Settings::keys.useslot_1));
                        wCont->getComponent<Button>(12)->getText().setString(getKeyName(Settings::keys.useslot_2));
                        wCont->getComponent<Button>(13)->getText().setString(getKeyName(Settings::keys.useslot_3));
                        wCont->getComponent<Button>(14)->getText().setString(getKeyName(Settings::keys.useslot_4));
                        wCont->getComponent<Button>(15)->getText().setString(getKeyName(Settings::keys.useslot_5));

                        wOpts->setVisible(false);
                    }
                }

                else if (wGame->isVisible())
                {
                    wGame->getComponent<Switch>(0)->buttonEvents(rw, e);
                    if (  wGame->getComponent<Button>(0)->isPressed(rw, e)
                        ) wGame->setVisible(false);
                }

                else if (wGrap->isVisible())
                {
                    for (unsigned i=0; i<2; i++)
                    {
                        if (wGrap->getComponent<Checkbox>(i)->isPressed(rw, e))
                        {
                            if ( !wGrap->getComponent<Checkbox>(i)->isChecked()
                                ) wGrap->getComponent<Checkbox>(i)->check(true);
                            else  wGrap->getComponent<Checkbox>(i)->check(false);
                        }
                    }
                    wGrap->getComponent<Switch>(0)->buttonEvents(rw, e);
                    wGrap->getComponent<Switch>(1)->buttonEvents(rw, e);
                    if (  wGrap->getComponent<Button>(0)->isPressed(rw, e)
                        ) wGrap->setVisible(false);
                }

                else if (wSoun->isVisible())
                {
                    for (int i=0; i<2; i++)
                    {
                        if (wSoun->getComponent<Checkbox>(i)->isPressed(rw, e))
                        {
                            if ( !wSoun->getComponent<Checkbox>(i)->isChecked()
                                ) wSoun->getComponent<Checkbox>(i)->check(true);
                            else  wSoun->getComponent<Checkbox>(i)->check(false);
                        }
                        wSoun->getComponent<ScrollBar>(0)->buttonEvents(rw, e);
                        wSoun->getComponent<ScrollBar>(1)->buttonEvents(rw, e);

                        g->getAudioManager()->setMusicVolume(wSoun->getComponent<Checkbox>(0)->isChecked() ? 0
                                                                                                           : (float) wSoun->getComponent<ScrollBar>(0)->getValue());
                    }
                    if (  wSoun->getComponent<Button>(0)->isPressed(rw, e)
                        ) wSoun->setVisible(false);
                }

                else if (wCont->isVisible())
                {
                    for (int i=0; i<16; i++)
                    {
                        if (!wWait->isVisible() && wCont->getComponent<Button>(i)->isPressed(rw, e))
                        {
                            wWait->setVisible(true);
                            wWait->setParentComponent(wCont->getComponent<Button>(i));
                        }
                        else if (wWait->isVisible() && e.type == sf::Event::KeyPressed)
                        {
                            if (  e.key.code != sf::Keyboard::Escape
                                ) ((Button*) wWait->getParentComponent())->setText(getKeyName(e.key.code));
                            wWait->setParentComponent(wCont);
                            wWait->setVisible(false);
                        }
                    }
                    if ( !wWait->isVisible() && wCont->getComponent<Button>(16)->isPressed(rw, e)
                        ) wCont->setVisible(false);
                }

            }

            else if (wHelp->isVisible())
            {
                if (  wHelp->getComponent<Button>(0)->isPressed(rw, e)
                    ) wHelp->setVisible(false);
            }

            else if (wCred->isVisible())
            {
                if (  wCred->getComponent<Button>(0)->isPressed(rw, e)
                    ) wCred->setVisible(false);
            }
        }

    }

    void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(background_, states);
        target.draw(title_     , states);
        target.draw(version_   , states);
        target.draw(wMenu_     , states);
    }

}
