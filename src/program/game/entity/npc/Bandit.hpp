/**
 * @file src/program/game/entity/npc/Bandit.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_BANDIT_HPP
#define NPC_BANDIT_HPP

#include "../Player.hpp"

namespace rr
{

    class Bandit : public NPC
    {
    private: bool m_moving;

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
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the damage that the bandit got.
             ////////////////////////////////////////////////////////////////////////
     virtual int handleDamage(int damage) override;

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

    private: Type m_type;
    };

}

#include "../NPC.hpp"

#endif // NPC_BANDIT_HPP
