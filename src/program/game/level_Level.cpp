/**
 * @file src/program/game/level_Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "game.hpp"
#include "../program.hpp"
#include "entities/entities.hpp"
#include "../funcs/files.hpp"
#include "../funcs/items.hpp"

extern rr::Resources resources;

namespace rr {

    Level::Level(int number)
        : size_         (sf::Vector2i(77, 43)),
          region_count_ (0),
          levelNumber_  (number) {

        tilemap_.setPrimitiveType(sf::Quads);
        tilemap_.resize(size_.x*size_.y*4);

        for (int i=0; i<size_.x; i++)
            tiles_.push_back(std::vector<Cell>());
        for (int i=0; i<size_.x; i++) {
            regions_.push_back(std::vector<int>());
            masks_.push_back(std::vector<Mask*>());
            for (int j=0; j<size_.y; j++) {
                regions_[i].push_back(-1);
                masks_[i].push_back(new Mask());
            }
        }
    }

    Level::~Level() {
        for (auto entity : entities_) {
            delete entity;
        }
        entities_.clear();
        for (auto x : masks_)
            for (auto mask : x)
                delete mask;
        masks_.clear();
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(tilemap_, states);
    }

    bool Level::loadFromFile(const char*) {
        return true;
    }

    void Level::drawObjects(sf::RenderWindow& rw) const {
        for (auto x : entities_) {
            x->draw(rw);
        }
        for (auto x : masks_) {
            for (auto mask : x) {
                mask->draw(rw);
            }
        }
    }

    void Level::addEntity(Entity* e, sf::Vector2i position) {
        if (e != nullptr) {
            entities_.push_back(e);
            entities_.back()->setPosition(position);
        }
    }

    void Level::removeEntity(unsigned index) {
        delete entities_[index];
        entities_.erase(entities_.begin()+index);
    }

    void Level::generateWorld() {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i=0; i<size_.x; i++)
            for (int j=0; j<size_.y; j++)
                tiles_[i].push_back(WALL);

     // at this point we generate some rooms_ to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the rooms_
        for (int i=1; i<size_.x; i+=2) {
            for (int j=1; j<size_.y; j+=2) {
                if (tiles_[i][j] == WALL) {
                    fillWithMaze(i, j);
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

     // and just transform the table of Cells to a table of ints
        for (int i=0; i<size_.x; i++) {
            tilesAsInts_.push_back(std::vector<int>());
            for (int j=0; j<size_.y; j++) {
                tilesAsInts_[i].push_back(tiles_[i][j]);
            }
        }
    }

    void Level::digRooms() {
        for (int i=0; i<100; i++) {
            sf::Vector2i rsize((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((size_.x-rsize.x)/2)*2+1, rand()%((size_.y-rsize.y)/2)*2+1);

            bool intersects = false;
            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                if (tiles_[i][rpos.y-1] == ROOM || tiles_[i][rpos.y+rsize.y+1] == ROOM) {
                    intersects = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+rsize.y && !intersects; i++) {
                if (tiles_[rpos.x-1][i] == ROOM || tiles_[rpos.x+rsize.x][i] == ROOM) {
                    intersects = true;
                    break;
                }
            }

            if (!intersects) {
                for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                    for (int j=rpos.y; j<rpos.y+rsize.y; j++) {
                        tiles_[i][j] = ROOM;
                        regions_[i][j] = region_count_;
                    }
                }

                rooms_.push_back(sf::IntRect(rpos, rsize));
                region_count_++;
            }
        }
    }

    void Level::fillWithMaze(int r, int c) {
        region_count_++;

        tiles_  [r][c] = CORRIDOR;
        regions_[r][c] = region_count_;

        std::vector<sf::Vector2i> cells;
        cells.push_back(sf::Vector2i(r, c));

        sf::Vector2i lastDir = sf::Vector2i(0, 0);

        std::vector<sf::Vector2i> directions;
        directions.push_back(sf::Vector2i(-1,  0));
        directions.push_back(sf::Vector2i( 0, -1));
        directions.push_back(sf::Vector2i( 1,  0));
        directions.push_back(sf::Vector2i( 0,  1));

        while (!cells.empty()) {
            sf::Vector2i cell = cells.back();

            std::vector<sf::Vector2i> unmadeCells;

            for (auto dir : directions) {
                if (!isOnBorder(cell.x+dir.x*3, cell.y+dir.y*3) && tiles_[cell.x+dir.x*2][cell.y+dir.y*2] == WALL)
                    unmadeCells.push_back(dir);
            }

            if (!unmadeCells.empty()) {
                sf::Vector2i dir;

                bool found = false;
                for (auto x : unmadeCells) {
                    if (x == lastDir) {
                        found = true;
                        break;
                    }
                }
                if (found && rand()%100 > 0) {
                    dir = lastDir;
                }
                else {
                    dir = unmadeCells[rand()%unmadeCells.size()];
                }

                tiles_[ cell.x+dir.x ][ cell.y+dir.y ] = CORRIDOR;
                tiles_[cell.x+dir.x*2][cell.y+dir.y*2] = CORRIDOR;

                regions_[ cell.x+dir.x ][ cell.y+dir.y ] = region_count_;
                regions_[cell.x+dir.x*2][cell.y+dir.y*2] = region_count_;

                cells.push_back(cell+dir*2);
                lastDir = dir;
            }
            else {
                cells.pop_back();
                lastDir = sf::Vector2i(0, 0);
            }
        }
    }

    void Level::connectRooms() {
     // a container of tiles_ which can connect two regions_
        std::vector<sf::Vector2i> connectors;

     // we have to place the conectors on every tile on whose two opposite sides is no wall
        for (sf::Vector2i pos(1, 1); pos.x<size_.x-1 && pos.y<size_.y-1; pos += ((pos.x >= size_.x-2)?(sf::Vector2i(-(size_.x-3), 1)):(sf::Vector2i(1, 0)))) {

         // we cannot place a connector on a tile which is not a wall
            if (tiles_[pos.x][pos.y] == WALL) {
                if (regions_[pos.x-1][pos.y] != -1 && regions_[pos.x+1][pos.y] != -1) {

                 // are there walls neither on the right nor on the left?
                    if (tiles_[pos.x-1][pos.y] == CORRIDOR || tiles_[pos.x+1][pos.y] == CORRIDOR) {

                     // the regions_ on both sides cannot be the same if one of them is a corridor
                        if (regions_[pos.x-1][pos.y] != regions_[pos.x+1][pos.y])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }

             // are there walls neither above nor below?
                else if (regions_[pos.x][pos.y-1] != -1 && regions_[pos.x][pos.y+1] != -1) {
                    if (tiles_[pos.x][pos.y-1] == CORRIDOR || tiles_[pos.x][pos.y+1] == CORRIDOR) {

                     // the regions_ on both sides cannot be the same if one of them is a corridor
                        if (regions_[pos.x][pos.y-1] != regions_[pos.x][pos.y+1])
                            connectors.push_back(pos);
                    }
                    else
                        connectors.push_back(pos);
                }
            }
        }

     // then we iterate on each room and give it a random numbers of entrances
        for (unsigned it=0; it<rooms_.size(); it++) {
            for (int entrances = rand()%2+2; entrances>0; entrances--) {
                sf::Vector2i position;
                bool found = false;

                int tries = 100;
                while (!found && tries > 0) {
                    switch (rand()%2) {
                    case 0: // LEFT OR RIGHT
                        position = (rand()%2)?sf::Vector2i(rooms_[it].left-1               , rooms_[it].top+rand()%rooms_[it].height)
                                             :sf::Vector2i(rooms_[it].left+rooms_[it].width, rooms_[it].top+rand()%rooms_[it].height);
                        break;
                    case 1: // UP OR DOWN
                        position = (rand()%2)?sf::Vector2i(rooms_[it].left+rand()%rooms_[it].width, rooms_[it].top-1)
                                             :sf::Vector2i(rooms_[it].left+rand()%rooms_[it].width, rooms_[it].top+rooms_[it].height);
                        break;
                    }

                    for (auto x : connectors) {
                        if (x == position) {
                            found = true;
                            tiles_[position.x][position.y] = ENTRANCE;
                            break;
                        }
                    }
                    tries--;
                }
            }
        }

     // after that we check if there appear any doors placed next to each other
     // if so-then we delete one of them
        for (sf::Vector2i pos(1, 1); pos.x<size_.x-1 && pos.y<size_.y-1; pos += ((pos.x >= size_.x-2)?(sf::Vector2i(-(size_.x-3), 1)):(sf::Vector2i(1, 0)))) {
            if (tiles_[pos.x][pos.y] == ENTRANCE) {
                if (tiles_[pos.x-1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        tiles_[pos.x][pos.y]   = WALL;
                    else
                        tiles_[pos.x-1][pos.y] = WALL;
                }
                if (tiles_[pos.x+1][pos.y] == ENTRANCE) {
                    if (rand()%2)
                        tiles_[pos.x][pos.y]   = WALL;
                    else
                        tiles_[pos.x+1][pos.y] = WALL;
                }
                if (tiles_[pos.x][pos.y-1] == ENTRANCE) {
                    if (rand()%2)
                        tiles_[pos.x][pos.y]   = WALL;
                    else
                        tiles_[pos.x][pos.y-1] = WALL;
                }
                if (tiles_[pos.x][pos.y+1] == ENTRANCE) {
                    if (rand()%2)
                        tiles_[pos.x][pos.y]   = WALL;
                    else
                        tiles_[pos.x][pos.y+1] = WALL;
                }
            }
        }
    }

    void Level::removeDeadEnds() {
        bool done = false;

        while (!done) {
            done = true;
            for (int i=1; i<size_.x-1; i++) {
                for (int j=1; j<size_.y-1; j++) {
                    if (tiles_[i][j] == WALL)
                        continue;

                    // if it only has one exit, it's a dead end.
                    int exits = 0;
                    if (tiles_[i-1][j] != WALL)
                        exits++;
                    if (tiles_[i+1][j] != WALL)
                        exits++;
                    if (tiles_[i][j-1] != WALL)
                        exits++;
                    if (tiles_[i][j+1] != WALL)
                        exits++;

                    if (exits > 1)
                        continue;

                    done = false;
                    tiles_[i][j] = WALL;
                }
            }
        }
    }

    void Level::generateTileMap() {
        for (int i=0; i<size_.x; ++i) {
            for (int j=0; j<size_.y; ++j) {
                int tileNumber;

             // assigning an appropriate tile number to a given cell
                switch (tiles_[i][j]) {
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
                        if      ((tiles_[i-1][j] != WALL) && (tiles_[i+1][j] != WALL) && (tiles_[i][j-1] != WALL) && (tiles_[i][j+1] != WALL)) tileNumber += Neighbour::ALL         *16;

                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::NO_TOP      *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::NO_BOTTOM   *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::NO_LEFT     *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::NO_RIGHT    *16;

                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::LEFT_RIGHT  *16;
                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::BOTTOM_LEFT *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::TOP_BOTTOM  *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::TOP_RIGHT   *16;
                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::TOP_LEFT    *16;

                        else if ((tiles_[i][j-1] != WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::TOP         *16;
                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] != WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::BOTTOM      *16;
                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] != WALL) && (tiles_[i+1][j] == WALL)) tileNumber += Neighbour::LEFT        *16;
                        else if ((tiles_[i][j-1] == WALL) && (tiles_[i][j+1] == WALL) && (tiles_[i-1][j] == WALL) && (tiles_[i+1][j] != WALL)) tileNumber += Neighbour::RIGHT       *16;
                    } else if (i == 0) {
                        if (j > 0 && j < size_.y-1) {
                            if      ((tiles_[i+1][j] != WALL)) tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((tiles_[i+1][j] == WALL)) tileNumber += Neighbour::LEFT      *16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_LEFT   *16;
                        }
                        else if (j == size_.y-1) {
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        }
                    } else if (i == size_.x-1) {
                        if (j > 0 && j < size_.y-1) {
                            if      ((tiles_[i-1][j] != WALL)) tileNumber += Neighbour::LEFT_RIGHT*16;
                            else if ((tiles_[i-1][j] == WALL)) tileNumber += Neighbour::RIGHT     *16;
                        }
                        else if (j == 0) {
                            tileNumber += Neighbour::TOP_RIGHT   *16;
                        }
                        else if (j == size_.y-1) {
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        }
                    } else if (j == 0 && i > 0 && i < size_.x-1) {
                        if      ((tiles_[i][j+1] != WALL)) tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((tiles_[i][j+1] == WALL)) tileNumber += Neighbour::TOP       *16;
                    } else if (j == size_.y-1 && i > 0 && i < size_.x-1) {
                        if      ((tiles_[i][j-1] != WALL)) tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((tiles_[i][j-1] == WALL)) tileNumber += Neighbour::BOTTOM    *16;
                    }
                    break;
                case CORRIDOR: tileNumber = 1;  break;
                default:       tileNumber = 17; break;
                }

                int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                sf::Vertex* quad = &tilemap_[(i+j*size_.x)*4];

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
    /* OBJECTS */
     // here we place the doors
        for (int x=1; x<size_.x-1; x++) {
            for (int y=1; y<size_.y-1; y++) {
                if (tiles_[x][y] == ENTRANCE)
                    addEntity(new Door(false), sf::Vector2i(x, y));
            }
        }

     // here we place the starting point
        for (int x=rand()%size_.x, y=size_.y; ; x=rand()%size_.x, y=rand()%size_.y) {
            if (tiles_[x][y] == ROOM) {
                startingPoint_ = sf::Vector2i(x, y);
                tiles_[x][y] = EXIT;
                addEntity(new Stairs(false), startingPoint_);
                break;
            }
        }

     // here we place the ending point
        for (int x=rand()%size_.x, y=size_.y; ; x=rand()%size_.x, y=rand()%size_.y) {
            if (tiles_[x][y] == ROOM && (abs(x-startingPoint_.x) > 30 || abs(y-startingPoint_.y) > 30)) {
                endingPoint_ = sf::Vector2i(x, y);
                tiles_[x][y] = EXIT;
                addEntity(new Stairs(true), endingPoint_);
                break;
            }
        }

     // here we generate the chests
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
             // just doing the same checking as in the item generating section
                if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                 // here we choose randomly whether the chest has to be the special (probability = 5%) or the regular one (p = 95%)
                    addEntity(new Chest((rand()%20) ? Chest::REGULAR : Chest::SPECIAL,
                                        getItemFromID(100+(rand()%3)*10+rand()%9, 1)), sf::Vector2i(x, y));
                    tiles_[x][y] = OCCUPIED;
                    break;
                }
            }
        }
    /* ITEMS */
     // here we generate the potions
        for (int i=0; i<rand()%10; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                    addEntity(getItemFromID(100+(rand()%3)*10+rand()%9, 1), sf::Vector2i(x, y));
                    tiles_[x][y] = OCCUPIED;
                    break;
                }
            }
        }

     // here we generate the coins
        for (int i=0; i<rand()%15; i++) {
            while (true) {
                int type = rand()%50;
                int csize; // 0 - big, ≥1 - small
                int x=rand()%size_.x, y=rand()%size_.y;

                if (type < 5) { // GOLD
                    csize = rand()%10;
                    if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                        addEntity(getItemFromID((csize)?1:4, (csize)?rand()%3+1:1), sf::Vector2i(x, y));
                        tiles_[x][y] = OCCUPIED;
                        break;
                    }
                }
                else if (type < 15) { // SILVER
                    csize = rand()%3;
                    if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                        addEntity(getItemFromID((csize)?2:5, (csize)?rand()%20+1:rand()%3+1), sf::Vector2i(x, y));
                        tiles_[x][y] = OCCUPIED;
                        break;
                    }
                }
                else { // BRONZE
                    csize = rand()%2;
                    if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                        addEntity(getItemFromID((csize)?3:6, (csize)?rand()%45+5:rand()%5+1), sf::Vector2i(x, y));
                        tiles_[x][y] = OCCUPIED;
                        break;
                    }
                }
            }
        }

     // here we generate the books
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                 // here we choose randomly the type of book
                    addEntity(getItemFromID(rand()%9+30, 1), sf::Vector2i(x, y));
                    tiles_[x][y] = OCCUPIED;
                    break;
                }
            }
        }

     // here we generate the cold weapon
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {

                 // here we choose randomly the type of cold weapon
                    addEntity(getItemFromID(rand()%13+10, 1), sf::Vector2i(x, y));
                    tiles_[x][y] = OCCUPIED;
                    break;
                }
            }
        }

     // here we place the runic stones
        for (int i=0; i<rand()%15; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x][y] == ROOM && tiles_[x][y] != OCCUPIED) {
                    addEntity(getItemFromID(rand()%12+39, 1), sf::Vector2i(x, y));
                    tiles_[x][y] = OCCUPIED;
                    break;
                }
            }
        }

     // here we place the teachers every 5th level
     {
        sf::Vector2i pos;
        while (true) {
            pos = sf::Vector2i(rand()%10-5, rand()%10-5)+startingPoint_;
            if (!isOnBorder(pos.x, pos.y) && tiles_[pos.x][pos.y] == ROOM
             && startingPoint_+pos != startingPoint_) break;
        }
        switch (levelNumber_) {
        case 5:
            addEntity(new Teacher(Teacher::SWORDSMAN), pos);
            break;
        case 10:
            addEntity(new Teacher(Teacher::SHARPSHOOTER), pos);
            break;
        case 15:
            addEntity(new Teacher(Teacher::CARPENTER), pos);
            break;
        case 20:
            addEntity(new Teacher(Teacher::MAGE), pos);
            break;
        case 25:
            addEntity(new Teacher(Teacher::KUNG_FU_CHAMPION), pos);
            break;
        }
     }

     // and in the end we place the masks upon the whole level to make the player have to discover it all
        for (int x=0; x<size_.x; x++) {
            for (int y=0; y<size_.y; y++) {
                masks_[x][y]->setPosition(sf::Vector2i(x, y));
            }
        }
    }

    void Level::onNotify(Observer::Event event, Entity* entity) {
        switch (event) {
        case Observer::ITEM_DISCOVERED:
            if (instanceof<Potion, Item>((Item*)entity)) {
                for (auto item : entities_) {
                    if (instanceof<Potion, Item>((Item*)item) && ((Potion*)item)->effect_ == ((Potion*)entity)->effect_) {
                        ((Potion*)item)->reveal();
                    }
                }
            }
            else if (instanceof<Rune, Item>((Item*)entity)) {
                for (auto item : entities_) {
                    if (instanceof<Rune, Item>((Item*)item) && ((Rune*)item)->type_ == ((Rune*)entity)->type_) {
                        ((Rune*)item)->reveal();
                    }
                }
            }
            break;
        case Observer::ITEM_DROPPED:
            break;
        default:
            break;
        }
    }

    bool Level::isOnBorder(int x, int y) {
        return x <= 0 || y <= 0 || x >= size_.x-1 || y >= size_.y-1;
    }

    std::vector<std::vector<int>> Level::getTiles() const {
        return tilesAsInts_;
    }

    std::vector<std::vector<Level::Cell>> Level::getTilesAsCells () const {
        return tiles_;
    }
}
