/**
 * @file src/program/game/menus/menus_Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Attributes::Attributes() {
        _shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        _shadow.setPosition(sf::Vector2f(0, 0));
        _shadow.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        _wAttr = new Window(resources.dictionary["gui.window.attributes"], sf::Vector2f(900, 310), (sf::Vector2f)settings.graphics.resolution/2.f-sf::Vector2f(450, 155));
            *_wAttr += new Text(sf::Vector2f(10,  25), resources.dictionary["player.attributes.health"]        +":\n"
                                                               +"MANA:\n"
                                                               +resources.dictionary["player.attributes.strength"]      +":\n"
                                                               +resources.dictionary["player.attributes.dexterity"]     +":\n"
                                                               +resources.dictionary["player.attributes.experience"]    +":\n"
                                                               +resources.dictionary["player.attributes.level"]         +":\n"
                                                               +resources.dictionary["player.attributes.skill_points"]  +":"  , resources.font.Unifont, 30); // attrs
            *_wAttr += new Text(sf::Vector2f(400, 25), "", resources.font.Unifont, 30, sf::Color::Yellow);             // values
            *_wAttr += new Text(sf::Vector2f(600, 25), "", resources.font.Unifont, 30, sf::Color::Green);              // skills
            *_wAttr += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
                component(_wAttr, Button, 0)->setPosition(sf::Vector2f(_wAttr->getPosition().x+_wAttr->getSize().x/2-component(_wAttr, Button, 0)->getSize().x/2,
                                                                      _wAttr->getPosition().y+_wAttr->getSize().y-component(_wAttr, Button, 0)->getSize().y-10));

#undef component

    }

    Attributes::~Attributes() {
        delete _wAttr;
    }

    void Attributes::open() {
        _wAttr->setVisible(true);
    }

    void Attributes::close() {
        _wAttr->setVisible(false);
    }

    void Attributes::update(Player* p) {

#define component(w, c, i) w->getComponent<c>(i)

        component(_wAttr, Text, 1)->setString(std::to_string((int)p->getAttributes().health     )+"/"+std::to_string((int)p->getAttributes().maxHealth)+"\n"
                                             +std::to_string((int)p->getAttributes().mana       )+"/"+std::to_string((int)p->getAttributes().maxMana  )+"\n"
                                             +std::to_string((int)p->getAttributes().strength   )                                                      +"\n"
                                             +std::to_string((int)p->getAttributes().dexterity  )                                                      +"\n"
                                             +std::to_string((int)p->getAttributes().experience )+"/"+std::to_string((int)p->getAttributes().nextLevel)+"\n"
                                             +std::to_string((int)p->getAttributes().level      )                                                      +"\n"
                                             +std::to_string((int)p->getAttributes().skillPoints));

        component(_wAttr, Text, 2)->setString((p->getAttributes().crafting              ? resources.dictionary["player.skills.crafting"]               : sf::String("-"))
                                       +"\n"+(p->getAttributes().alchemy                ? resources.dictionary["player.skills.alchemy"]                : sf::String("-"))
                                       +"\n"+(p->getAttributes().cold_weapon_mastery    ? resources.dictionary["player.skills.cold_weapon_mastery"]    : sf::String("-"))
                                       +"\n"+(p->getAttributes().ranged_weapon_mastery  ? resources.dictionary["player.skills.ranged_weapon_mastery"]  : sf::String("-"))
                                       +"\n"+(p->getAttributes().better_sight           ? resources.dictionary["player.skills.better_sight"]           : sf::String("-")));

#undef component

    }

    void Attributes::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, x) w->getComponent<c>(x)

        if (_wAttr->isVisible()) {
            if (component(_wAttr, Button, 0)->isPressed(rw, e))
                g->pause(false);
        }

#undef component

    }

    void Attributes::draw(sf::RenderWindow& rw) {
        rw.draw(_shadow);
        _wAttr->draw(rw);
    }

    bool Attributes::isOpen() {
        return _wAttr->isVisible();
    }

}
