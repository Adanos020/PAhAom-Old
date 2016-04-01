#include "menus.h"

extern std::map<sf::String, sf::String> dictionary;
extern rr::Settings settings;
extern sf::Font font_Pixel;
extern sf::Font font_Unifont;

namespace rr {

    Inventory::Inventory(sf::RenderWindow& rw) {
        #define dict(x) dictionary[x]

        wInve = new Window(nullptr, dict("gui.window.inventory"), sf::Vector2f(800, 400), sf::Vector2f(rw.getSize().x/2-400, rw.getSize().y/2-200));
    }

    Inventory::~Inventory() {
        delete wInve;
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw) {

    }

    void Inventory::draw(sf::RenderWindow& rw, sf::View& v) {
        rw.setView(rw.getDefaultView());
        wInve->draw(rw);
        rw.setView(v);
    }

}
