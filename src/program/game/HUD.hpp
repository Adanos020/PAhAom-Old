/**
 * @file src/program/game/HUD.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef HUD_HPP
#define HUD_HPP

#include "../gui/Bar.hpp"
#include "../gui/Text.hpp"

namespace rr {

/// Class for the HUD
    class HUD {
    private: Bar  bHP_;
             Bar  bMP_;
             Bar  bXP_;
             Text tXPlevel_;
             Text tLevelNumber;
    
    public:  HUD();
            ~HUD();
        
         /// Updates the HUD state
             void update      (Player*, int lvl);
         /// Method drawing the HUD components
             void draw        (sf::RenderWindow&);
    };

}

#endif
