/**
 * @file src/program/game/ui/Conversation.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../../Settings.hpp"
#include "../../Resources.hpp"

#include "../../gui/Menu.hpp"
#include "../../gui/Text.hpp"

#include "Conversation.hpp"

namespace rr
{

    Conversation::Conversation(Player* p) :
      m_wConv   ("", sf::Vector2f(1230, 200), sf::Vector2f(25, 25)),
      m_wOpts   ("", sf::Vector2f(1230, 200), sf::Vector2f(25, Settings::graphics.resolution.y - 225)),
      m_dialogue(nullptr),
      m_player  (p)
    {
        m_shadow.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        m_shadow.setPosition (sf::Vector2f(0, 0));
        m_shadow.setFillColor(sf::Color(0, 0, 0, 172));

        auto text = new Text(sf::Vector2f(20, 20), "", Resources::font.Unifont, 20);
             text->wrap(1190);
        m_wConv += text;

        m_wOpts += new Menu(sf::Vector2f(10, 10));
    }

    void
    Conversation::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (isOpen())
        {
            target.draw(m_shadow);
            target.draw(m_wConv);
            target.draw(m_wOpts);
        }
    }

    void
    Conversation::buttonEvents(sf::RenderWindow& rw, sf::Event& event, Game* g)
    {
        if (m_wOpts.isVisible())
        {
            sf::String action = m_wOpts.getComponent <Menu> (0)->getChosenOption(rw, event);

            auto answers = (Answers*) m_dialogue->getCurrentBranch();

            // removing the skill teaching answers if player already has learnt the skills
            {
                bool update = false;
                if (m_player->getAttributes().crafting)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.carpenter.skill"]))
                        update = true;
                }

                if (m_player->getAttributes().alchemy)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.alchemist.skill"]))
                        update = true;
                }

                if (m_player->getAttributes().melee_weapon_mastery)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.swordsman.skill"]))
                        update = true;
                }

                if (m_player->getAttributes().ranged_weapon_mastery)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.sharpshooter.skill"]))
                        update = true;
                }

                if (m_player->getAttributes().eagle_eye)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.kungfu.skill1"]))
                        update = true;
                }

                if (m_player->getAttributes().mana_regeneration)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.kungfu.skill2"]))
                        update = true;
                }

                if (m_player->getAttributes().health_regeneration)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.kungfu.skill3"]))
                        update = true;
                }

                if (m_player->getAttributes().faster_learning)
                {
                    if (answers->removeAnswer(Resources::dictionary["teacher.kungfu.skill4"]))
                        update = true;
                }

                // after removing any option the choice menu must be updated
                // unless you still want to see this option
                if (update)
                {
                    auto menu = m_wOpts.getComponent <Menu> (0);
                    auto answers = (Answers*) m_dialogue->getCurrentBranch();

                    menu->clear();
                    for (unsigned i = 0; i < answers->getAnswers().size(); ++i)
                    {
                        menu->addOption(answers->getAnswers()[i]->getSentence());
                    }
                }
            }

            // recognizing the choice
            auto chosen = ((Answers*) m_dialogue->getCurrentBranch())->find(action);
            if (chosen != nullptr)
                m_dialogue->setTree(chosen);

            // recognizing if the choice is a request for learning
            // a skill or increasing some attributes
            if (action == Resources::dictionary["teacher.swordsman.skill"])
            {
                if (g->getPlayer()->getAttributes().skillPoints >= 10 && g->getInventory()->getGold() >= 2)
                {
                    g->getPlayer()->learnSkill(Book::MELEE_WEAPON_MASTERY, 10);
                    g->getInventory()->removeItem(new Coin(Coin::GOLDEN), 2);
                    answers->removeAnswer(chosen);
                    m_dialogue->goLeft();
                }
                else
                {
                    m_dialogue->goRight();
                }
            }
            else if (action == Resources::dictionary["teacher.swordsman.strength5"])
            {
                if (g->getPlayer()->getAttributes().skillPoints >= 5 && g->getInventory()->getGold() >= 1)
                {
                    g->getPlayer()->increaseAttribute(Player::STRENGTH, 5, 5);
                    g->getInventory()->removeItem(new Coin(Coin::GOLDEN), 1);
                    m_dialogue->goLeft();
                }
                else
                {
                    m_dialogue->goRight();
                }
            }
            else if (action == Resources::dictionary["teacher.swordsman.strength1"])
            {
                if (g->getPlayer()->getAttributes().skillPoints >= 1 && g->getInventory()->getSilver() >= 10)
                {
                    g->getPlayer()->increaseAttribute(Player::STRENGTH, 1, 1);
                    g->getInventory()->removeItem(new Coin(Coin::SILVER), 10);
                    m_dialogue->goLeft();
                }
                else
                {
                    m_dialogue->goRight();
                }
            }

            // recognizing the type of the next branch of the dialogue tree

            // if the next branch is a nullptr then it means that this is the end
            // of the dialogue
            if (chosen != nullptr)
            {
                m_wOpts.getComponent <Menu> (0)->clear();
                if (instanceof <Answers, Branch> (m_dialogue->getCurrentBranch()))
                {
                    auto menu = m_wOpts.getComponent <Menu> (0);
                    auto answers = (Answers*) m_dialogue->getCurrentBranch();

                    for (unsigned i = 0; i < answers->getAnswers().size(); ++i)
                    {
                        menu->addOption(answers->getAnswers()[i]->getSentence());
                    }
                    m_wOpts.setVisible(true);
                    m_wConv.setVisible(false);
                }
                else if (instanceof <Sentence, Branch> (m_dialogue->getCurrentBranch()))
                {
                    m_wConv.getComponent <Text> (0)->setString(((Sentence*) m_dialogue->getCurrentBranch())->getSentence());
                    m_wOpts.setVisible(false);
                    m_wConv.setVisible(true);
                }
                else
                {
                    close(g);
                }
            }
        }
        else if (m_wConv.isVisible())
        {
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape))
                m_dialogue->goLeft();

            if (m_dialogue->getCurrentBranch() == nullptr)
                close(g);
            else
            {
                if (instanceof <Answers, Branch> (m_dialogue->getCurrentBranch()))
                {
                    auto menu = m_wOpts.getComponent <Menu> (0);
                    auto answers = (Answers*) m_dialogue->getCurrentBranch();

                    for (unsigned i = 0; i < answers->getAnswers().size(); ++i)
                    {
                        menu->addOption(answers->getAnswers()[i]->getSentence());
                    }
                    m_wOpts.setVisible(true);
                    m_wConv.setVisible(false);
                }
                else if (instanceof <Sentence, Branch> (m_dialogue->getCurrentBranch()))
                {
                    m_wConv.getComponent <Text> (0)->setString(((Sentence*) m_dialogue->getCurrentBranch())->getSentence());

                    if (((Sentence*) m_dialogue->getCurrentBranch())->getSpeaker() == Sentence::_NPC)
                        m_wConv.setHeader(m_npcName);
                    else
                        m_wConv.setHeader("");

                    m_wOpts.setVisible(false);
                    m_wConv.setVisible(true);
                }
            }
        }
    }

    void
    Conversation::open(NPC* npc)
    {
        m_dialogue = npc->getDialogue();
        m_npcName  = npc->getName();

        if (instanceof <Answers, Branch> (m_dialogue->getCurrentBranch()))
        {
            auto menu = m_wOpts.getComponent <Menu> (0);
            auto answers = (Answers*) m_dialogue->getCurrentBranch();

            for (unsigned i = 0; i < answers->getAnswers().size(); ++i)
            {
                menu->addOption(answers->getAnswers()[i]->getSentence());
            }

            m_wOpts.setVisible(true);
        }
        else if (instanceof <Sentence, Branch> (m_dialogue->getCurrentBranch()))
        {
            m_wConv.getComponent <Text> (0)->setString(((Sentence*) m_dialogue->getCurrentBranch())->getSentence());

            if (((Sentence*) m_dialogue->getCurrentBranch())->getSpeaker() == Sentence::_NPC)
                m_wConv.setHeader(m_npcName);
            else
                m_wConv.setHeader("");

            m_wConv.setVisible(true);
        }
    }

    void
    Conversation::close(Game* g)
    {
        m_dialogue->reset();
        m_dialogue = nullptr;

        m_wOpts.getComponent <Menu> (0)->clear();

        m_wOpts.setVisible(false);
        m_wConv.setVisible(false);

        g->pause(false);
    }

}
