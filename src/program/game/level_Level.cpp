/**
 * @file src/program/game/level_Level.cpp
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
        _size = sf::Vector2i(77, 43);
        _tilemap.setPrimitiveType(sf::Quads);
        _tilemap.resize(_size.x*_size.y*4);

        for (int i=0; i<_size.x; i++)
            _tiles.push_back(std::vector<Cell>());

        for (int i=0; i<_size.x; i++) {
            _regions.push_back(std::vector<int>());
            for (int j=0; j<_size.y; j++) {
                _regions[i].push_back(-1);
            }
        }
        _region_count = 0;
    }

    Level::~Level() {
        _entities.clear();
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(_tilemap, states);
    }

    void Level::drawObjects(sf::RenderWindow& rw) const {
        for (auto x : _entities)
            x->draw(rw);
    }

    bool Level::loadFromFile(const char*) {
        return true;
    }

    void Level::generateWorld() {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i=0; i<_size.x; i++)
            for (int j=0; j<_size.y; j++)
                _tiles[i].push_back(WALL);

     // at this point we generate some _rooms to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the _rooms
        for (int i=1; i<_size.x; i+=2) {
            for (int j=1; j<_size.y; j+=2) {
                if (_tiles[i][j] == WALL) {
                    fillWithMaze(i, j);
                    _region_count++;
                }
            }
        }

     // after that we generate the entrances between the _rooms and corridors
        connectRooms();

     // and then we can get rid of the dead ends of the corridors
        removeDeadEnds();

     // here we generate the _entities
        placeEntities();

     // in the end we generate the tile map from the created array
        generateTileMap();
    }

    void Level::digRooms() {
        for (int i=0; i<100; i++) {
            sf::Vector2i r_size((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((_size.x-r_size.x)/2)*2+1, rand()%((_size.y-r_size.y)/2)*2+1);

            bool intersects = false;
            for (int i=rpos.x; i<rpos.x+r_size.x; i++) {
                if (_tiles[i][rpos.y-1] == ROOM || _tiles[i][rpos.y+r_size.y+1] == ROOM) {
                    intersects = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+r_size.y && !intersects; i++) {
                if (_tiles[rpos.x-1][i] == ROOM || _tiles[rpos.x+r_size.x][i] == ROOM) {
                    intersects = true;
                    break;
                }
            }

            if (intersects)
                continue;

            for (int i=rpos.x; i<rpos.x+r_size.x; i++) {
                for (int j=rpos.y; j<rpos.y+r_size.y; j++) {
                    _tiles[i][j] = ROOM;
                    _regions[i][j] = _region_count;
                }
            }

            _rooms.push_back(sf::IntRect(rpos, r_size));
            _region_count++;
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
                if (_tiles[r-2][c] == WALL) {
                    _tiles[r-2][c] = CORRIDOR;
                    _tiles[r-1][c] = CORRIDOR;
                    _regions[r-2][c] = _region_count;
                    _regions[r-1][c] = _region_count;
                    fillWithMaze(r-2, c);
                }
                break;
            case 1: // RIGHT
                if (c+2 >= _size.y-1)
                    continue;
                if (_tiles[r][c+2] == WALL) {
                    _tiles[r][c+2] = CORRIDOR;
                    _tiles[r][c+1] = CORRIDOR;
                    _regions[r][c+2] = _region_count;
                    _regions[r][c+1] = _region_count;
                    fillWithMaze(r, c+2);
                }
                break;
            case 2: // DOWN
                if (r+2 >= _size.x-1)
                    continue;
                if (_tiles[r+2][c] == WALL) {
                    _tiles[r+2][c] = CORRIDOR;
                    _tiles[r+1][c] = CORRIDOR;
                    _regions[r+2][c] = _region_count;
                    _regions[r+1][c] = _region_count;
                    fillWithMaze(r+2, c);
                }
                break;
            case 3: // LEFT
                if (c-2 <= 0)
                    continue;
                if (_tiles[r][c-2] == WALL) {
                    _tiles[r][c-2] = CORRIDOR;
                    _tiles[r][c-1] = CORRIDOR;
                    _regions[r][c-2] = _region_count;
                    _regions[r][c-1] = _region_count;
                    fillWithMaze(r, c-2);
                }
                break;
            }
        }
    }

    void Level::connectRooms() {
     // a container of _tiles which can connect two _regions
        std::vector<sf::Vector2i> connectors;

     // we have to place the conectors on every tile on whose two opposite sides is no wall
        for (sf::Vector2i pos(1, 1); pos.x<_size.x-1 && pos.y<_size.y-1; pos += ((pos.x >= _size.x-2)?(sf::Vector2i(-(_size.x-3), 1)):(sf::Vector2i(1, 0)))) {
         // we cannot place a connector on a tile which is not a wall
            if (_tiles[pos.x][pos.y] == WALL) {
                if (_regions[pos.x-1][pos.y] != -1 && _regions[pos.x+1][pos.y] != -1) {
                 // are there walls neither on the right nor on the left?
                    if (_tiles[pos.x-1][pos.y] == CORRIDOR || _tiles[pos.x+1][pos.y] == CORRIDOR) {
                     // the _regions on both sides cannot be the same if one of them is a corridor
                        if (_regions[pos.x-1][pos.y] != _regions[pos.x+1][pos.y])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }
             // are there walls neither above nor below?
                else if (_regions[pos.x][pos.y-1] != -1 && _regions[pos.x][pos.y+1] != -1) {
                    if (_tiles[pos.x][pos.y-1] == CORRIDOR || _tiles[pos.x][pos.y+1] == CORRIDOR) {
                     // the _regions on both sides cannot be the same if one of them is a corridor
                        if (_regions[pos.x][pos.y-1] != _regions[pos.x][pos.y+1])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }
            }
        }

     // then we iterate on each room and give it a random numbers of entrances
        for (unsigned it=0; it<_rooms.size(); it++) {
            for (int entrances = rand()%3+2; entrances>0; entrances--) {
                sf::Vector2i position;
                bool found = false;

                int tries = 50;
                while (!found && tries > 0) {
                    switch (rand()%2) {
                    case 0: // LEFT OR RIGHT
                        position = (rand()%2)?sf::Vector2i(_rooms[it].left-1               , _rooms[it].top+rand()%_rooms[it].height)
                                             :sf::Vector2i(_rooms[it].left+_rooms[it].width, _rooms[it].top+rand()%_rooms[it].height);
                        break;
                    case 1: // UP OR DOWN
                        position = (rand()%2)?sf::Vector2i(_rooms[it].left+rand()%_rooms[it].width, _rooms[it].top-1)
                                             :sf::Vector2i(_rooms[it].left+rand()%_rooms[it].width, _rooms[it].top+_rooms[it].height);
                        break;
                    }

                    for (auto x : connectors) {
                        if (x == position) {
                            found = true;
                            _tiles[position.x][position.y] = ENTRANCE;
                            break;
                        }
                    }
                    tries--;
                }
            }
        }

     // after that we check if there appear any doors placed next to each other
     // if so-then we delete one of them
        for (sf::Vector2i pos(1, 1); pos.x<_size.x-1 && pos.y<_size.y-1; pos += ((pos.x >= _size.x-2)?(sf::Vector2i(-(_size.x-3), 1)):(sf::Vector2i(1, 0)))) {
            if (_tiles[pos.x][pos.y] == ENTRANCE) {
                if (_tiles[pos.x-1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        _tiles[pos.x][pos.y]   = WALL;
                    else
                        _tiles[pos.x-1][pos.y] = WALL;
                }
                if (_tiles[pos.x+1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        _tiles[pos.x][pos.y]   = WALL;
                    else
                        _tiles[pos.x+1][pos.y] = WALL;
                }
                if (_tiles[pos.x][pos.y-1] == ENTRANCE) {
                    if (rand()%2)
                        _tiles[pos.x][pos.y]   = WALL;
                    else
                        _tiles[pos.x][pos.y-1] = WALL;
                }
                if (_tiles[pos.x][pos.y+1] == ENTRANCE) {
                    if (rand()%2)
                        _tiles[pos.x][pos.y]   = WALL;
                    else
                        _tiles[pos.x][pos.y+1] = WALL;
                }
            }
        }
    }

    void Level::removeDeadEnds() {
        bool done = false;

        while (!done) {
            done = true;
            for (int i=1; i<_size.x-1; i++) {
                for (int j=1; j<_size.y-1; j++) {
                    if (_tiles[i][j] == WALL)
                        continue;

                    // if it only has one exit, it's a dead end.
                    int exits = 0;
                    if (_tiles[i-1][j] != WALL)
                        exits++;
                    if (_tiles[i+1][j] != WALL)
                        exits++;
                    if (_tiles[i][j-1] != WALL)
                        exits++;
                    if (_tiles[i][j+1] != WALL)
                        exits++;

                    if (exits > 1)
                        continue;

                    done = false;
                    _tiles[i][j] = WALL;
                }
            }
        }
    }

    void Level::generateTileMap() {
        for (int i=0; i<_size.x; ++i) {
            for (int j=0; j<_size.y; ++j) {
                int tileNumber;

             // assigning an appropriate tile number to a given cell
                switch (_tiles[i][j]) {
                case CHASM: tileNumber = 0; break;
                case WALL :
                    tileNumber = rand()%14+2;
                    enum Neighbour {
                        NONE,
                        TOP, BOTTOM, LEFT, RIGHT,
                        TOP_BOTTOM, TOP_LEFT, TOP_RIGHT, LEFT_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                        NO_TOP, NO_RIGHT, NO_LEFT, NO_BOTTOM,
                        ALL
                    };
                    if (!isOnBorder(i, j)) {
                        if ((_tiles[i-1][j] != WALL) && (_tiles[i+1][j] != WALL) && (_tiles[i][j-1] != WALL) && (_tiles[i][j+1] != WALL))
                            tileNumber += Neighbour::ALL*16;

                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_TOP*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_BOTTOM*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::NO_LEFT*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::NO_RIGHT*16;

                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::LEFT_RIGHT*16;
                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP_LEFT*16;

                        else if ((_tiles[i][j-1] != WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::TOP*16;
                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] != WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] != WALL) && (_tiles[i+1][j] == WALL))
                            tileNumber += Neighbour::LEFT*16;
                        else if ((_tiles[i][j-1] == WALL) && (_tiles[i][j+1] == WALL) && (_tiles[i-1][j] == WALL) && (_tiles[i+1][j] != WALL))
                            tileNumber += Neighbour::RIGHT*16;
                    } else if (i == 0) {
                        if (j > 0 && j < _size.y-1) {
                            if ((_tiles[i+1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((_tiles[i+1][j] == WALL))
                                tileNumber += Neighbour::LEFT*16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_LEFT*16;
                        }
                        else if (j == _size.y-1) {
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        }
                    } else if (i == _size.x-1) {
                        if (j > 0 && j < _size.y-1) {
                            if ((_tiles[i-1][j] != WALL))
                                tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((_tiles[i-1][j] == WALL))
                                tileNumber += Neighbour::RIGHT*16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        }
                        else if (j == _size.y-1) {
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        }
                    } else if (j == 0 && i > 0 && i < _size.x-1) {
                        if ((_tiles[i][j+1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((_tiles[i][j+1] == WALL))
                            tileNumber += Neighbour::TOP*16;
                    } else if (j == _size.y-1 && i > 0 && i < _size.x-1) {
                        if ((_tiles[i][j-1] != WALL))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((_tiles[i][j-1] == WALL))
                            tileNumber += Neighbour::BOTTOM*16;
                    }
                    break;
             // ROOM
                case ROOM:     tileNumber = 17; break;
                case CORRIDOR: tileNumber = 1;  break;
                case OCCUPIED: tileNumber = 48; break;
                case ENTRANCE: tileNumber = 17; break;
                }

                int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                sf::Vertex* quad = &_tilemap[(i+j*_size.x)*4];

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
        for (int x=1; x<_size.x-1; x++) {
            for (int y=1; y<_size.y-1; y++) {
                if (_tiles[x][y] == ENTRANCE)
                    addEntity(new Door(false), sf::Vector2i(x, y));
            }
        }
     // here we place the starting point
        for (int x=rand()%_size.x, y=_size.y; ; x=rand()%_size.x, y=rand()%_size.y) {
            if (_tiles[x][y] == ROOM) {
                _startingPoint = sf::Vector2i(x, y);
                _tiles[x][y] = OCCUPIED;
                break;
            }
        }
     // here we place the ending point
        for (int x=rand()%_size.x, y=_size.y; ; x=rand()%_size.x, y=rand()%_size.y) {
            if (_tiles[x][y] == ROOM && _tiles[x][y] != OCCUPIED && (abs(x-_startingPoint.x) > 30 || abs(y-_startingPoint.y) > 30)) {
                _endingPoint = sf::Vector2i(x, y);
                _tiles[x][y] = OCCUPIED;
                break;
            }
        }
     // here we generate the items
        for (int i=0; i<rand()%10; i++) {
            while (true) {
                int x=rand()%_size.x, y=rand()%_size.y;
                if (_tiles[x][y] == ROOM && _tiles[x][y] != OCCUPIED) {
                    addEntity(getItemFromID(100+(rand()%3)*10+rand()%9, 1), sf::Vector2i(x, y));
                    _tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
     // here we generate the chests
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%_size.x, y=rand()%_size.y;
                // just doing the same checking as in the item generating section
                if (_tiles[x][y] == ROOM && _tiles[x][y] != OCCUPIED) {
                    // here we choose randomly whether the chest has to be the special (probability = 5%) or the regular one (p = 95%)
                    addEntity(new Chest((rand()%20) ? Chest::REGULAR : Chest::SPECIAL,
                                        getItemFromID(100+(rand()%3)*10+rand()%9, 1)), sf::Vector2i(x, y));
                    _tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
     // here we generate the Coin
        for (int i=0; i<rand()%15; i++) {
            while (true) {
                int x=rand()%_size.x, y=rand()%_size.y;
                // same story here
                if (_tiles[x][y] == ROOM && _tiles[x][y] != OCCUPIED) {
                    // here we choose randomly the type of a coin
                    addEntity(getItemFromID(rand()%6+1, rand()%100), sf::Vector2i(x, y));
                    _tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
     // here we generate the books
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%_size.x, y=rand()%_size.y;
                if (_tiles[x][y] == ROOM && _tiles[x][y] != OCCUPIED) {
                    // here we choose randomly the type of a coin
                    addEntity(getItemFromID(rand()%3+10, 1), sf::Vector2i(x, y));
                    _tiles[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    }

    void Level::addEntity(Entity* e, sf::Vector2i position) {
        if (e != nullptr) {
            _entities.push_back(e);
            _entities.back()->setPosition(position);
        }
    }

    bool Level::isOnBorder(int x, int y) {
        return x <= 0 || y <= 0 || x >= _size.x-1 || y >= _size.y-1;
    }

}
