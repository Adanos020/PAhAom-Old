/**
 * @file src/program/game/item/item_RangedWeapon.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_RangedWeapon_hpp
#define item_RangedWeapon_hpp

#include "item.hpp"

namespace rr {

    class RangedWeapon : public Equipable {
    private:
    public:
         RangedWeapon();
         RangedWeapon(RangedWeapon const&);
        ~RangedWeapon();
/*
        virtual Entity*        clone     ()            const override { return new RangedWeapon(*this); }
        virtual Entity*        create    ()            const override { return new RangedWeapon(); }
*/
        virtual void           draw      (sf::RenderWindow&) override;

        virtual sf::String     getName        ()            const override;
        virtual sf::String     getDescription ()            const override;

        virtual std::ifstream& operator<<(std::ifstream&)    override;
        virtual std::ofstream& operator>>(std::ofstream&)    override;
    };

}

#endif // item_RangedWeapon_hpp
