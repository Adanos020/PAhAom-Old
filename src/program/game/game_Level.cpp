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

#include <list>

extern rr::Resources resources;

namespace rr {

    Level::Level() {
        size = sf::Vector2i(77, 43);
        tilemap.setPrimitiveType(sf::Quads);
        tilemap.resize(size.x*size.y*4);

        for (int i=0; i<size.x; i++)
            tiles.push_back(std::vector<Cell>());

        for (int i=0; i<size.x; i++) {
            regions.push_back(std::vector<int>());
            for (int j=0; j<size.y; j++) {
                regions[i].push_back(-1);
            }
        }
        region_count = 0;
    }

    Level::~Level() {
        entities.clear();
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(tilemap, states);
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
                tiles[i].push_back(WALL);

     // at this point we generate some rooms to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the rooms
        for (int i=1; i<size.x; i+=2) {
            for (int j=1; j<size.y; j+=2) {
                if (tiles[i][j] == WALL) {
                    fillWithMaze(i, j);
                    region_count++;
                }
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

            bool intersects = false;
            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                if (tiles[i][rpos.y-1] == ROOM || tiles[i][rpos.y+rsize.y+1] == ROOM) {
                    intersects = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+rsize.y && !intersects; i++) {
                if (tiles[rpos.x-1][i] == ROOM || tiles[rpos.x+rsize.x][i] == ROOM) {
                    intersects = true;
                    break;
                }
            }

            if (intersects)
                continue;

            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                for (int j=rpos.y; j<rpos.y+rsize.y; j++) {
                    tiles[i][j] = ROOM;
                    regions[i][j] = region_count;
                }
            }

            rooms.push_back(sf::IntRect(rpos, rsize));
            region_count++;
        }
    }

    void Level::fillWithMaze(int r, int c) {
 // at this point we generate an array of random directions
        int number = rand()%100+100;
        int* directions = new int[number];
        for (int i=0; i<number; i++) {
            directions[i] = rand()%4;
        }
     // and now let's start digging
        for (int i = 0; i<number; i++) {
            switch(directions[i]) {
            case 0: // UP
                if (r-2 <= 0)
                    continue;
                if (tiles[r-2][c] == WALL) {
                    tiles[r-2][c] = CORRIDOR;
                    tiles[r-1][c] = CORRIDOR;
                    regions[r-2][c] = region_count;
                    regions[r-1][c] = region_count;
                    fillWithMaze(r-2, c);
                }
                break;
            case 1: // RIGHT
                if (c+2 >= size.y-1)
                    continue;
                if (tiles[r][c+2] == WALL) {
                    tiles[r][c+2] = CORRIDOR;
                    tiles[r][c+1] = CORRIDOR;
                    regions[r][c+2] = region_count;
                    regions[r][c+1] = region_count;
                    fillWithMaze(r, c+2);
                }
                break;
            case 2: // DOWN
                if (r+2 >= size.x-1)
                    continue;
                if (tiles[r+2][c] == WALL) {
                    tiles[r+2][c] = CORRIDOR;
                    tiles[r+1][c] = CORRIDOR;
                    regions[r+2][c] = region_count;
                    regions[r+1][c] = region_count;
                    fillWithMaze(r+2, c);
                }
                break;
            case 3: // LEFT
                if (c-2 <= 0)
                    continue;
                if (tiles[r][c-2] == WALL) {
                    tiles[r][c-2] = CORRIDOR;
                    tiles[r][c-1] = CORRIDOR;
                    regions[r][c-2] = region_count;
                    regions[r][c-1] = region_count;
                    fillWithMaze(r, c-2);
                }
                break;
            }
        }
    }

