/**
 * @file src/program/game/Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Game.hpp"
#include "fov/FOV.hpp"
#include "entity/Entity.hpp"

#include "../Resources.hpp"

#include "../funcs/files.hpp"
#include "../funcs/items.hpp"

namespace rr {

    Level::Level(int number) :
      size_         (sf::Vector2i(77, 43)),
      region_count_ (0                   ),
      levelNumber_  (number              )
    {
        tilemap_.setPrimitiveType(sf::Quads);
        tilemap_.resize(size_.x*size_.y*4);

        for (int i=0; i<size_.x; i++) {
            for (int j=0; j<size_.y; j++) {
                regions_[i+j*size_.x] = -1;
            }
        }
    }

    Level::~Level() {
        for (auto entity : entities_) {
            delete entity;
        }
        entities_.clear();
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &Resources::texture.tileset;
        target.draw(tilemap_, states);
    }

    void Level::drawObjects(sf::RenderWindow& rw) const {
        for (auto it=entities_.begin(); it!=entities_.end(); ++it) {
            (*it)->draw(rw);
        }
        for (auto shadow : shadows_) {
            shadow.draw(rw);
        }
    }

    void Level::addEntity(Entity* e, sf::Vector2i position) {
        if (e != nullptr) {
            entities_.push_back(e);
            entities_.back()->setPosition(position);
        }
    }

    void Level::addEntity(Entity* e) {
        if (  e != nullptr
            ) entities_.push_back(e);
    }

    void Level::replaceEntity(unsigned index, Entity* entity) {
        Entity* temp  = entity->clone();

        auto it = entities_.begin();
        for (unsigned i=0; i<index; ++i) {
            ++it;
        }

        auto position = (*it)->getPosition();
        
        delete *it;
        *it = temp;

        (*it)->setPosition(position);
    }

    void Level::removeEntity(unsigned index) {
        auto it = entities_.begin();
        for (unsigned i=0; i<index; ++i) {
            ++it;
        }
        entities_.erase(it);
    }

    void Level::calculateFOV(sf::Vector2u origin, int range) {
        FOV::compute(shadows_, tilesAsInts_, origin, range);
    }

    void Level::generateWorld() {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i=0; i<size_.x; i++) {
            for (int j=0; j<size_.y; j++) {
                tiles_[i+j*size_.x] = WALL;
            }
        }

     // at this point we generate some rooms to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the rooms
        for (int i=1; i<size_.x; i+=2) {
            for (int j=1; j<size_.y; j+=2) {
                if (tiles_[i + j*size_.x] == WALL) {
                    fillWithMaze(i, j);
                }
            }
        }

     // after that we generate the entrances between the rooms and corridors
        connectRooms();

     // and then we can get rid of the dead ends of the corridors
        removeDeadEnds();

     // here we place the starting point
        for (int x=rand()%size_.x, y=size_.y; ; x=rand()%size_.x, y=rand()%size_.y) {
            if (tiles_[x+y*size_.x] == ROOM) {
                startingPoint_ = sf::Vector2i(x, y);
                tiles_[x+y*size_.x] = EXIT;
                
                if (  levelNumber_ >= 1
                    ) addEntity(new Stairs(false), startingPoint_);
                break;
            }
        }

     // here we place the ending point
        if (levelNumber_ < 29)
        for (int x=rand()%size_.x, y=size_.y; ; x=rand()%size_.x, y=rand()%size_.y) {
            if (tiles_[x+y*size_.x] == ROOM && (levelNumber_ == 1 || (abs(x-startingPoint_.x) > 30 || abs(y-startingPoint_.y) > 30))) {
                endingPoint_ = sf::Vector2i(x, y);
                tiles_[x+y*size_.x] = EXIT;
                addEntity(new Stairs(true), endingPoint_);
                break;
            }
        }

     // here we generate the entities
        placeEntities();

     // in the end we generate the tile map from the created array
        generateTileMap();

     // and just transform the table of cells to a table of ints
        for (int i=0; i<size_.x; i++) {
            for (int j=0; j<size_.y; j++) {
                tilesAsInts_[i + j*size_.x] = tiles_[i + j*size_.x];
            }
        }
     // ... and place the shadows. That's really it
        for (int x=0; x<size_.x; x++) {
            for (int y=0; y<size_.y; y++) {
                shadows_[x + y*size_.x].setPosition(sf::Vector2i(x, y));
            }
        }
    }

    void Level::digRooms() {
        for (int i=0; i<100; i++) {
            sf::Vector2i rsize((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((size_.x-rsize.x)/2)*2+1, rand()%((size_.y-rsize.y)/2)*2+1);

            bool intersects = false;
            for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                if (tiles_[i+(rpos.y-1)*size_.x] == ROOM || tiles_[i+(rpos.y+rsize.y+1)*size_.x] == ROOM) {
                    intersects = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+rsize.y && !intersects; i++) {
                if (tiles_[rpos.x-1+i*size_.x] == ROOM || tiles_[rpos.x+rsize.x+i*size_.x] == ROOM) {
                    intersects = true;
                    break;
                }
            }

            if (!intersects) {
                for (int i=rpos.x; i<rpos.x+rsize.x; i++) {
                    for (int j=rpos.y; j<rpos.y+rsize.y; j++) {
                        tiles_  [i+j*size_.x] = ROOM;
                        regions_[i+j*size_.x] = region_count_;
                    }
                }

                rooms_.push_back(sf::IntRect(rpos, rsize));
                region_count_++;
            }
        }
    }

    void Level::fillWithMaze(int r, int c) {
        region_count_++;

        tiles_  [r+c*size_.x] = CORRIDOR;
        regions_[r+c*size_.x] = region_count_;

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
                if (  !isOnBorder(cell.x+dir.x*3, cell.y+dir.y*3) && tiles_[cell.x+dir.x*2+(cell.y+dir.y*2)*size_.x] == WALL
                    ) unmadeCells.push_back(dir);
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
                if (  found && rand()%100 > 0
                    ) dir = lastDir;
                else  dir = unmadeCells[rand()%unmadeCells.size()];

                tiles_  [ cell.x+dir.x  +  (cell.y+dir.y)*size_.x ] = CORRIDOR;
                tiles_  [cell.x+dir.x*2 + (cell.y+dir.y*2)*size_.x] = CORRIDOR;

                regions_[ cell.x+dir.x  +  (cell.y+dir.y)*size_.x ] = region_count_;
                regions_[cell.x+dir.x*2 + (cell.y+dir.y*2)*size_.x] = region_count_;

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
            if (tiles_[pos.x+pos.y*size_.x] == WALL) {
                if (regions_[pos.x-1+pos.y*size_.x] != -1 && regions_[pos.x+1+pos.y*size_.x] != -1) {

                 // are there walls neither on the right nor on the left?
                    if (tiles_[pos.x-1+pos.y*size_.x] == CORRIDOR || tiles_[pos.x+1+pos.y*size_.x] == CORRIDOR) {

                     // the regions_ on both sides cannot be the same if one of them is a corridor
                        if (  regions_[pos.x-1+pos.y*size_.x] != regions_[pos.x+1+pos.y*size_.x]
                            ) connectors.push_back(pos);
                    }
                    else connectors.push_back(pos);
                }

             // are there walls neither above nor below?
                else if (regions_[pos.x+(pos.y-1)*size_.x] != -1 && regions_[pos.x+(pos.y+1)*size_.x] != -1) {
                    if (tiles_[pos.x+(pos.y-1)*size_.x] == CORRIDOR || tiles_[pos.x+(pos.y+1)*size_.x] == CORRIDOR) {

                     // the regions_ on both sides cannot be the same if one of them is a corridor
                        if (  regions_[pos.x+(pos.y-1)*size_.x] != regions_[pos.x+(pos.y+1)*size_.x]
                            ) connectors.push_back(pos);
                    }
                    else connectors.push_back(pos);
                }
            }
        }

     // then we iterate on each room and give it a random numbers of entrances
        for (auto room=rooms_.begin(); room!=rooms_.end(); ++room) {
            for (int entrances = rand()%2+3; entrances>0; entrances--) {
                sf::Vector2i position;
                bool found = false;

                int tries = 100;
                while (!found && tries > 0) {
                    switch (rand()%2) {
                        // LEFT OR RIGHT
                        case 0: position = (rand()%2) ? sf::Vector2i(room->left - 1          , room->top + rand()%room->height)
                                                      : sf::Vector2i(room->left + room->width, room->top + rand()%room->height); break;
                        // UP OR DOWN
                        case 1: position = (rand()%2) ? sf::Vector2i(room->left + rand()%room->width, room->top - 1)
                                                      : sf::Vector2i(room->left + rand()%room->width, room->top + room->height); break;
                    }

                    for (auto x : connectors) {
                        if (x == position) {
                            found = true;
                            tiles_[position.x+position.y*size_.x] = ENTRANCE;
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
            if (tiles_[pos.x+pos.y*size_.x] == ENTRANCE) {
                if (tiles_[pos.x-1 + pos.y*size_.x] == ENTRANCE) {
                    if (  rand()%2
                        ) tiles_[ pos.x  + pos.y*size_.x] = WALL;
                    else  tiles_[pos.x-1 + pos.y*size_.x] = WALL;
                }
                if (tiles_[pos.x+1 + pos.y*size_.x] == ENTRANCE) {
                    if (  rand()%2
                        ) tiles_[ pos.x  + pos.y*size_.x] = WALL;
                    else  tiles_[pos.x+1 + pos.y*size_.x] = WALL;
                }
                if (tiles_[pos.x+(pos.y-1)*size_.x] == ENTRANCE) {
                    if (  rand()%2
                        ) tiles_[pos.x +   pos.y*size_.x  ] = WALL;
                    else  tiles_[pos.x + (pos.y-1)*size_.x] = WALL;
                }
                if (tiles_[pos.x + (pos.y+1)*size_.x] == ENTRANCE) {
                    if (  rand()%2
                        ) tiles_[pos.x +   pos.y*size_.x  ] = WALL;
                    else  tiles_[pos.x + (pos.y+1)*size_.x] = WALL;
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
                    if (  tiles_[i+j*size_.x] == WALL
                        ) continue;

                    // if it only has one exit, it's a dead end.
                    int exits = 0;
                    if (  tiles_[(i-1)+j*size_.x] != WALL
                        ) exits++;
                    if (  tiles_[(i+1)+j*size_.x] != WALL
                        ) exits++;
                    if (  tiles_[i+(j-1)*size_.x] != WALL
                        ) exits++;
                    if (  tiles_[i+(j+1)*size_.x] != WALL
                        ) exits++;

                    if (  exits > 1
                        ) continue;

                    done = false;
                    tiles_[i+j*size_.x] = WALL;
                }
            }
        }
    }

    void Level::generateTileMap() {
        for (int i=0; i<size_.x; ++i) {
            for (int j=0; j<size_.y; ++j) {
                int tileNumber;
                switch (tiles_[i+j*size_.x]) { // assigning an appropriate tile number to a given cell
                    case CHASM: tileNumber = 0;
                                break;

                    case WALL : tileNumber = rand()%14+2;
                                enum Neighbour {
                                    NONE,
                                    TOP, BOTTOM, LEFT, RIGHT,
                                    TOP_BOTTOM, TOP_LEFT, TOP_RIGHT, LEFT_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                                    NO_TOP, NO_RIGHT, NO_LEFT, NO_BOTTOM,
                                    ALL
                                };
                                if (!isOnBorder(i, j)) {
                                    if      (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                                   )                                       tileNumber += ALL         *16;
        
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += NO_TOP      *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += NO_BOTTOM   *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += NO_LEFT     *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                                   )                                       tileNumber += NO_RIGHT    *16;
        
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += LEFT_RIGHT  *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += BOTTOM_RIGHT*16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                            )                                       tileNumber += BOTTOM_LEFT *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                            )                                       tileNumber += TOP_BOTTOM  *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += TOP_RIGHT   *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                                   )                                       tileNumber += TOP_LEFT    *16;
        
                                    else if (  (tiles_[ i  + (j-1)*size_.x] != WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                            )                                       tileNumber += TOP         *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] != WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                            )                                       tileNumber += BOTTOM      *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] != WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] == WALL)
                                            )                                       tileNumber += LEFT        *16;
                                    else if (  (tiles_[ i  + (j-1)*size_.x] == WALL)
                                            && (tiles_[ i  + (j+1)*size_.x] == WALL)
                                            && (tiles_[i-1 +   j*size_.x  ] == WALL)
                                            && (tiles_[i+1 +   j*size_.x  ] != WALL)
                                            )                                       tileNumber += RIGHT       *16;
                                }
                                else if (i == 0) {
                                    if (j > 0 && j < size_.y-1) {
                                        if      ((tiles_[i+1 + j*size_.x] != WALL))  tileNumber += LEFT_RIGHT  *16;
                                        else if ((tiles_[i+1 + j*size_.x] == WALL))  tileNumber += LEFT        *16;
                                    }
                                    else if (j == 0)                                 tileNumber += TOP_LEFT    *16;
                                    else if (j == size_.y-1)                         tileNumber += BOTTOM_LEFT *16;
                                }
                                else if (i == size_.x-1) {
                                    if (j > 0 && j < size_.y-1) {
                                        if      ((tiles_[i-1+j*size_.x] != WALL))    tileNumber += LEFT_RIGHT  *16;
                                        else if ((tiles_[i-1+j*size_.x] == WALL))    tileNumber += RIGHT       *16;
                                    }
                                    else if (j == 0)                                 tileNumber += TOP_RIGHT   *16;
                                    else if (j == size_.y-1)                         tileNumber += BOTTOM_RIGHT*16;
                                }
                                else if (j == 0 && i > 0 && i < size_.x-1) {
                                    if      ((tiles_[i+(j+1)*size_.x] != WALL))      tileNumber += TOP_BOTTOM  *16;
                                    else if ((tiles_[i+(j+1)*size_.x] == WALL))      tileNumber += TOP         *16;
                                }
                                else if (j == size_.y-1 && i > 0 && i < size_.x-1) {
                                    if      ((tiles_[i+(j-1)*size_.x] != WALL))      tileNumber += TOP_BOTTOM  *16;
                                    else if ((tiles_[i+(j-1)*size_.x] == WALL))      tileNumber += BOTTOM      *16;
                                }
                                break;
                    
                    default   : tileNumber = 17;
                                break;
                }

                int tu = tileNumber%(Resources::texture.tileset.getSize().x/16);
                int tv = tileNumber/(Resources::texture.tileset.getSize().y/16);

                sf::Vertex* quad = &tilemap_[(i + j*size_.x)*4];

                quad[0].position  = sf::Vector2f(  i  *80,   j  *80);
                quad[1].position  = sf::Vector2f((i+1)*80,   j  *80);
                quad[2].position  = sf::Vector2f((i+1)*80, (j+1)*80);
                quad[3].position  = sf::Vector2f(  i  *80, (j+1)*80);

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
                if (  tiles_[x+y*size_.x] == ENTRANCE
                    ) addEntity(new Door(false), sf::Vector2i(x, y));
            }
        }

     // here we generate the chests
        for (int i=0; i<rand()%5; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x+y*size_.x] == ROOM && tiles_[x+y*size_.x] != OCCUPIED) {
                    addEntity(new Chest((rand()%20) ? Chest::REGULAR : Chest::SPECIAL, getRandomItem()), sf::Vector2i(x, y)); // here we choose randomly whether the chest
                    tiles_[x+y*size_.x] = OCCUPIED;                                                                           // has to be the special (probability = 5%)
                    break;                                                                                                    // or the regular one (p = 95%)
                }
            }
        }

     /* ITEMS */
     // at this moment all we need is just to place random items in random places, we'll deal with the balance later
        for (int i=0; i<rand()%15+15; i++) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x+y*size_.x] == ROOM && tiles_[x+y*size_.x] != OCCUPIED) {
                    addEntity(getRandomItem(), sf::Vector2i(x, y));
                    tiles_[x+y*size_.x] = OCCUPIED;
                    break;
                }
            }
        }

     /* NPCs */
     // here we place the teachers every 5th level
        if (levelNumber_%5 == 0) {
           sf::Vector2i pos;
           while (true) {
               pos = sf::Vector2i(rand()%10-5, rand()%10-5)+startingPoint_;
               if ( !isOnBorder(pos.x, pos.y) && tiles_[pos.x+pos.y*size_.x] == ROOM
                  && startingPoint_+pos != startingPoint_
                   ) break;
           }
           switch (levelNumber_) {
               case 5 : addEntity(new Teacher(Teacher::SWORDSMAN     ), pos); break;
               case 10: addEntity(new Teacher(Teacher::SHARPSHOOTER  ), pos); break;
               case 15: addEntity(new Teacher(Teacher::CARPENTER     ), pos); break;
               case 20: addEntity(new Teacher(Teacher::MAGE          ), pos); break;
               case 25: addEntity(new Teacher(Teacher::KUNG_FU_MASTER), pos); break;
           }
        }
    }

    void Level::onNotify(Observer::Event event, Entity* entity) {
        switch (event) {
            case Observer::ITEM_DROPPED: addEntity(entity);
                                         break;
            default                    : break;
        }
    }

    bool Level::isOnBorder(int x, int y) {
        return x <= 0 || y <= 0 || x >= size_.x-1 || y >= size_.y-1;
    }

    std::ifstream& Level::operator<<(std::ifstream& file) {
        for (auto entity=entities_.begin(); entity!=entities_.end(); ++entity) { // save the entities
            delete *entity;
        }
        entities_.clear();

        try {
            readFile <int> (file, startingPoint_.x);
            readFile <int> (file, startingPoint_.y);
            readFile <int> (file, endingPoint_  .x);
            readFile <int> (file, endingPoint_  .y);

            int number;
            readFile <int> (file, number);

            for (int i=0; i<number; ++i) { // load the entities
                int identificator;
                readFile <int> (file, identificator);

                Entity* entity;

                switch (identificator) {
                    case  0: entity = new Chest       (Chest::REGULAR , new Book(Book::CRAFTING)); readEntity(file, entity); addEntity(entity); break;
                    case  1: entity = new Door        (false                                    ); readEntity(file, entity); addEntity(entity); break;
                    case  2: entity = new Book        (Book::CRAFTING	                        ); readEntity(file, entity); addEntity(entity); break;
                    case  3: entity = new Coin        (Coin::BRONZE   , Coin::SMALL             ); readEntity(file, entity); addEntity(entity); break;
                    case  4: entity = new ColdWeapon  (ColdWeapon::KNIFE                        ); readEntity(file, entity); addEntity(entity); break;
                    case  5: /*entity = new Food        (	                                      ); readEntity(file, entity); addEntity(entity);*/ break;
                    case  6: entity = new Potion      (Potion::HEALING, Potion::SMALL           ); readEntity(file, entity); addEntity(entity); break;
                    case  7: /*entity = new RangedWeapon(	                                      ); readEntity(file, entity); addEntity(entity);*/ break;
                    case  8: entity = new Rune        (Rune::HEAL                               ); readEntity(file, entity); addEntity(entity); break;
                    case  9: entity = new Teacher     (Teacher::SWORDSMAN                       ); readEntity(file, entity); addEntity(entity); break;
                    case 10: entity = new Stairs      (false                                    ); readEntity(file, entity); addEntity(entity); break;
                }
            }
            for (int i=0; i<77*43; ++i) { // load the shadows
                shadows_[i] << file;
            }
            for (int x=0; x<77; x++) {
                for (int y=0; y<43; y++) {
                    shadows_[x + y*77].setPosition(sf::Vector2i(x, y));
                }
            }

            for (int i=0; i<77*43; ++i) { // load the tiles
                file >> tilesAsInts_[i];
                tiles_[i] = (Cell)tilesAsInts_[i];
            }
            generateTileMap();
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream& Level::operator>>(std::ofstream& file) {
        file << startingPoint_.x << ' '
             << startingPoint_.y << '\n'              // save the starting point
             << endingPoint_  .x << ' '
             << endingPoint_  .y << '\n';             // save the ending point

        file << entities_.size() << '\n';
        for (auto entity=entities_.begin(); entity!=entities_.end(); ++entity) { // save the entities
            *(*entity) >> file << '\n';
        }
        for (int i=0; i<77*43; ++i) {                 // save the shadows
            shadows_[i] >> file << (((i+1)%77 == 0) ? '\n' : ' ');
        }
        for (int i=0; i<77*43; ++i) {                 // save the tiles
            file << tiles_[i] << (((i+1)%77 == 0) ? '\n' : ' ');
        }

        return file;
    }

}
