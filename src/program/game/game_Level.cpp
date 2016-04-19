/**
 * @file src/program/game/menus/game_Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"
#include "../program.hpp"
#include "../funcs/files.hpp"
#include "../funcs/items.hpp"

extern rr::Resources resources;

namespace rr {

    Level::Level() {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(13728);
    }

    void Level::addItem(Item* i, sf::Vector2f position) {
        if (i != nullptr) {
            entities.push_back(i);
            entities.back()->setPosition(position);
        }
    }

    void Level::addChest(Chest* c) {
        entities.push_back(c);
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(m_vertices, states);
    }

    void Level::drawObjects(sf::RenderWindow& rw) {
        for (auto x : entities)
            x->draw(rw);
    }

    void Level::generateWorld() {
        int tiles[3432];
        for (int i=0; i<3432; i++) {
            if (i%78 == 0 || (i+1)%78 == 0 || i<78 || i>3354)
                tiles[i] = 1;
            else {
                tiles[i] = (rand()%250)?2:0;
            }
        }

        // generate the tile map
        for (unsigned int i=0; i<78; ++i) {
            for (unsigned int j=0; j<44; ++j) {
                int tileNumber;

                switch (tiles[i+j*78]) {
                case 0: tileNumber = 0;            break; // chasm
                case 1: tileNumber = rand()%14+1;  break; // wall
                case 2: tileNumber = rand()%10+15; break; // floor
                }

                int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                sf::Vertex* quad = &m_vertices[(i+j*78)*4];

                quad[0].position = sf::Vector2f(  i  *80,   j  *80);
                quad[1].position = sf::Vector2f((i+1)*80,   j  *80);
                quad[2].position = sf::Vector2f((i+1)*80, (j+1)*80);
                quad[3].position = sf::Vector2f(  i  *80, (j+1)*80);

                quad[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
                quad[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
                quad[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
                quad[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
            }
        }

        // generate the objects
        for (int i=0; i<20; i++) {
            addItem(getItemFromID(100 + (rand()%3)*10 + rand()%9, 1),
                    sf::Vector2f(1+(rand()%76)*80.f, 1+(rand()%43)*80.f+1));
        }
        for (int i=0; i<11; i++) {
            addChest(new Chest(sf::Vector2f((rand()%76+1)*80, (rand()%42+1)*80),
                               Chest::SPECIAL,
                               getItemFromID(100 + (rand()%3)*10 + rand()%9, 1)));
        }
        for (int i=0; i<4; i++) {
            addChest(new Chest(sf::Vector2f((rand()%76+1)*80, (rand()%42+1)*80),
                               Chest::REGULAR,
                               getItemFromID(100 + (rand()%3)*10 + rand()%9, 1)));
        }
    }

    void Level::loadFromFile(const char*) {

    }

}
