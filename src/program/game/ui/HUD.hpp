/**
 * @file src/program/game/ui/HUD.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef UI_HUD_HPP
#define UI_HUD_HPP

#include "../../gui/Bar.hpp"
#include "../../gui/Text.hpp"

namespace rr
{

    class HUD : public sf::Drawable
    {
    private: Bar  m_bHP;
             Bar  m_bMP;
             Bar  m_bXP;
             Text m_tXPlevel;
             Text m_tLevelNumber;
             Text m_tFPS;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the HUD on the screen.
             ////////////////////////////////////////////////////////////////////////
             virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             HUD();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the HUD's state.
             ////////////////////////////////////////////////////////////////////////
             void update(Player*, int lvl, sf::Time&);
    };

}

#endif // UI_HUD_HPP
