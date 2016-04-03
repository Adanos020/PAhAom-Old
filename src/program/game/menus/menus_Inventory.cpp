#include "menus.h"

extern std::map<sf::String, sf::String> dictionary;
extern rr::Settings settings;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;

namespace rr {

	Inventory::Inventory(sf::RenderWindow& rw) {
#define dict(x) dictionary[x]
#define component(w, c, i) w->getComponent<c>(i)

		wInve = new Window(nullptr, dict("gui.window.inventory"), sf::Vector2f(800, 400), sf::Vector2f(rw.getSize().x/2-400, rw.getSize().y/2-200));
		for (int i=0, j=0; i<8 && j<4; i++, j++)
			wInve->addComponent(new Slot(wInve, sf::Vector2f(90, 90), sf::Vector2f(5+i*95, 20+j*95)));
		wInve->addComponent(new Button(wInve, sf::Vector2f(0, 0), dict("gui.button.quit"), 30));
		component(wInve, Button, 0)->setPosition(sf::Vector2f(wInve->getSize().x-component(wInve, Button, 0)->getSize().x-5, wInve->getSize().y-component(wInve, Button, 0)->getSize().y-5));

#undef dict
#undef component
	}

	Inventory::~Inventory() {
		delete wInve;
	}

	void Inventory::buttonEvents(sf::RenderWindow& rw) {

	}

	void Inventory::draw(sf::RenderWindow& rw) {
		wInve->draw(rw);
	}

}
