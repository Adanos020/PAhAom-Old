/**
 * @file src/program/game/dialogue/Dialogue.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

namespace rr {
    
    class Branch {
    private: Branch* left_  = nullptr;
             Branch* right_ = nullptr;
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Virtual destructor.
             ////////////////////////////////////////////////////////////////////////
     virtual ~Branch() { if (left_ != nullptr) delete left_; if (right_ != nullptr) delete right_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the left link.
             ////////////////////////////////////////////////////////////////////////
             void setLeft(Branch* b) { left_ = b; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the right link.
             ////////////////////////////////////////////////////////////////////////
             void setRight(Branch* b) { right_ = b; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the left link.
             ////////////////////////////////////////////////////////////////////////
             Branch* getLeft() const { return left_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the right link.
             ////////////////////////////////////////////////////////////////////////
             Branch* getRight() const { return right_; }
    };

    class Sentence : public Branch {
    public:  enum Speaker {
                 PLAYER,
                 _NPC
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Sentence(Speaker, sf::String);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the speaker of the sentence.
             ////////////////////////////////////////////////////////////////////////
             Speaker getSpeaker() const { return speaker_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the sentence's string.
             ////////////////////////////////////////////////////////////////////////
             sf::String getSentence() const { return sentence_; }

    private: Speaker    speaker_;
             sf::String sentence_;
    };

    class Answers : public Branch {
    private: std::vector<Sentence*> answers_;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an answer to the list.
             ////////////////////////////////////////////////////////////////////////
             void addAnswer(Sentence* s) { answers_.push_back(s); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes an answer from the list.
             ////////////////////////////////////////////////////////////////////////
             void removeAnswer(Sentence*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes an answer from the list.
             ////////////////////////////////////////////////////////////////////////
             void removeAnswer(sf::String);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the list of answers.
             ////////////////////////////////////////////////////////////////////////
             std::vector<Sentence*> getAnswers() const { return answers_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Finds an answer that equals the given string.
             ///
             /// \return a Sentence branch if the answer is found, nullptr if not.
             ////////////////////////////////////////////////////////////////////////
             Sentence* find(sf::String) const;
    };

    class DialogueTree {
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             DialogueTree();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~DialogueTree() { if (root_ != nullptr) delete root_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Assigns the tree.
             ////////////////////////////////////////////////////////////////////////
             void setTree(Branch*, bool permanent = false);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the pointer to the current branch to its left branch.
             ////////////////////////////////////////////////////////////////////////
             void goLeft() { current_ = current_->getLeft(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the pointer to the current branch to its right branch.
             ////////////////////////////////////////////////////////////////////////
             void goRight() { current_ = current_->getRight(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the current step of the dialogue.
             ////////////////////////////////////////////////////////////////////////
             Branch* getCurrentBranch() { return current_; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the pointer to the current step to the initial one.
             ////////////////////////////////////////////////////////////////////////
             void reset() { current_ = root_; }
    
    private: Branch* current_;
             Branch* root_;
    };

}

#endif // DIALOGUE_HPP
