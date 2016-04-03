/**
 * @file src/program/game/item/potion.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#ifndef item_Potion_hpp
#define item_Potion_hpp

#include "item.h"

namespace rr {

	class Potion :public Discoverable, public Item {
	  public:
		enum Effect {
			HEALING,
			MAGIC,
			STRENGTH,
			DEXTERITY,
			SPEED,
			REGENERATION,
			POISON,
			SLOWNESS,
			WEAKNESS
		};
		enum Size {
			SMALL,
			MEDIUM,
			BIG
		};

		Potion (Effect, Size, int am, sf::Vector2f pos = sf::Vector2f(0, 0));
		~Potion();

		virtual void draw      (sf::RenderWindow&) override;
		virtual void editAmount(int)               override;
		virtual void update    ()                  override;
		virtual void reveal    ()                  override;

		Effect getEffect       () { return effect; }
		Size getSize           () { return size; }
	  private:
		Effect effect;
          Size size;
	};

}

#endif // item_Potion_hpp
