/**
 * @file src/program/game/Dialogue.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>
#include <fstream>
#include <string>

#include "../funcs/files.hpp"

#include "Dialogue.hpp"

namespace rr
{

    Sentence::Sentence(Sentence::Speaker s, sf::String sn) :
      m_speaker (s),
      m_sentence(sn)
    {}

    DialogueTree::DialogueTree(Teacher::DialogueType t) :
      m_current (nullptr),
      m_root    (nullptr),
      m_switchTo(t)
    {}

    void
    DialogueTree::setTree(Branch* tree, bool permanent)
    {
        if (permanent)
            m_root = tree;
        m_current = tree;
    }

    bool
    Answers::removeAnswer(Sentence* s)
    {
        unsigned i=0;
        while (i < m_answers.size())
        {
            if (m_answers[i] == s)
            {
                m_answers.erase(m_answers.begin()+i);
                return true;
            }
            ++i;
        }
        return false;
    }

    bool
    Answers::removeAnswer(sf::String s)
    {
        unsigned i=0;
        while (i<m_answers.size())
        {
            if (m_answers[i]->getSentence() == s)
            {
                m_answers.erase(m_answers.begin()+i);
                return true;
            }
            ++i;
        }
        return false;
    }

    Sentence*
    Answers::find(sf::String sought) const
    {
        for (unsigned i=0; i<m_answers.size(); ++i)
        {
            if (m_answers[i]->getSentence() == sought)
                return m_answers[i];
        }
        return nullptr;
    }

}