    void Level::connectRooms() {
     // a container of tiles which can connect two regions
        std::vector<sf::Vector2i> connectors;

     // we have to place the conectors on every tile on whose two opposite sides is no wall
        for (sf::Vector2i pos(1, 1); pos.x<size.x-1 && pos.y<size.y-1; pos += ((pos.x >= size.x-2)?(sf::Vector2i(-(size.x-3), 1)):(sf::Vector2i(1, 0)))) {
         // we cannot place a connector on a tile which is not a wall
            if (tiles[pos.x][pos.y] == WALL) {
                if (regions[pos.x-1][pos.y] != -1 && regions[pos.x+1][pos.y] != -1) {
                 // are there walls neither on the right nor on the left?
                    if (tiles[pos.x-1][pos.y] == CORRIDOR || tiles[pos.x+1][pos.y] == CORRIDOR) {
                     // the regions on both sides cannot be the same if one of them is a corridor
                        if (regions[pos.x-1][pos.y] != regions[pos.x+1][pos.y])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }
             // are there walls neither above nor below?
                else if (regions[pos.x][pos.y-1] != -1 && regions[pos.x][pos.y+1] != -1) {
                    if (tiles[pos.x][pos.y-1] == CORRIDOR || tiles[pos.x][pos.y+1] == CORRIDOR) {
                     // the regions on both sides cannot be the same if one of them is a corridor
                        if (regions[pos.x][pos.y-1] != regions[pos.x][pos.y+1])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }
            }
        }

     // then we iterate on each room and give it a random numbers of entrances
        for (unsigned it=0; it<rooms.size(); it++) {
            for (int entrances = rand()%((rooms[it].width<rooms[it].height)?rooms[it].width:rooms[it].height)/2+1; entrances>0; entrances--) {
                sf::Vector2i position;
                bool found = false;

                int tries = 50;
                while (!found && tries > 0) {
                    switch (rand()%2) {
                    case 0: // LEFT OR RIGHT
                        position = (rand()%2)?sf::Vector2i(rooms[it].left                  , rooms[it].top + rand()%rooms[it].height)
                                             :sf::Vector2i(rooms[it].left + rooms[it].width, rooms[it].top + rand()%rooms[it].height);
                        break;
                    case 1: // UP OR DOWN
                        position = (rand()%2)?sf::Vector2i(rooms[it].left + rand()%rooms[it].width, rooms[it].top - 1)
                                             :sf::Vector2i(rooms[it].left + rand()%rooms[it].width, rooms[it].top + rooms[it].height);
                        break;
                    }

                    for (auto x : connectors) {
                        if (x == position) {
                            found = true;
                            tiles[position.x][position.y] = ENTRANCE;
                            break;
                        }
                    }
                    tries--;
                }
            }
        }

     // after that we check if there appear any doors placed next to each other
     // if so - then we delete one of them
        for (sf::Vector2i pos(1, 1); pos.x<size.x-1 && pos.y<size.y-1; pos += ((pos.x >= size.x-2)?(sf::Vector2i(-(size.x-3), 1)):(sf::Vector2i(1, 0)))) {
            if (tiles[pos.x][pos.y] == ENTRANCE) {
                if (tiles[pos.x-1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        tiles[pos.x][pos.y] = WALL;
                    else
                        tiles[pos.x-1][pos.y] = WALL;
                }
                if (tiles[pos.x+1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        tiles[pos.x][pos.y] = WALL;
                    else
                        tiles[pos.x+1][pos.y] = WALL;
                }
                if (tiles[pos.x][pos.y-1] == ENTRANCE) {
                    if (rand()%2)
                        tiles[pos.x][pos.y] = WALL;
                    else
                        tiles[pos.x][pos.y-1] = WALL;
                }
                if (tiles[pos.x][pos.y+1] == ENTRANCE) {
                    if (rand()%2)
                        tiles[pos.x][pos.y] = WALL;
                    else
                        tiles[pos.x][pos.y+1] = WALL;
                }
            }
        }
    }

    void Level::removeDeadEnds() {
        bool done = false;

        while (!done) {
            done = true;
            for (int i=1; i<size.x-1; i++) {
                for (int j=1; j<size.y-1; j++) {
                    if (tiles[i][j] == WALL)
                        continue;

                    // if it only has one exit, it's a dead end.
                    int exits = 0;
                    if (tiles[i-1][j] != WALL)
                        exits++;
                    if (tiles[i+1][j] != WALL)
                        exits++;
                    if (tiles[i][j-1] != WALL)
                        exits++;
                    if (tiles[i][j+1] != WALL)
                        exits++;

                    if (exits > 1)
                        continue;

                    done = false;
                    tiles[i][j] = WALL;
                }
            }
        }
    }

    void Level::generateTileMap() {
        for (int i=0; i<size.x; ++i) {
            for (int j=0; j<size.y; ++j) {
                int tileNumber;

             // assigning an appropriate tile number to a given cell
                switch (tiles[i][j]) {
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
                        if ((tiles[i-1][j] != WALL) && (tiles[i+1][j] != WALL) && (tiles[i][j-1] != WALL) && (tiles[i][j+1] != WALL))
                            tileNumber += Neighbour::ALL*16;

                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_TOP*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_BOTTOM*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_LEFT*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::NO_RIGHT*16;

                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::LEFT_RIGHT*16;
                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_LEFT*16;

                        else if ((tiles[i][j-1] != WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP*16;
                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] != WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] != WALL) && (tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::LEFT*16;
                        else if ((tiles[i][j-1] == WALL) && (tiles[i][j+1] == WALL) && (tiles[i-1][j] == WALL) && (tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::RIGHT*16;
                    } else if (i == 0) {
                        if (j > 0 && j < size.y-1) {
                            if ((tiles[i+1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((tiles[i+1][j] == WALL))
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
                            if ((tiles[i-1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((tiles[i-1][j] == WALL))
                                tileNumber += Neighbour::RIGHT*16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        }
                        else if (j == size.y-1) {
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        }
                    } else if (j == 0 && i > 0 && i < size.x-1) {
                        if ((tiles[i][j+1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((tiles[i][j+1] == WALL))
                            tileNumber += Neighbour::TOP*16;
                    } else if (j == size.y-1 && i > 0 && i < size.x-1) {
                        if ((tiles[i][j-1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((tiles[i][j-1] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                    }
                    break;
             // ROOM
                case ROOM:     tileNumber = 17;  break;
                case CORRIDOR: tileNumber = 1;  break;
                case OCCUPIED: tileNumber = 48; break;
                case ENTRANCE: tileNumber = 1;  break;
                }

                int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                sf::Vertex* quad = &tilemap[(i+j*size.x)*4];

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
    // here we place the doors
        for (int x=1; x<size.x-1; x++) {
            for (int y=1; y<size.y-1; y++) {
                if (tiles[x][y] == ENTRANCE)
                    addEntity(new Door(false), sf::Vector2f(x*80, y*80));
            }
        }
    // here we place the starting point
        for (int x=rand()%size.x, y=size.y; ; x=rand()%size.x, y=rand()%size.y) {
            if (tiles[x][y] == ROOM) {
                startingPoint = sf::Vector2f(x*80, y*80);
                tiles[x][y] = OCCUPIED;
                break;
            }
        }
    // here we place the ending point
        for (int x=rand()%size.x, y=size.y; ; x=rand()%size.x, y=rand()%size.y) {
            if (tiles[x][y] == ROOM && tiles[x][y] != OCCUPIED) {
                endingPoint = sf::Vector2f(x*80, y*80);
                tiles[x][y] = OCCUPIED;
                break;
            }
        }
    // here we generate the items
        for (int i=0; i<rand()%10; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                if (tiles[x][y] == ROOM && tiles[x][y] != OCCUPIED) {
                    addEntity(getItemFromID(100 + (rand()%3)*10 + rand()%9, 1), sf::Vector2f(x*80, y*80));
                    tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    // here we generate the chests
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                // just doing the same checking as in the item generating section
                if (tiles[x][y] == ROOM && tiles[x][y] != OCCUPIED) {
                    // here we choose randomly whether the chest has to be the special (probability = 5%) or the regular one (p = 95%)
                    addEntity(new Chest((rand()%20)?Chest::REGULAR:Chest::SPECIAL,
                                        getItemFromID(100+(rand()%3)*10+rand()%9, 1)), sf::Vector2f(x*80, y*80));
                    tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    // here we generate the cash
        for (int i=0; i<rand()%15; i++) {
            while (true) {
                int x=rand()%size.x, y=rand()%size.y;
                // same story here
                if (tiles[x][y] == ROOM && tiles[x][y] != OCCUPIED) {
                    // here we choose randomly the type of a coin
                    addEntity(getItemFromID(rand()%3+1, rand()%100), sf::Vector2f(x*80, y*80));
                    tiles[x][y] = OCCUPIED;
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
