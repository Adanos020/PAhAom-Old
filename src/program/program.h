#ifndef program_h
#define program_h

#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include "game/game.h"

namespace rr {

    class Program {
    private:
        Game* game;

        sf::RenderWindow window;
        sf::Event event;
        sf::View view;
        sf::Vector2u resolution;

        bool vsync;
        bool fullscreen;
        std::string language;

        void runGame();
        bool readConfig();
        bool readDictionary();
    public:
        Program();
        ~Program();
    };

}

#endif // program_h
