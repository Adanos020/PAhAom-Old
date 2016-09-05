/**
 * @file src/program/game/dialogue/Dialogue.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>
#include <fstream>
#include <string>

#include "../../funcs/files.hpp"

#include "Dialogue.hpp"

namespace rr
{

    Sentence::Sentence(Sentence::Speaker s, sf::String sn) :
      speaker_ (s),
      sentence_(sn) {}

    DialogueTree::DialogueTree() :
      current_(nullptr),
      root_   (nullptr) {}

    void
    DialogueTree::setTree(Branch* tree, bool permanent)
    {
        if (permanent)
            root_ = tree;
        current_ = tree;
    }

    bool
    Answers::removeAnswer(Sentence* s)
    {
        unsigned i=0;
        while (i < answers_.size())
        {
            if (answers_[i] == s)
            {
                answers_.erase(answers_.begin()+i);
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
        while (i<answers_.size())
        {
            if (answers_[i]->getSentence() == s)
            {
                answers_.erase(answers_.begin()+i);
                return true;
            }
            ++i;
        }
        return false;
    }

    Sentence*
    Answers::find(sf::String sought) const
    {
        for (unsigned i=0; i<answers_.size(); ++i)
        {
            if (answers_[i]->getSentence() == sought)
                return answers_[i];
        }
        return nullptr;
    }

}
