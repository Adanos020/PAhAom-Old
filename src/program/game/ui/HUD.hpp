/**
 * @file src/program/game/ui/HUD.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef UI_HUD_HPP
#define UI_HUD_HPP

#include "../../gui/Bar.hpp"
#include "../../gui/Text.hpp"

namespace rr {

/// Class for the HUD
    class HUD : public sf::Drawable {
    private: Bar  bHP_;
             Bar  bMP_;
             Bar  bXP_;
             Text tXPlevel_;
             Text tLevelNumber_;
             Text tFPS_;

             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:  HUD();
        
         /// Updates the HUD state
             void update      (Player*, int lvl, sf::Time);
    };

}

#endif // UI_HUD_HPP
