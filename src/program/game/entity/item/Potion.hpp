/**
 * @file src/program/game/item/Potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_POTION_HPP
#define ITEM_POTION_HPP

#include "Item.hpp"

namespace rr {

    class Potion : public Discoverable {
    private: virtual void           initialize     ()                  override;
    
    public:  enum Effect {
                 HEALING,
                 MAGIC,
                 STRENGTH,
                 DEXTERITY,
                 SPEED,
                 REGENERATION,
                 POISON,
                 SLOWNESS,
                 WEAKNESS
             } effect_;
             enum Size {
                 BIG,
                 MEDIUM,
                 SMALL
             } size_;
             
             static bool identified_[9];
         
             Potion(Effect, Size, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
             Potion(Potion const&);
         
             virtual Entity*        clone          ()            const override { return new Potion(*this); }
             virtual Entity*        create         ()            const override { return new Potion(HEALING, SMALL); }
         
             virtual void           draw           (sf::RenderWindow&) override;
         
             virtual void           reveal         ()                  override { identified_[effect_] = true; }
             virtual bool           isDiscovered   ()            const override { return identified_[effect_]; }
         
             virtual sf::String     getName        ()            const override;
             virtual sf::String     getDescription ()            const override;
         
             void                   setPosition    (sf::Vector2i)      override;
             void                   setRealPosition(sf::Vector2f pos)  override;
         
             virtual std::ifstream& operator<<     (std::ifstream&)         override;
             virtual std::ofstream& operator>>     (std::ofstream&)         override;
    };

}

#endif // ITEM_POTION_HPP
