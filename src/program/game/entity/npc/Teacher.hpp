/**
 * @file src/program/game/entity/npc/Teacher.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_TEACHER_HPP
#define NPC_TEACHER_HPP

#include "NPC.hpp"

namespace rr {

    class Teacher : public NPC {
    private: sf::Animation standingStill_;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the teacher.
             ////////////////////////////////////////////////////////////////////////
             virtual void           initialize()                             override;

    public:  enum Type {
                 SWORDSMAN,
                 SHARPSHOOTER,
                 CARPENTER,
                 MAGE,
                 KUNG_FU_MASTER
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Teacher(Type = SWORDSMAN);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Teacher(Teacher const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the teachers's type.
             ///
             /// The possible values are:
             /// - CLUB
             /// - CROSSBOW
             /// - DAGGER
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return type_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the teacher.
             ////////////////////////////////////////////////////////////////////////
             virtual Entity* clone() const override { return new Teacher(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the teacher's state.
             ///
             /// \param timeStep the time duration of a single frame
             ///
             /// The things updated in this function are the animations, states of
             /// the seeked path, moving the teacher, etc.
             ////////////////////////////////////////////////////////////////////////
             virtual void update(sf::Time timeStep) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the damage that the teacher got.
             ////////////////////////////////////////////////////////////////////////
             virtual void handleDamage(int damage) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the path that the teacher has to follow.
             ///
             /// \param path a vector of positions the teacher has to visit in a
             /// specific order.
             ////////////////////////////////////////////////////////////////////////
             virtual void setPath(std::vector<sf::Vector2i>) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the bandit's name.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the teacher from the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the teacher to the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // NPC_TEACHER_HPP
