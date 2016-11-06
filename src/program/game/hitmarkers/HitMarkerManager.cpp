/**
 * @file src/program/game/hitmarkers/HitMarkerManager.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../HitMarkerManager.hpp"

namespace rr
{

// PRIVATE

    void
    HitMarkerManager::onNotify(Observer::Event event, Entity* entity, sf::String message)
    {
        switch (event)
        {
            case PLAYER_ATTACK_SUCCESS:
            {
                add(message, sf::Color::Red, entity->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            case PLAYER_ATTACK_FAILURE:
            {
                add(message, sf::Color::Yellow, entity->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            case PLAYER_LEVELUP:
            {
                add(message, sf::Color::Yellow, m_player->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            case NPC_ATTACK_SUCCESS:
            {
                add(message, sf::Color::Red, m_player->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            case NPC_ATTACK_FAILURE:
            {
                add(message, sf::Color::Yellow, m_player->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            case NPC_DIES:
            {
                add(message, sf::Color::Yellow, m_player->getPosition() + sf::Vector2f(40, 0));
            }
            break;

            default: break;
        }
    }

// PUBLIC

    HitMarkerManager::HitMarkerManager(Player* player) :
      m_player(player)
    {}

    void
    HitMarkerManager::add(sf::String text, sf::Color color, sf::Vector2f pos)
    {
        m_hitmarkers.push_back(HitMarker(text, color, pos));
    }

    void
    HitMarkerManager::update(sf::Time& delta)
    {
        std::vector <HitMarker> toErase;
        for (auto it = m_hitmarkers.begin(); it != m_hitmarkers.end(); ++it)
        {
            it->update(delta);
            if (it->isDead())
            {
                m_hitmarkers.erase(it);
                break;
            }
        }
    }

    void HitMarkerManager::draw(sf::RenderWindow& window)
    {
        for (auto& hitmarker : m_hitmarkers)
        {
            window.draw(hitmarker);
        }
    }

}
