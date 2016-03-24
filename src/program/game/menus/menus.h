#ifndef menus_h
#define menus_h

#include "../../gui/gui.h"
#include "../game.h"
#include "../../program.h"

namespace rr {

    class Game;
    struct Settings;

    class MainMenu {
      private:
        Text* title;
        Window* wMenu;
        Window* wOpts;
        Window* wHelp;
        Window* wCred;
      public:
        MainMenu(sf::RenderWindow&, Settings);
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
        PauseMenu(sf::RenderWindow&, Settings);
        ~PauseMenu();

        void buttonEvents(sf::RenderWindow&, Game*);
        void draw(sf::RenderWindow&, sf::View&);
    };

}

#endif // menus_h
