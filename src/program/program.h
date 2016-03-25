#ifndef program_h
#define program_h

#include <SFML/Graphics.hpp>

#include "game/game.h"

namespace rr {

    class Game;

    struct Settings {
      public:
        sf::ContextSettings csettings;
        sf::Vector2u resolution;

        bool vsync;
        bool fullscreen;
        std::string language;

        void print();
        void save();
    };

    class Program {
      private:
        sf::RenderWindow window;
        sf::Event event;
        sf::View view;

        Game* game;

        void runGame();
        bool readConfig();
        bool readDictionary();
        bool loadResources();
      public:
        Program();
        ~Program();
    };

}

#endif // program_h
