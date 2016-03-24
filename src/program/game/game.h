#ifndef game_h
#define game_h

#include <ctime>
#include "menus/menus.h"
#include "player/player.h"
#include "../program.h"

namespace rr {

    class MainMenu;
    class PauseMenu;
    struct Settings;

    class Game {
      private:
        MainMenu* mainMenu;
        PauseMenu* pauseMenu;

        Player* player;

        bool started;
        bool paused;
      public:
        Game(sf::RenderWindow&, Settings);
        ~Game();

        void draw(sf::RenderWindow&, sf::View&);
        void buttonEvents(sf::RenderWindow&, sf::View&);
        void controls(float);

        void start(bool);
        void pause(bool);
        void save();
        bool load();
        bool loadNewGame();

        bool isStarted();
        bool isPaused();
    };

}

#endif // game_h
