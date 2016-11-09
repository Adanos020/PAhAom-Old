/**
 * @file src/program/game/entity/npc/Teacher.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include "../NPC.hpp"

namespace rr
{
/*
    class NPC;
    class DialogueTree;
*/
    class Teacher : public NPC
    {
    private: DialogueTree m_dialogue_quest;
             DialogueTree m_dialogue_check;
             DialogueTree m_dialogue_teach;

             Branch::SwitchTo m_dialogueType;
    
             struct // Structure for buffs - each buff is represented by an integer
             {      // which tells for how many turns is it going to be valid.
             public: int speed;
                     int regeneration;
                     int poison;
                     int slowness;
                     int weakness;
                     int hunger;
             } m_buffs;
             
             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the teacher.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

    public:  enum Type
             {
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
             /// - SWORDSMAN
             /// - SHARPSHOOTER
             /// - CARPENTER
             /// - MAGE
             /// - KUNG_FU_MASTER
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the dialogue type.
             ///
             /// Possible values:
             /// - QUEST
             /// - CHECK
             /// - TEACH
             /// - NONE
             ////////////////////////////////////////////////////////////////////////
             void setDialogue(Branch::SwitchTo);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the dialogue type.
             ///
             /// Possible values:
             /// - QUEST
             /// - CHECK
             /// - TEACH
             /// - NONE
             ////////////////////////////////////////////////////////////////////////
             Branch::SwitchTo getDialogueType() const { return m_dialogueType; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the teacher.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Teacher(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Attacks other NPC.
             ////////////////////////////////////////////////////////////////////////
     virtual int attack(NPC*) { return 0; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Attacks the player.
             ////////////////////////////////////////////////////////////////////////
     virtual int attack(Player*) { return 0; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the damage that the teacher got.
             ////////////////////////////////////////////////////////////////////////
     virtual int handleDamage(int damage) override;

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

    private: Type m_type;
    };

}
