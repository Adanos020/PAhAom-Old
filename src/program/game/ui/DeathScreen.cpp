/**
 * @file src/program/game/ui/DeathScreen.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "DeathScreen.hpp"

#include "../../Resources.hpp"
#include "../../Settings.hpp"

namespace rr {

    DeathScreen::DeathScreen() :
      endAnimation_(sf::Time::Zero                                                                                        ),
      tYouDied_    (Resources::dictionary["gui.text.you_died"], Resources::font.FinalFantasy, 200, sf::Color(255, 0, 0, 0)),
      bNewGame_    (sf::Vector2f(0, 0), Resources::dictionary["gui.button.newgame"], 52                                   ),
      bQuit_       (sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"   ], 52                                   ),
      visible_     (false                                                                                                 )
    {
        shadow_.setSize((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(255, 0, 0, 0));

        tYouDied_.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2 - tYouDied_.getSize().x/2 - 2.5f,
                                           Settings::graphics.resolution.y/2 - tYouDied_.getSize().y/0.5));

        bNewGame_.setPosition(sf::Vector2f(Settings::graphics.resolution.x/2 - (bNewGame_.getSize().x + bQuit_.getSize().x+7.5f)/2,
                                           Settings::graphics.resolution.y/2 + bNewGame_.getSize().y*0.25f));
        bQuit_.setPosition(sf::Vector2f(bNewGame_.getSize().x+5, 0) + bNewGame_.getPosition());
    }

    void DeathScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (visible_) {
            target.draw(shadow_  , states);
            target.draw(tYouDied_, states);
            target.draw(bNewGame_, states);
            target.draw(bQuit_   , states);
        }
    }

    void DeathScreen::buttonEvents(sf::RenderWindow& rw, sf::Event& event, Game* g) {
        if (visible_) {
            if (bNewGame_.isPressed(rw, event)) {
                visible_ = false;
                g->loadNewGame();
            }
            if (bQuit_.isPressed(rw, event)) {
                visible_ = false;
                reset();
                g->start(false);
            }
        }
    }

    void DeathScreen::update(sf::Time timeStep) {
        if (visible_) {
            if (endAnimation_.asSeconds() <= 1.f) {
                sf::Color shadow  = shadow_  .getFillColor();
                sf::Color youdied = tYouDied_.getFillColor();

                shadow .a = 140 * endAnimation_.asSeconds();
                youdied.a = 255 * endAnimation_.asSeconds();

                shadow_  .setFillColor(shadow);
                tYouDied_.setFillColor(youdied);

                endAnimation_ += timeStep;
            }
        }
    }

    void DeathScreen::reset() {
        endAnimation_ = sf::Time::Zero;
        tYouDied_.setFillColor(sf::Color(255, 0, 0, 0));
        shadow_  .setFillColor(sf::Color(255, 0, 0, 0));
    }

}
