#include "item.h"

namespace rr {

    Potion::Potion(double id, std::string itemName, short icon, int am, short val, sf::Vector2f pos) {
        name = itemName;
        amount = am;
        bonus = val;
        disposable = true;

        skin.loadFromFile("data/graphics/items.png");

        body.setPrimitiveType(sf::Quads);
        body.resize(4);

        int tu = icon%(280/14);
        int tv = icon/(280/14);

        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+70, pos.y);
        body[2].position = sf::Vector2f(pos.x+70, pos.y+70);
        body[3].position = sf::Vector2f(pos.x, pos.y+70);

        body[0].texCoords = sf::Vector2f(tu*14, tv*14);
        body[1].texCoords = sf::Vector2f((tu+1)*14, tv*14);
        body[2].texCoords = sf::Vector2f((tu+1)*14, (tv+1)*14);
        body[3].texCoords = sf::Vector2f(tu*14, (tv+1)*14);

        if (name != "Unknown item ID") {
            ID = id;
            description = "A";
            if (name.find("Small") != std::string::npos) description += " small";
            else if (name.find("Medium") != std::string::npos) description += " regular";
            else if (name.find("Large") != std::string::npos) description += " big";
            description += " bottle of a";

            if (name.find("healing") != std::string::npos || name.find("health") != std::string::npos) {
                description += " red liquid that can";
                body[2].color = body[3].color = sf::Color::Red;
                if (name.find("bonus") != std::string::npos) description += " increase your max health";
                else description += " heal you";
            } else if (name.find("mana") != std::string::npos) {
                description += " blue liquid that can";
                body[2].color = body[3].color = sf::Color::Blue;
                if (name.find("bonus") != std::string::npos) description += " increase your max mana";
                else description += " restore some of your mana";
            } else if (name.find("strength") != std::string::npos) {
                description += " green liquid that can";
                body[2].color = body[3].color = sf::Color::Green;
                if (name.find("bonus") != std::string::npos) description += " increase your strength";
                else description += " increase your strength for some time";
            } else if (name.find("dexterity") != std::string::npos) {
                description += " magenta liquid that can";
                body[2].color = body[3].color = sf::Color::Magenta;
                if (name.find("bonus") != std::string::npos) description += " increase your dexterity";
                else description += " increase your dexterity for some time";
            }
            description += '.';
        } else description = "Check if the ID "+std::to_string(ID)+" is on the item ID list.";
    }

    Potion::~Potion() {}

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body, &skin);
    }

    void Potion::editAmount(int am) {
        amount = am;
    }

    void Potion::update() {
        boundBox = body.getBounds();
    }

}
