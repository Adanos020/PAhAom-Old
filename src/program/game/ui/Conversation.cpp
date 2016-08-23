/**
 * @file src/program/game/ui/Conversation.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "../../Settings.hpp"
#include "../../Resources.hpp"

#include "../../gui/Menu.hpp"
#include "../../gui/Text.hpp"

#include "Conversation.hpp"

namespace rr {

    Conversation::Conversation(Player* p) :
      wConv_   ("", sf::Vector2f(Settings::graphics.resolution.x - 50, 200), sf::Vector2f(25, 25)),
      wOpts_   ("", sf::Vector2f(Settings::graphics.resolution.x - 50, 200), sf::Vector2f(25, Settings::graphics.resolution.y - 225)),
      dialogue_(nullptr),
      player_  (p)
    {
        shadow_.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

        auto text = new Text(sf::Vector2f(20, 20), "", Resources::font.Unifont, 20);
             text->wrap(wConv_.getSize().x-40);
        wConv_ += text;

        wOpts_ += new Menu(sf::Vector2f(10, 10));
    }

    void Conversation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (isOpen()) {
            target.draw(shadow_);
            target.draw(wConv_);
            target.draw(wOpts_);
        }
    }

    void Conversation::buttonEvents(sf::RenderWindow& rw, sf::Event& event, Game* g) {
        if (wOpts_.isVisible()) {
            sf::String action = wOpts_.getComponent<Menu>(0)->getChosenOption(rw, event);

            auto answers = (Answers*) dialogue_->getCurrentBranch();

            {   // removing the skill teaching answers if player already has learnt the skills
                auto temp = ((Answers*) dialogue_->getCurrentBranch())->find("Crafting (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().crafting
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Alchemy (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().alchemy
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Cold Weapon Mastery (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().cold_weapon_mastery
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Ranged Weapon Mastery (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().ranged_weapon_mastery
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Enhanced Sight (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().eagle_eye
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Mana Regeneration (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().mana_regeneration
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Health Regeneration (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().health_regeneration
                    ) answers->removeAnswer(temp);

                temp = ((Answers*) dialogue_->getCurrentBranch())->find("Faster Learning (10SP, 2 gold)");
                if (  temp != nullptr
                   && player_->getAttributes().faster_learning
                    ) answers->removeAnswer(temp);
            }
            
            auto chosen = ((Answers*) dialogue_->getCurrentBranch())->find(action);
            if (  chosen != nullptr
                ) dialogue_->setTree(chosen);

            if (action == "Cold Weapon Mastery (10SP, 2 gold)") {
                if (g->getPlayer()->getAttributes().skillPoints >= 10 && g->getInventory()->getGold() >= 2) {
                    g->getPlayer()->learnSkill(Book::COLD_WEAPON_MASTERY, 10);
                    g->getInventory()->removeItem(new Coin(Coin::GOLDEN), 2);
                    answers->removeAnswer(chosen);
                    dialogue_->goLeft();
                }
                else {
                    dialogue_->goRight();
                }
            }
            else if (action == "+5STR (5SP, 1 gold)") {
                if (g->getPlayer()->getAttributes().skillPoints >= 5 && g->getInventory()->getGold() >= 1) {
                    g->getPlayer()->increaseAttribute(Player::STRENGTH, 5, 5);
                    g->getInventory()->removeItem(new Coin(Coin::GOLDEN), 1);
                    dialogue_->goLeft();
                }
                else {
                    dialogue_->goRight();
                }
            }
            else if (action == "+1STR (1SP, 10 silver)") {
                if (g->getPlayer()->getAttributes().skillPoints >= 1 && g->getInventory()->getSilver() >= 10) {
                    g->getPlayer()->increaseAttribute(Player::STRENGTH, 1, 1);
                    g->getInventory()->removeItem(new Coin(Coin::SILVER), 10);
                    dialogue_->goLeft();
                }
                else {
                    dialogue_->goRight();
                }
            }

            if (chosen != nullptr) {
                wOpts_.getComponent<Menu>(0)->clear();
                if (instanceof <Answers, Branch> (dialogue_->getCurrentBranch())) {
                    auto menu = wOpts_.getComponent <Menu> (0);
                    auto answers = (Answers*) dialogue_->getCurrentBranch();

                    for (unsigned i=0; i<answers->getAnswers().size(); ++i) {
                        menu->addOption(answers->getAnswers()[i]->getSentence());
                    }
                    wOpts_.setVisible(true);
                    wConv_.setVisible(false);
                }
                else if (instanceof <Sentence, Branch> (dialogue_->getCurrentBranch())) {
                    wConv_.getComponent <Text> (0)->setString(((Sentence*) dialogue_->getCurrentBranch())->getSentence());
                    wOpts_.setVisible(false);
                    wConv_.setVisible(true);
                }
                else {
                    close(g);
                }
            }
        }
        else if (wConv_.isVisible()) {
            if (  event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
                ) dialogue_->goLeft();

            if (  dialogue_->getCurrentBranch() == nullptr
                ) close(g);
            else {
                if (instanceof <Answers, Branch> (dialogue_->getCurrentBranch())) {
                    auto menu = wOpts_.getComponent <Menu> (0);
                    auto answers = (Answers*) dialogue_->getCurrentBranch();

                    for (unsigned i=0; i<answers->getAnswers().size(); ++i) {
                        menu->addOption(answers->getAnswers()[i]->getSentence());
                    }
                    wOpts_.setVisible(true);
                    wConv_.setVisible(false);
                }
                else if (instanceof <Sentence, Branch> (dialogue_->getCurrentBranch())) {
                    wConv_.getComponent <Text> (0)->setString(((Sentence*) dialogue_->getCurrentBranch())->getSentence());
                    
                    if ( ((Sentence*) dialogue_->getCurrentBranch())->getSpeaker() == Sentence::_NPC
                        ) wConv_.setHeader(npcName_);
                    else  wConv_.setHeader("");
                    
                    wOpts_.setVisible(false);
                    wConv_.setVisible(true);
                }
            }
        }
    }

    void Conversation::open(NPC* npc) {
        dialogue_ = npc->getDialogue();
        npcName_  = npc->getName();

        if (instanceof <Answers, Branch> (dialogue_->getCurrentBranch())) {
            auto menu = wOpts_.getComponent <Menu> (0);
            auto answers = (Answers*) dialogue_->getCurrentBranch();

            for (unsigned i=0; i<answers->getAnswers().size(); ++i) {
                menu->addOption(answers->getAnswers()[i]->getSentence());
            }

            wOpts_.setVisible(true);
        }
        else if (instanceof <Sentence, Branch> (dialogue_->getCurrentBranch())) {
            wConv_.getComponent <Text> (0)->setString(((Sentence*) dialogue_->getCurrentBranch())->getSentence());
            
            if ( ((Sentence*) dialogue_->getCurrentBranch())->getSpeaker() == Sentence::_NPC
                ) wConv_.setHeader(npcName_);
            else  wConv_.setHeader("");
            
            wConv_.setVisible(true);
        }
    }

    void Conversation::close(Game* g) {
        dialogue_->reset();
        dialogue_ = nullptr;

        wOpts_.getComponent<Menu>(0)->clear();

        wOpts_.setVisible(false);
        wConv_.setVisible(false);

        g->pause(false);
    }

}
