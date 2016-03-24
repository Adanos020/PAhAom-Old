#ifndef menus_h
#define menus_h

#include "../../gui/gui.h"
#include "../game.h"

namespace rr {

    class Game;

    class MainMenu {
    private:
        Text* title;
        Window* wMenu;
        Window* wOpts;
        Window* wHelp;
        Window* wCred;
    public:
        MainMenu(sf::RenderWindow&);
        ~MainMenu();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

    class PauseMenu {
    private:
        Text* title;
        Window* wMenu;
        Window* wOpts;
        Window* wHelp;
    public:
        PauseMenu(sf::RenderWindow&);
        ~PauseMenu();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

}

#endif // menus_h
