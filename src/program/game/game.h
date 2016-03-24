#ifndef game_h
#define game_h

#include <ctime>
#include "menus/menus.h"
#include "player/player.h"

namespace rr {

    class MainMenu;
    class PauseMenu;

    class Game {
    private:
        MainMenu* mainMenu;
        PauseMenu* pauseMenu;

        Player* player;

        bool started;
        bool paused;
    public:
        Game(sf::RenderWindow&);
        ~Game();

        void draw(sf::RenderWindow&, sf::View&);
        void buttonEvents(sf::RenderWindow&, sf::View&);
        void controls(clock_t);

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
