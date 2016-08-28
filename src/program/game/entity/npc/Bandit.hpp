/**
 * @file src/program/game/entity/npc/Bandit.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_BANDIT_HPP
#define NPC_BANDIT_HPP

#include "NPC.hpp"

#include "../Player.hpp"

namespace rr
{

    class Bandit : public NPC
    {
    private: bool moving_;

             struct // Structure for buffs - each buff is represented by an integer
             {      // which tells for how many turns is it going to be valid.
             public: int speed;
                     int regeneration;
                     int poison;
                     int slowness;
                     int weakness;
                     int hunger;
             } buffs_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the bandit.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
                 CLUB,
                 CROSSBOW,
                 DAGGER
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Bandit(Type = CLUB);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Bandit(Bandit const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the bandit.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Bandit(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the bandits's type.
             ///
             /// The possible values are:
             /// - CLUB
             /// - CROSSBOW
             /// - DAGGER
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the bandit's state.
             ///
             /// \param timeStep the time duration of a single frame
             ///
             /// The things updated in this function are the animations, states of
             /// the seeked path, moving the bandit, etc.
             ////////////////////////////////////////////////////////////////////////
     virtual void update(int tiles[], sf::Time timeStep) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the damage that the bandit got.
             ////////////////////////////////////////////////////////////////////////
     virtual void handleDamage(int damage) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the bandit's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the bandit attack an NPC.
             ////////////////////////////////////////////////////////////////////////
             void attack(NPC*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Makes the bandit attack the player.
             ////////////////////////////////////////////////////////////////////////
             void attack(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the bandit from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the bandit to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // NPC_BANDIT_HPP
