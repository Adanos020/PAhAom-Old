/**
 * @file src/program/game/entity/npc/NPC.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_HPP
#define NPC_HPP

#include <stack>

#include "../../../../../lib/AnimatedSprite.hpp"
#include "../../../gui/ALL.hpp"
#include "../../../Resources.hpp"

#include "../Entity.hpp"
#include "../Player.hpp"

namespace rr {

    class Player;

    class NPC : public Entity {
    protected: struct Attrs {
                 float health;
                 float maxHealth;
                 int   level;
                 float armor;
               }                         attrs_;
               sf::AnimatedSprite        body_;
               sf::Animation*            currentAnimation_;

               std::stack<sf::Vector2i> path_;

               sf::Vector2i playerDetectors_[8];

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets all the player detectors' positions.
               ////////////////////////////////////////////////////////////////////////
               void placeDetectors();

               ////////////////////////////////////////////////////////////////////////
               /// \brief Draws the NPC's body and texture on the screen.
               ////////////////////////////////////////////////////////////////////////
       virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:    enum Attitude {
                   PASSIVE,
                   NEUTRAL,
                   AGGRESSIVE
               };
               enum State {
                   STANDING,
                   EXPLORING,
                   HUNTING,
                   ESCAPING
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
       virtual void update(sf::Time timeStep) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Handles the damage that the NPC got.
               ////////////////////////////////////////////////////////////////////////
       virtual void handleDamage(int damage) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the path that the NPC has to follow.
               ///
               /// \param path a vector of positions the NPC has to visit in a specific
               /// order.
               ////////////////////////////////////////////////////////////////////////
       virtual void setPath(std::vector<sf::Vector2i>) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's name.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::String getName() const = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's position relatively to the grid marked out by
               /// the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual void setGridPosition (sf::Vector2i pos) override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's position relatively to the grid marked out
               /// by the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2i getGridPosition() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual void setPosition(sf::Vector2f pos) override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2f getPosition() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if another entity's bound box intersects with the NPC's
               /// bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual bool collides(Entity* e) const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::FloatRect getBounds() const override;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's attitude to the Player.
               ///
               /// The possible values are:
               /// - PASSIVE (the NPC doesn't attack the Player, after being attacked
               /// just starts escaping)
               /// - NEUTRAL (the NPC doesn't attack the Player as long as the Player
               /// doesn't attack him)
               /// - AGGRESSIVE (the NPC starts chasing the Player if he sees him and
               /// tries to attack)
               ////////////////////////////////////////////////////////////////////////
               void setAttitude(Attitude attitude);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the NPC's state moving.
               ///
               /// The possible values are:
               /// - STANDING (just stands in one place)
               /// - EXPLORING (picks random points on the map and goes towards them)
               /// - HUNTING (chases the Player and tries to attack him)
               /// - ESCAPING (is frightened of something and tries to find a way to
               /// get as far as he cannot se it)
               ////////////////////////////////////////////////////////////////////////
               void setState(State state);

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's attitude to the Player.
               ///
               /// The possible values are:
               /// - PASSIVE (the NPC doesn't attack the Player, after being attacked
               /// just starts escaping)
               /// - NEUTRAL (the NPC doesn't attack the Player as long as the Player
               /// doesn't attack him)
               /// - AGGRESSIVE (the NPC starts chasing the Player if he sees him and
               /// tries to attack)
               ////////////////////////////////////////////////////////////////////////
               Attitude getAttitude() const;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the NPC's state moving.
               ///
               /// The possible values are:
               /// - STANDING (just stands in one place)
               /// - EXPLORING (picks random points on the map and goes towards them)
               /// - HUNTING (chases the Player and tries to attack him)
               /// - ESCAPING (is frightened of something and tries to find a way to
               /// get as far as he cannot se it)
               ////////////////////////////////////////////////////////////////////////
               State getState() const;

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
               /// the Player's bound box. It returns -1 if none of the detectors
               /// intersect with the Player's bound box.
               ///
               /// This function returns an index of a detector which intersects the
               /// Player's bound box. It returns -1 if none of the detectors intersect
               /// with the Player's bound box. The indices of the detectors are placed
               /// in such way:
               /// 0 1 2
               /// 3 x 4
               /// 5 6 7
               /// and -1 is anywhere else.
               ////////////////////////////////////////////////////////////////////////
               int detects(Player*) const;

    protected: Attitude attitude_;
               State    state_;
    };

}

#endif // NPC_HPP

