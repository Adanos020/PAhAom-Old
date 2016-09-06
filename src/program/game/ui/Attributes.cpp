/**
 * @file src/program/game/ui/Attributes.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Attributes.hpp"

#include "../../gui/Text.hpp"
#include "../../gui/Button.hpp"

#include "../../Settings.hpp"
#include "../../Resources.hpp"

namespace rr
{

    Attributes::Attributes() :
      wAttr_ (Window(Resources::dictionary["gui.window.attributes"], sf::Vector2f(900, 310), (sf::Vector2f) Settings::graphics.resolution/2.f - sf::Vector2f(450, 155)))
    {
        shadow_.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

        wAttr_ += new Text(sf::Vector2f(10,  25), Resources::dictionary["player.attributes.health"      ]  +":\n"
                                                 +"MANA:\n"
                                                 +Resources::dictionary["player.attributes.strength"    ]  +":\n"
                                                 +Resources::dictionary["player.attributes.dexterity"   ]  +":\n"
                                                 +Resources::dictionary["player.attributes.experience"  ]  +":\n"
                                                 +Resources::dictionary["player.attributes.level"       ]  +":\n"
                                                 +Resources::dictionary["player.attributes.skill_points"]  +":", Resources::font.Unifont, 30);
        wAttr_ += new Text(sf::Vector2f(300, 25), "", Resources::font.Unifont, 30, sf::Color::Yellow);
        wAttr_ += new Text(sf::Vector2f(550, 25), "", Resources::font.Unifont, 30, sf::Color::Green);

        auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
             bQuit->setPosition(sf::Vector2f(wAttr_.getSize().x/2 - bQuit->getSize().x/2,
                                             wAttr_.getSize().y   - bQuit->getSize().y-10));

        wAttr_ += bQuit;
    }

    void
    Attributes::update(Player* p)
    {
        wAttr_.getComponent <Text> (1)->setString(std::to_string((int)p->getAttributes().health     )+"/"+std::to_string((int)p->getAttributes().maxHealth)+"\n"
                                                 +std::to_string((int)p->getAttributes().mana       )+"/"+std::to_string((int)p->getAttributes().maxMana  )+"\n"
                                                 +std::to_string((int)p->getAttributes().strength   )                                                      +"\n"
                                                 +std::to_string((int)p->getAttributes().dexterity  )                                                      +"\n"
                                                 +std::to_string((int)p->getAttributes().experience )+"/"+std::to_string((int)p->getAttributes().nextLevel)+"\n"
                                                 +std::to_string((int)p->getAttributes().level      )                                                      +"\n"
                                                 +std::to_string((int)p->getAttributes().skillPoints));

        wAttr_.getComponent <Text> (2)->setString((p->getAttributes().crafting               ? Resources::dictionary["player.skills.crafting"             ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().alchemy                ? Resources::dictionary["player.skills.alchemy"              ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().melee_weapon_mastery   ? Resources::dictionary["player.skills.melee_weapon_mastery" ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().ranged_weapon_mastery  ? Resources::dictionary["player.skills.ranged_weapon_mastery"] : sf::String("-"))
                                            +"\n"+(p->getAttributes().eagle_eye              ? Resources::dictionary["player.skills.better_sight"         ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().mana_regeneration      ? Resources::dictionary["player.skills.mana_regen"           ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().health_regeneration    ? Resources::dictionary["player.skills.health_regen"         ] : sf::String("-"))
                                            +"\n"+(p->getAttributes().faster_learning        ? Resources::dictionary["player.skills.faster_learn"         ] : sf::String("-")));
    }

    void
    Attributes::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g)
    {
        if (wAttr_.isVisible())
        {
            if (wAttr_.getComponent <Button> (0)->isPressed(rw, e))
                g->pause(false);
        }
    }

    void
    Attributes::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(shadow_, states);
            target.draw(wAttr_ , states);
        }
    }

}
