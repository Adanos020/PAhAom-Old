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
        size = sf::Vector2i(77, 43);
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(size.x*size.y*4);

        for (int i=0; i<size.x; i++)
            grid.push_back(std::vector<Cell>());
    }

    Level::~Level() {
        entities.clear();
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

    bool Level::loadFromFile(const char*) {
        return true;
    }

    void Level::generateWorld() {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i=0; i<size.x; i++)
            for (int j=0; j<size.y; j++)
                grid[i].push_back(WALL);

     // at this point we generate some rooms to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the rooms
        for (int i=1; i<size.x; i+=2) {
            for (int j=1; j<size.y; j+=2) {
                if (grid[i][j] != WALL)
                    continue;
                fillWithMaze(i, j);
            }
        }

     // after that we generate the entrances between the rooms and corridors
        connectRooms();

     // and then we can get rid of the dead ends of the corridors
        removeDeadEnds();

     // here we generate the entities
        placeEntities();

     // in the end we generate the tile map from the created array
        generateTileMap();
    }

    void Level::digRooms() {
        for (int i=0; i<100; i++) {
            sf::Vector2i rsize((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((size.x-rsize.x)/2)*2+1, rand()%((size.y-rsize.y)/2)*2+1);

            bool overlaps = false;
            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                if (grid[i][rpos.y-1] == ROOM || grid[i][rpos.y+rsize.y+1] == ROOM) {
                    overlaps = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+rsize.y && !overlaps; i++) {
                if (grid[rpos.x-1][i] == ROOM || grid[rpos.x+rsize.x][i] == ROOM) {
                    overlaps = true;
                    break;
                }
            }

            if (overlaps)
                continue;

            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                for (int j=rpos.y; j<rpos.y+rsize.y; j++) {
                    grid[i][j] = ROOM;
                }
            }
        }
    }

    void Level::fillWithMaze(int r, int c) {
 // at this point we generate an array of random directions
        int number = rand()%100+100;
        int* directions = new int[number];
        for (int i=0; i<number; i++) {
            directions[i] = rand()%4+1;
        }
     // and now let's start digging
        for (int i = 0; i<number; i++) {
            switch(directions[i]) {
            case 1: // UP
                if (r-2 <= 0)
                    continue;
                if (grid[r-2][c] == WALL) {
                    grid[r-2][c] = CORRIDOR;
                    grid[r-1][c] = CORRIDOR;
                    fillWithMaze(r-2, c);
                }
                break;
            case 2: // RIGHT
                if (c+2 >= size.y-1)
                    continue;
                if (grid[r][c+2] == WALL) {
                    grid[r][c+2] = CORRIDOR;
                    grid[r][c+1] = CORRIDOR;
                    fillWithMaze(r, c+2);
                }
                break;
            case 3: // DOWN
                if (r+2 >= size.x-1)
                    continue;
                if (grid[r+2][c] == WALL) {
                    grid[r+2][c] = CORRIDOR;
                    grid[r+1][c] = CORRIDOR;
                    fillWithMaze(r+2, c);
                }
                break;
            case 4: // LEFT
                if (c-2 <= 0)
                    continue;
                if (grid[r][c-2] == WALL) {
                    grid[r][c-2] = CORRIDOR;
                    grid[r][c-1] = CORRIDOR;
                    fillWithMaze(r, c-2);
                }
                break;
            }
        }
    }

    void Level::connectRooms() {
        for (int i=1; i<size.x-1; i++) {
            for (int j=1; j<size.y-1; j++) {
                if (((grid[i-1][j] != WALL && grid[i+1][j] != WALL && (grid[i-1][j] == ROOM)?true:grid[i-1][j] != grid[i+1][j])
                  || (grid[i][j-1] != WALL && grid[i][j+1] != WALL && (grid[i][j-1] == ROOM)?true:grid[i][j-1] != grid[i][j+1])) && grid[i][j] == WALL && !(rand()%10))
                    grid[i][j] = ENTRANCE;
            }
        }
    }

    void Level::removeDeadEnds() {
        bool done = false;

        while (!done) {
            done = true;
            for (int i=1; i<size.x-1; i++) {
                for (int j=1; j<size.y-1; j++) {
                    if (grid[i][j] == WALL)
                        continue;

                    // If it only has one exit, it's a dead end.
                    int exits = 0;
                    if (grid[i-1][j] != WALL)
                        exits++;
                    if (grid[i+1][j] != WALL)
                        exits++;
                    if (grid[i][j-1] != WALL)
                        exits++;
                    if (grid[i][j+1] != WALL)
                        exits++;

                    if (exits > 1)
                        continue;

                    done = false;
                    grid[i][j] = WALL;
                }
            }
        }
    }

    void Level::generateTileMap() {
        for (int i=0; i<size.x; ++i) {
            for (int j=0; j<size.y; ++j) {
                int tileNumber;

             // assigning an appropriate tile number to a given cell
                switch (grid[i][j]) {
             // chasm
                case CHASM: tileNumber = 0 ; break;
             // wall
                case WALL:
                    tileNumber = rand()%14+2;
                    enum Neighbour {
                        NONE,
                        TOP, BOTTOM, LEFT, RIGHT,
                        TOP_BOTTOM, TOP_LEFT, TOP_RIGHT, LEFT_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                        NO_TOP, NO_RIGHT, NO_LEFT, NO_BOTTOM,
                        ALL
                    };
                    if (!isOnBorder(i, j)) {
                        if ((grid[i-1][j] != WALL) && (grid[i+1][j] != WALL) && (grid[i][j-1] != WALL) && (grid[i][j+1] != WALL))
                            tileNumber += Neighbour::ALL*16;

                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_TOP*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_BOTTOM*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_LEFT*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::NO_RIGHT*16;

                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::LEFT_RIGHT*16;
                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_LEFT*16;

                        else if ((grid[i][j-1] != WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP*16;
                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] != WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] != WALL) && (grid[i+1][j] == WALL))
                            tileNumber += Neighbour::LEFT*16;
                        else if ((grid[i][j-1] == WALL) && (grid[i][j+1] == WALL) && (grid[i-1][j] == WALL) && (grid[i+1][j] != WALL))
                            tileNumber += Neighbour::RIGHT*16;
                    } else if (i == 0) {
                        if (j > 0 && j < size.y-1) {
                            if ((grid[i+1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((grid[i+1][j] == WALL))
                                tileNumber += Neighbour::LEFT*16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_LEFT*16;
                        }
                        else if (j == size.y-1) {
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        }
                    } else if (i == size.x-1) {
                        if (j > 0 && j < size.y-1) {
                            if ((grid[i-1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((grid[i-1][j] == WALL))
                                tileNumber += Neighbour::RIGHT*16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        }
                        else if (j == size.y-1) {
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        }
                    } else if (j == 0 && i > 0 && i < size.x-1) {
                        if ((grid[i][j+1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((grid[i][j+1] == WALL))
                            tileNumber += Neighbour::TOP*16;
                    } else if (j == size.y-1 && i > 0 && i < size.x-1) {
                        if ((grid[i][j-1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((grid[i][j-1] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                    }
                    break;
             // ROOM
                case ROOM:     tileNumber = 1; break;
                case CORRIDOR: tileNumber = 17; break;
                case OCCUPIED: tileNumber = 48; break;
                case ENTRANCE: tileNumber = 64; break;
                }

                int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                sf::Vertex* quad = &m_vertices[(i+j*size.x)*4];

                quad[0].position = sf::Vector2f(  i  *80,   j  *80);
                quad[1].position = sf::Vector2f((i+1)*80,   j  *80);
                quad[2].position = sf::Vector2f((i+1)*80, (j+1)*80);
                quad[3].position = sf::Vector2f(  i  *80, (j+1)*80);

                quad[0].texCoords = sf::Vector2f(  tu  *16+0.0625f,   tv  *16+0.0625f);
                quad[1].texCoords = sf::Vector2f((tu+1)*16-0.0625f,   tv  *16+0.0625f);
                quad[2].texCoords = sf::Vector2f((tu+1)*16-0.0625f, (tv+1)*16-0.0625f);
                quad[3].texCoords = sf::Vector2f(  tu  *16+0.0625f, (tv+1)*16-0.0625f);
            }
        }
    }

    void Level::placeEntities() {
    // here we place the starting point
        for (int x=rand()%size.x, y=size.y; ; x=rand()%size.x, y=rand()%size.y) {
            if (grid[x][y] == ROOM) {
                startingPoint = sf::Vector2f(x*80, y*80);
                grid[x][y] = OCCUPIED;
                break;
            }
        }
    // here we place the ending point
        for (int x=rand()%size.x, y=size.y; ; x=rand()%size.x, y=rand()%size.y) {
            if (grid[x][y] == ROOM && grid[x][y] != OCCUPIED) {
                endingPoint = sf::Vector2f(x*80, y*80);
                grid[x][y] = OCCUPIED;
                break;
            }
        }
    // here we generate the items
        for (int i=0; i<rand()%10; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                // now we use the cell's color to distinguish which type of tile is in a randomised cell
                // - if the cell is green (ROOM) and not cyan (occupied) then you can place an item on it
                if (grid[x][y] == ROOM && grid[x][y] != OCCUPIED) {
                    addEntity(getItemFromID(100 + (rand()%3)*10 + rand()%9, 1), sf::Vector2f(x*80, y*80));
                    grid[x][y] = OCCUPIED; // cyan means that the cell is occupied by an object
                    break;
                }
            }
        }
    // here we generate the chests
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                // just doing the same checking as in the item generating section
                if (grid[x][y] == ROOM && grid[x][y] != OCCUPIED) {
                    // here we choose randomly whether the chest has to be the special (probability = 5%) or the regular one (p = 95%)
                    addEntity(new Chest((rand()%20)?Chest::REGULAR:Chest::SPECIAL,
                                        getItemFromID(100+(rand()%3)*10+rand()%9, 1)), sf::Vector2f(x*80, y*80));
                    grid[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    // here we generate the cash
        for (int i=0; i<rand()%15; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                // same story here
                if (grid[x][y] == ROOM && grid[x][y] != OCCUPIED) {
                    // here we choose randomly the type of a coin
                    addEntity(getItemFromID(rand()%3+1, rand()%100), sf::Vector2f(x*80, y*80));
                    grid[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    }

    void Level::addEntity(Entity* e, sf::Vector2f position) {
        if (e != nullptr) {
            entities.push_back(e);
            entities.back()->setPosition(position);
        }
    }

    bool Level::isOnBorder(int x, int y) {
        return x <= 0 || y <= 0 || x >= size.x-1 || y >= size.y-1;
    }

}
