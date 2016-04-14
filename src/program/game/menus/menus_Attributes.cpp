/**
 * @file src/program/game/menus/menus_Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"

extern rr::Dictionary dictionary;
extern rr::Resources  resources;

namespace rr {

    Attributes::Attributes(sf::RenderWindow& rw) {
        shadow.setSize((sf::Vector2f)rw.getSize());
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 128));

#define component(w, c, i) w->getComponent<c>(i)

        wAttr = new Window(dictionary.gui.window.attributes, sf::Vector2f(900, 310), (sf::Vector2f)rw.getSize()/2.f-sf::Vector2f(450, 155));
            wAttr->addComponent(new Text(sf::Vector2f(10,  25), dictionary.player.attributes.health        +":\n"
                                                               +"MANA:\n"
                                                               +dictionary.player.attributes.strength      +":\n"
                                                               +dictionary.player.attributes.dexterity     +":\n"
                                                               +dictionary.player.attributes.experience    +":\n"
                                                               +dictionary.player.attributes.level         +":\n"
                                                               +dictionary.player.attributes.skill_points  +":"  , resources.font.Unifont, 30), true); // attrs
            wAttr->addComponent(new Text(sf::Vector2f(400, 25), "", resources.font.Unifont, 30, sf::Color::Yellow), true);             // values
            wAttr->addComponent(new Text(sf::Vector2f(600, 25), "", resources.font.Unifont, 30, sf::Color::Green),  true);             // skills
            wAttr->addComponent(new Button(sf::Vector2f(0, 0), dictionary.gui.button.quit, 30), true);
                component(wAttr, Button, 0)->setPosition(sf::Vector2f(wAttr->getPosition().x+wAttr->getSize().x/2-component(wAttr, Button, 0)->getSize().x/2,
                                                                      wAttr->getPosition().y+wAttr->getSize().y-component(wAttr, Button, 0)->getSize().y-10));

#undef component

    }

    Attributes::~Attributes() {
        delete wAttr;
    }

    void Attributes::open() {
        wAttr->setVisible(true);
    }

    void Attributes::close() {
        wAttr->setVisible(false);
    }

    void Attributes::update(Player* p) {

#define component(w, c, i) w->getComponent<c>(i)

        component(wAttr, Text, 1)->setString(std::to_string((int)p->getAttributes().health     )+"/"+std::to_string((int)p->getAttributes().maxHealth)+"\n"
                                            +std::to_string((int)p->getAttributes().mana       )+"/"+std::to_string((int)p->getAttributes().maxMana  )+"\n"
                                            +std::to_string((int)p->getAttributes().strength   )                                                      +"\n"
                                            +std::to_string((int)p->getAttributes().dexterity  )                                                      +"\n"
                                            +std::to_string((int)p->getAttributes().experience )+"/"+std::to_string((int)p->getAttributes().nextLevel)+"\n"
                                            +std::to_string((int)p->getAttributes().level      )                                                      +"\n"
                                            +std::to_string((int)p->getAttributes().skillPoints));

        component(wAttr, Text, 2)->setString((p->getAttributes().crafting               ? dictionary.player.skills.crafting               : sf::String("-"))
                                       +"\n"+(p->getAttributes().alchemy                ? dictionary.player.skills.alchemy                : sf::String("-"))
                                       +"\n"+(p->getAttributes().cold_weapon_mastery    ? dictionary.player.skills.cold_weapon_mastery    : sf::String("-"))
                                       +"\n"+(p->getAttributes().ranged_weapon_mastery  ? dictionary.player.skills.ranged_weapon_mastery  : sf::String("-"))
                                       +"\n"+(p->getAttributes().better_sight           ? dictionary.player.skills.better_sight           : sf::String("-")));

#undef component

    }

    void Attributes::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, x) w->getComponent<c>(x)

        if (wAttr->isVisible()) {
            if (component(wAttr, Button, 0)->isPressed(rw, e)) {
                wAttr->setVisible(false);
                g->pause(false);
            }
        }

#undef component

    }

    void Attributes::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        wAttr->draw(rw);
    }

    bool Attributes::isOpen() {
        return wAttr->isVisible();
    }

}
