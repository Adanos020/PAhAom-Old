/**
 * @file src/program/game/menus/Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Attributes.hpp"

#include "../../gui/Text.hpp"
#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Attributes::Attributes()
    :
      wAttr_ (Window(resources.dictionary["gui.window.attributes"], sf::Vector2f(900, 310), (sf::Vector2f)settings.graphics.resolution/2.f-sf::Vector2f(450, 155))) {

        shadow_.setSize     ((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w.getComponent<c>(i)

        wAttr_ = Window(resources.dictionary["gui.window.attributes"], sf::Vector2f(900, 310), (sf::Vector2f)settings.graphics.resolution/2.f-sf::Vector2f(450, 155));
            wAttr_ += new Text(sf::Vector2f(10,  25), resources.dictionary["player.attributes.health"      ]  +":\n"
                                                     +"MANA:\n"
                                                     +resources.dictionary["player.attributes.strength"    ]  +":\n"
                                                     +resources.dictionary["player.attributes.dexterity"   ]  +":\n"
                                                     +resources.dictionary["player.attributes.experience"  ]  +":\n"
                                                     +resources.dictionary["player.attributes.level"       ]  +":\n"
                                                     +resources.dictionary["player.attributes.skill_points"]  +":"  , resources.font.Unifont, 30); // attrs
            wAttr_ += new Text(sf::Vector2f(300, 25), "", resources.font.Unifont, 30, sf::Color::Yellow);             // values
            wAttr_ += new Text(sf::Vector2f(550, 25), "", resources.font.Unifont, 30, sf::Color::Green);              // skills
            wAttr_ += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
                component(wAttr_, Button, 0)->setPosition(sf::Vector2f(wAttr_.getPosition().x+wAttr_.getSize().x/2-component(wAttr_, Button, 0)->getSize().x/2,
                                                                       wAttr_.getPosition().y+wAttr_.getSize().y  -component(wAttr_, Button, 0)->getSize().y-10));

#undef component

    }

    Attributes::~Attributes() {}

    void Attributes::open() {
        wAttr_.setVisible(true);
    }

    void Attributes::close() {
        wAttr_.setVisible(false);
    }

    void Attributes::update(Player* p) {

#define component(w, c, i) w.getComponent<c>(i)

        component(wAttr_, Text, 1)->setString( std::to_string((int)p->getAttributes().health     )+"/"+std::to_string((int)p->getAttributes().maxHealth)+"\n"
                                              +std::to_string((int)p->getAttributes().mana       )+"/"+std::to_string((int)p->getAttributes().maxMana  )+"\n"
                                              +std::to_string((int)p->getAttributes().strength   )                                                      +"\n"
                                              +std::to_string((int)p->getAttributes().dexterity  )                                                      +"\n"
                                              +std::to_string((int)p->getAttributes().experience )+"/"+std::to_string((int)p->getAttributes().nextLevel)+"\n"
                                              +std::to_string((int)p->getAttributes().level      )                                                      +"\n"
                                              +std::to_string((int)p->getAttributes().skillPoints));

        component(wAttr_, Text, 2)->setString( (p->getAttributes().crafting               ? resources.dictionary["player.skills.crafting"             ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().alchemy                ? resources.dictionary["player.skills.alchemy"              ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().cold_weapon_mastery    ? resources.dictionary["player.skills.cold_weapon_mastery"  ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().ranged_weapon_mastery  ? resources.dictionary["player.skills.ranged_weapon_mastery"] : sf::String("-"))
                                         +"\n"+(p->getAttributes().eagle_eye              ? resources.dictionary["player.skills.better_sight"         ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().mana_regeneration      ? resources.dictionary["player.skills.mana_regen"           ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().health_regeneration    ? resources.dictionary["player.skills.health_regen"         ] : sf::String("-"))
                                         +"\n"+(p->getAttributes().faster_learning        ? resources.dictionary["player.skills.faster_learn"         ] : sf::String("-")));

#undef component

    }

    void Attributes::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, x) w.getComponent<c>(x)

        if (wAttr_.isVisible()) {
            if (  component(wAttr_, Button, 0)->isPressed(rw, e)
                ) g->pause(false);
        }

#undef component

    }

    void Attributes::draw(sf::RenderWindow& rw) {
        if (isOpen()) {
            rw.draw(shadow_);
            wAttr_.draw(rw);
        }
    }

    bool Attributes::isOpen() {
        return wAttr_.isVisible();
    }

}
