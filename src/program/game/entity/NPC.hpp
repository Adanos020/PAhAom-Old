/**
 * @file src/program/game/entity/NPC.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_HPP
#define NPC_HPP

#include "../../../../lib/AnimatedSprite.hpp"
#include "../../gui/ALL.hpp"
#include "../../Resources.hpp"

#include "../Entity.hpp"
#include "Player.hpp"

#include "../Dialogue.hpp"

namespace rr
{

    class Player;
    class NPCState;

    class NPC : public Entity
    {
        friend class AIManager;

        friend class NPCAttacking;
        friend class NPCHunting;
        friend class NPCMoving;
        friend class NPCSleeping;
        friend class NPCState;

    protected: struct Attrs
               {
                   float health;
                   float maxHealth;
                   int   level;
                   float armor;
               } m_attrs;

               struct // Structure for buffs - each buff is represented by an integer
               {      // which tells for how many turns is it going to be valid.
               public: int speed;
                       int regeneration;
                       int poison;
                       int slowness;
                       int weakness;
                       int hunger;
               } m_buffs;

               sf::AnimatedSprite m_body;

               sf::Animation*     m_currentAnimation;
               sf::Animation      m_standingLeft;
               sf::Animation      m_standingRight;
               sf::Animation      m_walkingLeft;
               sf::Animation      m_walkingRight;
               sf::Animation      m_attackingLeft;
               sf::Animation      m_attackingRight;

               sf::Vector2i       m_entityDetector[8];
               sf::Vector2i       m_position;
               sf::Vector2i       m_destination;

               float              m_velocity;

               DialogueTree*      m_currentDialogue;

               NPCState*          m_state;
               int                m_stepsToFollow;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets all the player detectors' positions.
               ////////////////////////////////////////////////////////////////////////
               void placeDetectors();

               ////////////////////////////////////////////////////////////////////////
               /// \brief Draws the NPC's body and texture on the screen.
               ////////////////////////////////////////////////////////////////////////
       virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:    enum Direction
               {
                   UP,
                   DOWN,
                   LEFT,
                   RIGHT,

                   UPLEFT,
                   UPRIGHT,
                   DOWNLEFT,
                   DOWNRIGHT
               };
               enum Attitude
               {
                   PASSIVE,
                   NEUTRAL,
                   HOSTILE
               };

               ////////////////////////////////////////////////////////////////////////
               /// \brief Virtual destructor.
               ////////////////////////////////////////////////////////////////////////
       virtual ~NPC() {}

               ////////////////////////////////////////////////////////////////////////
               /// \brief Updates the NPC's state.
               ///
               /// \param timeStep the time duration of a single frame
               ///
               /// The things updated in this function are the animations, states of
               /// the seeked path, moving the NPC, etc.
               ////////////////////////////////////////////////////////////////////////
               void update(int tiles[], sf::Time& timeStep);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Attacks other NPC.
               ////////////////////////////////////////////////////////////////////////
       virtual int attack(NPC*) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Attacks the player.
               ////////////////////////////////////////////////////////////////////////
       virtual int attack(Player*) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Handles the damage that the NPC got.
               ////////////////////////////////////////////////////////////////////////
       virtual int handleDamage(int damage) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's name.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::String getName() const = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the species of the entity.
               ////////////////////////////////////////////////////////////////////////
       virtual Species getSpecies() const override { return N_P_C; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's position relatively to the grid marked out by
               /// the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual void setGridPosition(sf::Vector2i) override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's position relatively to the grid marked out
               /// by the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2i getGridPosition() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual void setPosition(sf::Vector2f) override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2f getPosition() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if another entity's bound box intersects with the NPC's
               /// bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual bool collides(Entity*) const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::FloatRect getBounds() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's dialogue tree.
               ////////////////////////////////////////////////////////////////////////
               DialogueTree* getDialogue() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the destination the NPC has to find a path to.
               ////////////////////////////////////////////////////////////////////////
               void setDestination(sf::Vector2i);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the destination the NPC has to find a path to.
               ////////////////////////////////////////////////////////////////////////
               sf::Vector2i getDestination() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's attitude to the Player.
               ///
               /// The possible values are:
               /// - PASSIVE (the NPC doesn't attack the Player, after being attacked
               /// just starts escaping)
               /// - NEUTRAL (the NPC doesn't attack the Player as long as the Player
               /// doesn't attack him)
               /// - HOSTILE (the NPC starts chasing the Player if he sees him and
               /// tries to attack)
               ////////////////////////////////////////////////////////////////////////
               void setAttitude(Attitude);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's attitude to the Player.
               ///
               /// The possible values are:
               /// - PASSIVE (the NPC doesn't attack the Player, after being attacked
               /// just starts escaping)
               /// - NEUTRAL (the NPC doesn't attack the Player as long as the Player
               /// doesn't attack him)
               /// - HOSTILE (the NPC starts chasing the Player if he sees him and
               /// tries to attack)
               ////////////////////////////////////////////////////////////////////////
               Attitude getAttitude() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's facing direction.
               ///
               /// The possible values are:
               /// - UP
               /// - DOWN
               /// - LEFT
               /// - RIGHT
               ////////////////////////////////////////////////////////////////////////
               void setDirection(Direction);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's facing direction.
               ///
               /// The possible values are:
               /// - UP
               /// - DOWN
               /// - LEFT
               /// - RIGHT
               ////////////////////////////////////////////////////////////////////////
               Direction getDirection() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Moves the NPC to a cell in a given direction.
               ///
               /// \param tiles the set of tiles of the level in which the NPC moves
               ////////////////////////////////////////////////////////////////////////
               void move(int[], Direction);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Makes the npc react to the current of the level.
               ////////////////////////////////////////////////////////////////////////
               void react(Level*, Player*);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Gives a read-only access to the NPC's attributes.
               ///
               /// The attributes you can access are:
               /// - health
               /// - maxHealth
               /// - level
               /// - armor
               ////////////////////////////////////////////////////////////////////////
               Attrs getAttributes() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief This function returns an index of a detector which intersects
               /// the Entity's bound box. It returns -1 if none of the detectors
               /// intersect with the Entity's bound box.
               ///
               /// This function returns an index of a detector which intersects the
               /// Entity's bound box. It returns -1 if none of the detectors intersect
               /// with the Entity's bound box. The indices of the detectors are placed
               /// in such way:
               /// 0 1 2
               /// 3 x 4
               /// 5 6 7
               /// and -1 is anywhere else.
               ////////////////////////////////////////////////////////////////////////
               int detects(Entity*) const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the NPC is moving;
               ////////////////////////////////////////////////////////////////////////
               bool isMoving() const;

    protected: Attitude  m_attitude;
               Direction m_direction;
    };

}

#include "npc/NPCState.hpp"

#endif // NPC_HPP

