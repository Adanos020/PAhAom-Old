/**
 * @file src/program/game/item/item_Rune.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Rune_hpp
#define item_Rune_hpp

#include "item.hpp"

namespace rr {

    class Rune : public Discoverable {
    private:
        virtual void           initialize     ()                  override;
    public:
        enum Type {
            HEAL,
            FIREBOLT,
            LIGHTNING,
            ICE_BULLET,
            TELEPORT,
            FIRE_RAIN,
            STORM,
            ICE_WAVE,
            TIME_FREEZING,
            IDENTIFY,
            UNCURSE,
            TELEKINESIS
        } type_;

         Rune(Type, int am = 1, sf::Vector2i pos = sf::Vector2i(0, 0));
         Rune(Rune const&);
        ~Rune() {}

        virtual Entity*        clone          ()            const override { return new Rune(*this); }
        virtual Entity*        create         ()            const override { return new Rune(HEAL); }

        virtual void           draw           (sf::RenderWindow&) override;
        virtual void           reveal         ()                  override;

        void                   setPosition    (sf::Vector2i)      override;
        void                   setRealPosition(sf::Vector2f pos)  override;

        virtual std::ifstream& operator<<     (std::ifstream&)    override;
        virtual std::ofstream& operator>>     (std::ofstream&)    override;
    };

}

#endif // item_Rune_hpp
