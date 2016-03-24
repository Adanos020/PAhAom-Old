#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>

namespace rr {

    class Player {
    private:
        sf::VertexArray body;
        sf::Texture skin;
        sf::Vector2f position;

        double velocity;

        double hp;
        double sp;
        int exp;
        int lvl;
    public:
        Player(sf::Vector2f pos);
        ~Player();

        enum direction { down, left, right, up };

        void setPosition(sf::Vector2f);

        void go(double timeStep, direction);
        void draw(sf::RenderWindow&);
    };

}

#endif // player_h
