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

        grid.setPrimitiveType(sf::Points);
        grid.resize(3432);
    }

    Level::~Level() {
        entities.clear();
    }

    void Level::addEntity(Entity* e, sf::Vector2f position) {
        if (e != nullptr) {
            entities.push_back(e);
            entities.back()->setPosition(position);
        }
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(m_vertices, states);
    }

    void Level::drawObjects(sf::RenderWindow& rw) const {
        for (auto x : entities)
            x->draw(rw);
    }

    void Level::generateWorld() {
        /* generate the tile map */ {
            int tiles[3432];
            for (int i=0; i<3432; i++) {
                if (i%78 == 0 || (i+1)%78 == 0 || i<78 || i>3354)
                    tiles[i] = 1;
                else {
                    tiles[i] = (rand()%250)?2:0;
                }
            }

            for (unsigned int i=0; i<78; ++i) {
                for (unsigned int j=0; j<44; ++j) {
                    int tileNumber;

                    switch (tiles[i+j*78]) {        // giving the grid points a color to distinguish whether a cell is a wall/floor/chasm
                    case 0: tileNumber = 0           ; grid[i+j*78].color = sf::Color::Black; break; // black cell means there is a chasm
                    case 1: tileNumber = rand()%14+1 ; grid[i+j*78].color = sf::Color::White; break; // white stands for a wall
                    case 2: tileNumber = rand()%10+15; grid[i+j*78].color = sf::Color::Blue ; break; // and blue represents the floor
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

                    grid[i+j*78].position = sf::Vector2f(i*80, j*80);
                }
            }
        }

        /* generate the objects */ {
            // here we generate the items
            for (int i=0; i<20; i++) {
                while (true) {
                    int x=rand()%3432;
                    // now we use the cell's color to distinguish which type of tile is in a randomised cell
                    if (grid[x].color == sf::Color::Blue && grid[x].color != sf::Color::Cyan) {
                        addEntity(getItemFromID(100 + (rand()%3)*10 + rand()%9, 1), grid[x].position);
                        grid[x].color = sf::Color::Cyan; // cyan means that the cell is occupied by an object
                        break;
                    }
                }
            }
            // here we generate the chests
            for (int i=0; i<15; i++) {
                while (true) {
                    int x=rand()%3432;
                    if (grid[x].color == sf::Color::Blue && grid[x].color != sf::Color::Cyan) {
                        addEntity(new Chest((rand()%20)?Chest::REGULAR:Chest::SPECIAL, getItemFromID(100+(rand()%3)*10+rand()%9, 1)), grid[x].position);
                        grid[x].color = sf::Color::Cyan;
                        break;
                    }
                }
            }
        }
    }

    void Level::loadFromFile(const char*) {

    }

}
