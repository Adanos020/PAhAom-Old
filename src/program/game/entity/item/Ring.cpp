/**
 * @file src/program/game/item/Ring.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "Ring.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/random.hpp"

extern sf::Color itemColors[9];

namespace rr
{

    bool Ring::m_identified[7] = { false, false, false, false, false, false, false };

    Ring::Ring(Ring::Type type, int bonus, int amount) :
      m_type (type),
      m_bonus(bonus)
    {
        m_amount = amount;

        initialize();
    }

    Ring::Ring(Ring const& copy) :
     m_type (copy.m_type),
     m_bonus(copy.m_bonus)
    {
        m_amount     = copy.m_amount;
        m_disposable = copy.m_disposable;
        m_stackable  = copy.m_stackable;
        m_ID         = copy.m_ID;
        m_iconIndex  = copy.m_iconIndex;
        m_body       = copy.m_body;

        initialize();
    }

    void
    Ring::initialize()
    {
        m_disposable = false;
        m_stackable  = false;
        m_cursed     = chance(2, 5);
        m_ID         = 70 + m_type;

        bool fromQuest = ((m_type == QUEST_SWORDSMAN) || (m_type == QUEST_SHARPSHOOTER) ||
            (m_type == QUEST_CARPENTER) || (m_type == QUEST_MAGE) || (m_type == QUEST_KUNG_FU_MASTER));

        m_iconIndex = 96 + (int) fromQuest;
        int icons[] = { (int) m_iconIndex, (int) m_iconIndex + 16 };

        setIcon(m_body, 2, icons);
        setColor(m_body, 1, itemColors[m_type % 6]);

        if (fromQuest)
        {
            m_identified[m_type] = fromQuest;
        }
    }

    sf::String
    Ring::getName() const
    {
        if (m_identified[m_type])
        {
            switch (m_type)
            {
                case HEALTH         : return Resources::dictionary["item.ring.type.health"];
                case MAGIC          : return Resources::dictionary["item.ring.type.magic"];
                case STRENGTH       : return Resources::dictionary["item.ring.type.strength"];
                case DEXTERITY      : return Resources::dictionary["item.ring.type.dexterity"];
                case ACCURACY       : return Resources::dictionary["item.ring.type.accuracy"];
                case SPEED          : return Resources::dictionary["item.ring.type.speed"];
                case QUEST_SWORDSMAN: return Resources::dictionary["item.ring.type.quest_swordsman"];

                default: return "";
            }
        }

        if (itemColors[m_type % 6] == sf::Color::Red)           return Resources::dictionary["item.ring.color.red"];
        if (itemColors[m_type % 6] == sf::Color::Blue)          return Resources::dictionary["item.ring.color.blue"];
        if (itemColors[m_type % 6] == sf::Color(32, 32, 0))     return Resources::dictionary["item.ring.color.brown"];
        if (itemColors[m_type % 6] == sf::Color::Green)         return Resources::dictionary["item.ring.color.green"];
        if (itemColors[m_type % 6] == sf::Color::Cyan)          return Resources::dictionary["item.ring.color.cyan"];
        if (itemColors[m_type % 6] == sf::Color(255, 172, 172)) return Resources::dictionary["item.ring.color.orange"];
        if (itemColors[m_type % 6] == sf::Color::Magenta)       return Resources::dictionary["item.ring.color.magenta"];
        if (itemColors[m_type % 6] == sf::Color::Yellow)        return Resources::dictionary["item.ring.color.yellow"];
        if (itemColors[m_type % 6] == sf::Color::White)         return Resources::dictionary["item.ring.color.white"];

         return "";
    }

    sf::String
    Ring::getDescription() const
    {
        if (m_identified[m_type])
        {
            switch (m_type)
            {
                case HEALTH         : return Resources::dictionary["item.ring.description.health"];
                case MAGIC          : return Resources::dictionary["item.ring.description.magic"];
                case STRENGTH       : return Resources::dictionary["item.ring.description.strength"];
                case DEXTERITY      : return Resources::dictionary["item.ring.description.dexterity"];
                case ACCURACY       : return Resources::dictionary["item.ring.description.accuracy"];
                case SPEED          : return Resources::dictionary["item.ring.description.speed"];
                case QUEST_SWORDSMAN: return Resources::dictionary["item.ring.description.quest_swordsman"];

                default: return "";
            }
        }
        return Resources::dictionary["item.ring.description.unknown"];
    }

    void
    Ring::enhance()
    {

    }

    void
    Ring::setGridPosition(sf::Vector2i pos)
    {
        m_body[0].position = (sf::Vector2f) pos*80.f;
        m_body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        m_body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        m_body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        m_body[4].position = m_body[0].position;
        m_body[5].position = m_body[1].position;
        m_body[6].position = m_body[2].position;
        m_body[7].position = m_body[3].position;
    }

    void
    Ring::setPosition(sf::Vector2f pos)
    {
        m_body[0].position = pos;
        m_body[1].position = sf::Vector2f(pos.x+80, pos.y   );
        m_body[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        m_body[3].position = sf::Vector2f(pos.x   , pos.y+80);

        m_body[4].position = m_body[0].position;
        m_body[5].position = m_body[1].position;
        m_body[6].position = m_body[2].position;
        m_body[7].position = m_body[3].position;
    }

    std::ifstream&
    Ring::operator<<(std::ifstream& file)
    {
        sf::Vector2i position;
        int type;

        try
        {
            readFile <int> (file, position.x);
            readFile <int> (file, position.y);
            readFile <int> (file, m_amount);
            readFile <int> (file, m_bonus);
            readFile <int> (file, type);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        m_type = (Type) type;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream&
    Ring::operator>>(std::ofstream& file)
    {
        file << 7                             << ' '
             << (int) m_body[0].position.x/80 << ' '
             << (int) m_body[0].position.y/80 << ' '
             << m_amount                      << ' '
             << m_bonus                       << ' '
             << m_type;

        return file;
    }

}
