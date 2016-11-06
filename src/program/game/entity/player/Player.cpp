/**
 * @file src/program/game/entity/player/Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>
#include <cmath>

#include "../Player.hpp"
#include "../item/ALL.hpp"

#include "../../../Resources.hpp"
#include "../../../Observer.hpp"

#include "../../../funcs/classes.hpp"
#include "../../../funcs/files.hpp"
#include "../../../funcs/keys.hpp"

#include "../../Level.hpp"

extern rr::Subject subject;

namespace rr
{

    PlayerStanding  PlayerState::standing;
    PlayerMoving    PlayerState::moving;
    PlayerAttacking PlayerState::attacking;

    Player::Player(Level* level) :
      m_meleeWeapon     (nullptr),
      m_rangedWeapon    (nullptr),
      m_state           (new PlayerStanding()),
      m_currentLevel    (level),
      m_position        (sf::Vector2i(0, 0)),
      m_currentAnimation(&m_walkingRight),
      m_velocity        (900.f),
      m_sightRange      (4)
    {
        m_attrs.health = m_attrs.maxHealth =  50.f;
        m_attrs.mana   = m_attrs.maxMana   =   5.f;
        m_attrs.strength                   =  10.f;
        m_attrs.dexterity                  =  10.f;
        m_attrs.experience                 =   0.f;
        m_attrs.nextLevel                  = 500.f;
        m_attrs.level                      =   0  ;
        m_attrs.skillPoints                =   0.f;
        m_attrs.armor                      =   0.f;

        m_attrs.crafting              = false;
        m_attrs.alchemy               = false;
        m_attrs.melee_weapon_mastery  = false;
        m_attrs.ranged_weapon_mastery = false;
        m_attrs.eagle_eye             = false;
        m_attrs.mana_regeneration     = false;
        m_attrs.health_regeneration   = false;
        m_attrs.faster_learning       = false;

        m_buffs.speed        = 0;
        m_buffs.regeneration = 0;
        m_buffs.poison       = 0;
        m_buffs.slowness     = 0;
        m_buffs.weakness     = 0;
        m_buffs.hunger       = 0;

        initialize();
        m_body.setPosition(sf::Vector2f(0, 0));
        m_body.scale      (sf::Vector2f(5, 5));
    }

    Player::Player(Player const& copy) :
      m_attrs           (copy.m_attrs),
      m_buffs           (copy.m_buffs),
      m_meleeWeapon     (copy.m_meleeWeapon),
      m_rangedWeapon    (copy.m_rangedWeapon),
      m_state           (copy.m_state),
      m_currentLevel    (copy.m_currentLevel),
      m_position        (copy.m_position),
      m_body            (copy.m_body),
      m_walkingLeft     (copy.m_walkingLeft),
      m_walkingRight    (copy.m_walkingRight),
      m_currentAnimation(copy.m_currentAnimation),
      m_velocity        (copy.m_velocity),
      m_sightRange      (copy.m_sightRange) {}

    void
    Player::initialize()
    {
        // loading the sprite sheets for the animations
        m_standingLeft .setSpriteSheet(Resources::texture.player);
        m_standingRight.setSpriteSheet(Resources::texture.player);

        m_walkingLeft .setSpriteSheet(Resources::texture.player);
        m_walkingRight.setSpriteSheet(Resources::texture.player);

        // adding the frames to the animations
        m_standingLeft.addFrame(sf::IntRect(0, 16, 16, 16));
        
        m_standingRight.addFrame(sf::IntRect(0, 0, 16, 16));

        m_walkingLeft.addFrame(sf::IntRect( 0, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(16, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect( 0, 16, 16, 16));
        m_walkingLeft.addFrame(sf::IntRect(32, 16, 16, 16));

        m_walkingRight.addFrame(sf::IntRect( 0, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(16, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect( 0, 0, 16, 16));
        m_walkingRight.addFrame(sf::IntRect(32, 0, 16, 16));

        // setting the animated sprite's properties
        m_body.setFrameTime(sf::seconds(.1f));
        m_body.setLooped(false);
        m_body.pause();
    }

    void
    Player::setCurrentLevel(Level* level)
    {
        m_currentLevel = level;
    }

    void
    Player::handleInput(sf::Event& event)
    {
        PlayerState* state = m_state->handleInput(event, *this);
        if (state != nullptr)
            m_state = state;
    }

    bool
    Player::move(Direction di)
    {
        auto tiles = m_currentLevel->getTiles();
        bool success = false;

        if (di == UP && (tiles[m_position.x + (m_position.y-1)*77] != 1 && tiles[m_position.x + (m_position.y-1)*77] != 5))
        {
            m_position = sf::Vector2i(m_position.x, m_position.y-1);

            if (m_currentAnimation == &m_standingLeft)
                m_currentAnimation = &m_walkingLeft;

            else if (m_currentAnimation == &m_standingRight)
                m_currentAnimation = &m_walkingRight;

            success = true;
        }
        if (di == DOWN && (tiles[m_position.x + (m_position.y+1)*77] != 1 && tiles[m_position.x + (m_position.y+1)*77] != 5))
        {
            m_position = sf::Vector2i(m_position.x, m_position.y+1);

            if (m_currentAnimation == &m_standingLeft)
                m_currentAnimation = &m_walkingLeft;

            else if (m_currentAnimation == &m_standingRight)
                m_currentAnimation = &m_walkingRight;

            success = true;
        }
        if (di == LEFT)
        {
            if (tiles[m_position.x-1 + m_position.y*77] != 1 && tiles[m_position.x-1 + m_position.y*77] != 5)
            {
                m_position = sf::Vector2i(m_position.x-1, m_position.y);
                success = true;
            }
            m_currentAnimation = &m_walkingLeft;
        }
        if (di == RIGHT)
        {
            if (tiles[m_position.x+1 + m_position.y*77] != 1 && tiles[m_position.x+1 + m_position.y*77] != 5)
            {
                m_position = sf::Vector2i(m_position.x+1, m_position.y);
                success = true;
            }
            m_currentAnimation = &m_walkingRight;
        }
        return success;
    }

    void
    Player::update(sf::Time& timeStep)
    {
        auto state = m_state->update(timeStep, *this);
        if (state != nullptr)
            m_state = state;

        if (m_attrs.health >= m_attrs.maxHealth)
            m_attrs.health  = m_attrs.maxHealth;

        if (m_attrs.health <= 0)
            m_attrs.health  = 0;

        if (m_attrs.mana <= 0)
            m_attrs.mana  = 0;

        if (m_attrs.mana >= m_attrs.maxMana)
            m_attrs.mana  = m_attrs.maxMana;

        if (m_attrs.experience >= m_attrs.nextLevel)
        {
            m_attrs.experience  -= m_attrs.nextLevel;
            m_attrs.nextLevel   *= 1.15f;
            m_attrs.level       ++;
            m_attrs.skillPoints += (m_attrs.faster_learning) ? 15 : 10;

            float proportion   = m_attrs.health/m_attrs.maxHealth;
            m_attrs.maxHealth += 10;
            m_attrs.health     = proportion*m_attrs.maxHealth;

            proportion       = m_attrs.mana/m_attrs.maxMana;
            m_attrs.maxMana += 1;
            m_attrs.mana     = proportion*m_attrs.maxMana;

            subject.notify(Observer::PLAYER_LEVELUP, this);
        }

        m_body.update(timeStep);
        m_body.play(*m_currentAnimation);
    }

    int
    Player::attack(NPC* npc)
    {
        int maxDamage = m_attrs.strength/3.f;
        if (m_meleeWeapon != nullptr)
            maxDamage = m_meleeWeapon->getDamageDealt() - (m_meleeWeapon->getRequirement() - m_attrs.strength);

        return npc->handleDamage(rand()%maxDamage);
    }

    int
    Player::handleDamage(int damage)
    {
        if (damage >= m_attrs.armor)
            damage -= m_attrs.armor;
        else
            damage = 0;

        m_attrs.health -= damage;
        return damage;
    }

    void
    Player::learnSkill(Book::Type skill, int sp)
    {
        switch (skill)
        {
            case Book::CRAFTING             : m_attrs.crafting              = true; break;
            case Book::ALCHEMY              : m_attrs.alchemy               = true; break;
            case Book::MELEE_WEAPON_MASTERY : m_attrs.melee_weapon_mastery  = true; break;
            case Book::RANGED_WEAPON_MASTERY: m_attrs.ranged_weapon_mastery = true; break;
            case Book::EAGLE_EYE            : m_attrs.eagle_eye             = true; break;
            case Book::MANA_REGEN           : m_attrs.mana_regeneration     = true; break;
            case Book::HEALTH_REGEN         : m_attrs.health_regeneration   = true; break;
            case Book::FASTER_LEARNING      : m_attrs.faster_learning       = true; break;
            
            default: break; // any other is ignored
        }
        m_attrs.skillPoints -= sp;
    }

    void
    Player::increaseAttribute(Attribute attribute, float difference, int sp)
    {
        switch (attribute)
        {
            case HEALTH:
            {
                float proportion   = m_attrs.health/m_attrs.maxHealth;
                m_attrs.maxHealth += difference;
                m_attrs.health     = proportion*m_attrs.maxHealth;
            } break;

            case MANA:
            {
                float proportion  = m_attrs.mana/m_attrs.maxMana;
                m_attrs.maxMana  += difference;
                m_attrs.mana      = proportion*m_attrs.maxMana;
            } break;

            case STRENGTH : m_attrs.strength += difference;
                            break;
                            
            case DEXTERITY: m_attrs.dexterity += difference;
                            break;
        }
        m_attrs.skillPoints -= sp;
    }

    void
    Player::reset()
    {
        m_attrs.health      =  50.f;
        m_attrs.mana        =   5.f;
        m_attrs.maxHealth   =  50.f;
        m_attrs.maxMana     =   5.f;
        m_attrs.strength    =  10.f;
        m_attrs.dexterity   =  10.f;
        m_attrs.experience  =   0.f;
        m_attrs.nextLevel   = 500.f;
        m_attrs.level       =   0  ;
        m_attrs.skillPoints =   0.f;
        m_attrs.armor       =   0.f;

        m_buffs.speed        = 0;
        m_buffs.regeneration = 0;
        m_buffs.poison       = 0;
        m_buffs.slowness     = 0;
        m_buffs.weakness     = 0;
        m_buffs.hunger       = 0;

        m_attrs.crafting              = false;
        m_attrs.alchemy               = false;
        m_attrs.melee_weapon_mastery  = false;
        m_attrs.ranged_weapon_mastery = false;
        m_attrs.eagle_eye             = false;
        m_attrs.mana_regeneration     = false;
        m_attrs.health_regeneration   = false;
        m_attrs.faster_learning       = false;
    }

    void
    Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &Resources::texture.player;
        target.draw(m_body, states);
    }

    void
    Player::useItem(Item* item)
    {
        if (instanceof <Discoverable, Item> (item) && !((Discoverable*) item)->isDiscovered())
        {
            ((Discoverable*) item)->reveal();
            subject.notify(Observer::ITEM_DISCOVERED, item);
        }

        subject.notify(Observer::ITEM_USED, item);

        if (instanceof <Book, Item> (item))
        {
            switch (((Book*) item)->getType())
            {
                case Book::CRAFTING             : m_attrs.crafting              = true; break;
                case Book::ALCHEMY              : m_attrs.alchemy               = true; break;
                case Book::MELEE_WEAPON_MASTERY : m_attrs.melee_weapon_mastery  = true; break;
                case Book::RANGED_WEAPON_MASTERY: m_attrs.ranged_weapon_mastery = true; break;
                case Book::EAGLE_EYE            : m_attrs.eagle_eye             = true; break;
                case Book::MANA_REGEN           : m_attrs.mana_regeneration     = true; break;
                case Book::HEALTH_REGEN         : m_attrs.health_regeneration   = true; break;
                case Book::FASTER_LEARNING      : m_attrs.faster_learning       = true; break;
                default                         :                                      break;
            }
        }
        else if (instanceof <Food, Item> (item))
        {
            if (m_buffs.hunger >= 1000)
                m_buffs.hunger  = 500;
            else
                m_buffs.hunger  = 0;

            m_attrs.health += 10;
        }
        else if (instanceof <Potion, Item> (item))
        {
            switch (((Potion*) item)->getType())
            {
                case Potion::HEALING     : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_attrs.health += m_attrs.maxHealth*0.25; break;
                                               case Potion::MEDIUM: m_attrs.health += m_attrs.maxHealth*0.50; break;
                                               case Potion::BIG   : m_attrs.health += m_attrs.maxHealth*0.75; break;
                                           }
                                           m_buffs.poison = 0;
                                           break;

                case Potion::MAGIC       : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_attrs.mana += m_attrs.maxMana * 0.25; break;
                                               case Potion::MEDIUM: m_attrs.mana += m_attrs.maxMana * 0.50; break;
                                               case Potion::BIG   : m_attrs.mana += m_attrs.maxMana * 0.75; break;
                                           } break;

                case Potion::STRENGTH    : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_attrs.strength += 1; break;
                                               case Potion::MEDIUM: m_attrs.strength += 3; break;
                                               case Potion::BIG   : m_attrs.strength += 5; break;
                                           } break;

                case Potion::DEXTERITY   : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_attrs.dexterity += 1; break;
                                               case Potion::MEDIUM: m_attrs.dexterity += 3; break;
                                               case Potion::BIG   : m_attrs.dexterity += 5; break;
                                           } break;

                case Potion::SPEED       : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_buffs.speed += 10; break;
                                               case Potion::MEDIUM: m_buffs.speed += 30; break;
                                               case Potion::BIG   : m_buffs.speed += 50; break;
                                           } break;

                case Potion::REGENERATION: switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_buffs.regeneration += 10; break;
                                               case Potion::MEDIUM: m_buffs.regeneration += 30; break;
                                               case Potion::BIG   : m_buffs.regeneration += 50; break;
                                           } break;

                case Potion::POISON      : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_buffs.poison += 10; break;
                                               case Potion::MEDIUM: m_buffs.poison += 30; break;
                                               case Potion::BIG   : m_buffs.poison += 50; break;
                                           } break;

                case Potion::SLOWNESS    : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_buffs.slowness += 10; break;
                                               case Potion::MEDIUM: m_buffs.slowness += 30; break;
                                               case Potion::BIG   : m_buffs.slowness += 50; break;
                                           } break;

                case Potion::WEAKNESS    : switch (((Potion*) item)->getSize())
                                           {
                                               case Potion::SMALL : m_buffs.weakness += 10; break;
                                               case Potion::MEDIUM: m_buffs.weakness += 30; break;
                                               case Potion::BIG   : m_buffs.weakness += 50; break;
                                           } break;
            }
        }
        else if (instanceof <Rune, Item> (item))
        {

        }
    }

    bool
    Player::equipItem(Equipable* item, bool equip)
    {
        bool success = false;
        if (instanceof <MeleeWeapon, Equipable> (item))
        {
            if (!equip)
            {
                m_meleeWeapon = nullptr;
                success = true;
            }
            else if (((MeleeWeapon*) item)->getRequirement() <= m_attrs.strength)
            {
                m_meleeWeapon = (MeleeWeapon*) item;
                success = true;
            }
        }
        else if (instanceof <RangedWeapon, Equipable> (item))
        {
            if (!equip)
            {
                m_rangedWeapon = nullptr;
                success = true;
            }
            else if (((RangedWeapon*) item)->getRequirement() <= m_attrs.dexterity)
            {
                m_rangedWeapon = (RangedWeapon*) item;
                success = true;
            }
        }

        if (success)
        {
            if (!item->isDiscovered())
            {
                item->reveal();
                subject.notify(Observer::ITEM_DISCOVERED, item);
            }
        }
        else subject.notify(Observer::ITEM_EQUIP_FAILURE, item);

        return success;
    }

    bool
    Player::isMoving() const
    {
         return instanceof <PlayerMoving, PlayerState> (m_state);
    }

    void
    Player::cheat()
    {
             if (isKeyPressed(sf::Keyboard::Numpad1)) m_attrs.health     --;
        else if (isKeyPressed(sf::Keyboard::Numpad2)) m_attrs.health     ++;
        else if (isKeyPressed(sf::Keyboard::Numpad3)) m_attrs.mana       --;
        else if (isKeyPressed(sf::Keyboard::Numpad4)) m_attrs.mana       ++;
        else if (isKeyPressed(sf::Keyboard::Numpad5)) m_attrs.experience ++;
        else if (isKeyPressed(sf::Keyboard::Numpad6)) m_attrs.level      ++;
        else if (isKeyPressed(sf::Keyboard::Numpad7)) m_attrs.skillPoints++;
        else if (isKeyPressed(sf::Keyboard::Numpad8)) m_attrs.strength   ++;
        else if (isKeyPressed(sf::Keyboard::Numpad9)) m_attrs.dexterity  ++;
    }

    std::ifstream&
    Player::operator<<(std::ifstream& file)
    {
        m_currentAnimation->clearFrames();

        try
        {
            readFile <float> (file, m_attrs.health);
            readFile <float> (file, m_attrs.mana);
            readFile <float> (file, m_attrs.maxHealth);
            readFile <float> (file, m_attrs.maxMana);
            readFile <float> (file, m_attrs.strength);
            readFile <float> (file, m_attrs.dexterity);
            readFile <float> (file, m_attrs.experience);
            readFile <float> (file, m_attrs.nextLevel);
            readFile < int > (file, m_attrs.level);
            readFile <float> (file, m_attrs.skillPoints);

            readFile < int > (file, m_buffs.speed);
            readFile < int > (file, m_buffs.regeneration);
            readFile < int > (file, m_buffs.poison);
            readFile < int > (file, m_buffs.slowness);
            readFile < int > (file, m_buffs.weakness);
            readFile < int > (file, m_buffs.hunger);

            readFile < bool> (file, m_attrs.crafting);
            readFile < bool> (file, m_attrs.alchemy);
            readFile < bool> (file, m_attrs.melee_weapon_mastery);
            readFile < bool> (file, m_attrs.ranged_weapon_mastery);
            readFile < bool> (file, m_attrs.eagle_eye);
            readFile < bool> (file, m_attrs.mana_regeneration);
            readFile < bool> (file, m_attrs.health_regeneration);
            readFile < bool> (file, m_attrs.faster_learning);

            readFile < int > (file, m_position.x);
            readFile < int > (file, m_position.y);
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        initialize();
        setGridPosition(m_position);

        return file;
    }

    std::ofstream&
    Player::operator>>(std::ofstream& file)
    {
        file << m_attrs.health                << ' '
             << m_attrs.mana                  << ' '
             << m_attrs.maxHealth             << ' '
             << m_attrs.maxMana               << ' '
             << m_attrs.strength              << ' '
             << m_attrs.dexterity             << ' '
             << m_attrs.experience            << ' '
             << m_attrs.nextLevel             << ' '
             << m_attrs.level                 << ' '
             << m_attrs.skillPoints           << ' '

             << m_buffs.speed                 << ' '
             << m_buffs.regeneration          << ' '
             << m_buffs.poison                << ' '
             << m_buffs.slowness              << ' '
             << m_buffs.weakness              << ' '
             << m_buffs.hunger                << ' '

             << m_attrs.crafting              << ' '
             << m_attrs.alchemy               << ' '
             << m_attrs.melee_weapon_mastery  << ' '
             << m_attrs.ranged_weapon_mastery << ' '
             << m_attrs.eagle_eye             << ' '
             << m_attrs.mana_regeneration     << ' '
             << m_attrs.health_regeneration   << ' '
             << m_attrs.faster_learning       << ' '
             
             << m_position.x                  << ' '
             << m_position.y;
        
        return file;
    }

}
