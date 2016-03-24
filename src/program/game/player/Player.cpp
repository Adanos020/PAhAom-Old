#include "player.h"

namespace rr {

    Player::Player(sf::Vector2f pos) {
        skin.loadFromFile("data/graphics/player.png");

        body.resize(4);
        body.setPrimitiveType(sf::Quads);

        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+70, pos.y);
        body[2].position = sf::Vector2f(pos.x+70, pos.y+70);
        body[3].position = sf::Vector2f(pos.x, pos.y+70);

        body[0].texCoords = sf::Vector2f(0, 0);
        body[1].texCoords = sf::Vector2f(14, 0);
        body[2].texCoords = sf::Vector2f(14, 14);
        body[3].texCoords = sf::Vector2f(0, 14);

        position = pos;
        velocity = 0.5;
        hp = 30;
        sp = 0;
        exp = 0;
        lvl = 0;
    }

    Player::~Player() {

    }

    void Player::setPosition(sf::Vector2f pos) {
        if (position != pos) position = pos;
        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+70, pos.y);
        body[2].position = sf::Vector2f(pos.x+70, pos.y+70);
        body[3].position = sf::Vector2f(pos.x, pos.y+70);
    }

    void Player::go(double ts, direction di) {
        if (di == up) {
            position.y -= ts*velocity;
            setPosition(position);
        }
        else if (di == down) {
            position.y += ts*velocity;
            setPosition(position);
        }
        else if (di == left) {
            position.x -= ts*velocity;
            setPosition(position);

            body[0].texCoords = sf::Vector2f(0, 14);
            body[1].texCoords = sf::Vector2f(14, 14);
            body[2].texCoords = sf::Vector2f(14, 28);
            body[3].texCoords = sf::Vector2f(0, 28);
        }
        else if (di == right) {
            position.x += ts*velocity;
            setPosition(position);

            body[0].texCoords = sf::Vector2f(0, 0);
            body[1].texCoords = sf::Vector2f(14, 0);
            body[2].texCoords = sf::Vector2f(14, 14);
            body[3].texCoords = sf::Vector2f(0, 14);
        }
    }

    void Player::draw(sf::RenderWindow& rw) {
        rw.draw(body, &skin);
    }

}
