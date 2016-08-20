/**
 * @file src/program/game/level/Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>
#include <stack>

#include "../fov/FOV.hpp"

#include "../../Resources.hpp"
#include "../../observer/Observer.hpp"
#include "../../funcs/files.hpp"
#include "../../funcs/items.hpp"

#include "Level.hpp"

extern rr::Subject subject;

namespace rr {

    Level::Level(int number) :
      size_         (sf::Vector2i(77, 43)),
      shadowMap_    (ShadowMap(size_)    ),
      region_count_ (0                   ),
      levelNumber_  (number              )
    {
        tilemap_.setPrimitiveType(sf::Quads);
        tilemap_.resize(size_.x*size_.y*4);

        for (int i=0; i<size_.x; ++i) {
            for (int j=0; j<size_.y; ++j) {
                regions_[i + j*size_.x] = -1;
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
        
        states = sf::RenderStates::Default;

        for (auto it=entities_.begin(); it!=entities_.end(); ++it) {
            target.draw(**it);
        }
        target.draw(shadowMap_, states);
    }

    void Level::addEntity(Entity* e, sf::Vector2i position) {
        if (e != nullptr) {
            entities_.push_back(e);
            entities_.back()->setGridPosition(position);
        }
    }

    void Level::addEntity(Entity* e) {
        if (  e != nullptr
            ) entities_.push_back(e);
    }

    void Level::playerInteract(Game* game) {
        auto it=entities_.begin();
        while (it != entities_.end()) {
            if (game->getPlayer()->getGridPosition() == (*it)->getGridPosition()) {
                if (instanceof<Item, Entity>(*it)) {
                    if (game->getInventory()->addItem((Item*) *it)) {
                        subject.notify(ITEM_PICKED, *it);
                        entities_.erase(it++);
                    }
                    else game->getMessageManager()->addMessage(Message(Resources::dictionary["message.full_inventory"], sf::Color::Red));
                }
                else if (instanceof<Chest, Entity>(*it)) {
                    Entity* temp  = ((Chest*) *it)->getItem()->clone();
                    auto position = (*it)->getGridPosition();
                    
                    delete *it;
                    *it = temp;
                    (*it++)->setGridPosition(position);
                }
                else if (instanceof<Stairs, Entity>(*it)) {
                    if (((Stairs*) *it)->isUpwards()) {
                        game->switchLevel(levelNumber_+1);
                        break;
                    }
                    else {
                        game->switchLevel(levelNumber_-1);
                        break;
                    }
                }
            }
            else if (instanceof<NPC, Entity>(*it)) {
                auto npc = (NPC*) *it;
                if (npc->getAttitude() != NPC::AGGRESSIVE) {
                    
                }
            }
            ++it;
        }

        makeOrdersToNPCs(game->getPlayer());
    }

    void Level::playerAttack(Player* player) {
        auto it=entities_.begin();
        while (it!=entities_.end()) {
            // the entity is an NPC
            if (instanceof<NPC, Entity>(*it)) {
                auto npc = (NPC*) *it;
                // the npc detects the player
                if ((npc)->detects(player) != -1) {
                    npc->setState(NPC::HUNTING);

                    // the player has a weapon
                    if (player->getColdWeapon() != nullptr && chance(player->getColdWeapon()->getAccuracy()*2, 21)) {
                        player->attack(npc);
                        subject.notify(PLAYER_ATTACK_SUCCESS, npc);
                    }
                    // the player has no weapon
                    else if (player->getColdWeapon() == nullptr && chance(10, 21)) {
                        player->attack(npc);
                        subject.notify(PLAYER_ATTACK_SUCCESS, npc);
                    }
                    // the probability didn't let the player attack
                    else subject.notify(PLAYER_ATTACK_FAILURE, npc);

                    // the npc dies
                    if (npc->getAttributes().health <= 0) {
                        subject.notify(NPC_DIES, npc);
                        player->addExperience(npc->getAttributes().level*10);
                    }

                    break;
                }
            }
            ++it;
        }

        makeOrdersToNPCs(player);
    }

    void Level::update(Game* game, sf::Clock& timer) {
        for (auto it=entities_.begin(); it!=entities_.end(); ++it) {
            if (instanceof<Door, Entity>(*it)) {
                if (  game->getPlayer()->collides(*it)
                    ) ((Door*) *it)->setOpen(true);
                else  ((Door*) *it)->setOpen(false);
            }
            else if (instanceof<NPC, Entity>(*it)) {
                auto npc = (NPC*) *it;
                npc->update(tilesAsInts_, timer.getElapsedTime());
            }
        }
    }

    void Level::makeOrdersToNPCs(Player* player) {
        // clearing all the previously occupied tiles
        for (int i=0; i<77*43; ++i) {
            if (tiles_[i] == OCCUPIED) {
                tiles_      [i] = ROOM;
                tilesAsInts_[i] = 2;
            }
        }

        for (auto it=entities_.begin(); it!=entities_.end(); ++it) {
            if (instanceof<NPC, Entity>(*it)) {
                auto npc = (NPC*) *it;

                {   auto pos = npc->getGridPosition();
                    tiles_      [pos.x + pos.y*size_.x] = OCCUPIED;
                    tilesAsInts_[pos.x + pos.y*size_.x] = 5;    }

                if (npc->getState() == NPC::STANDING) {
                    while (true) {
                        int x=rand()%size_.x, y=rand()%size_.y;
                        if (tiles_[x + y*size_.x] == ROOM && tiles_[x + y*size_.x] != OCCUPIED) {
                            npc->setDestination(sf::Vector2i(x, y));
                            npc->setState(NPC::EXPLORING);
                            break;
                        }
                    }
                }

                if (npc->getAttitude() == NPC::AGGRESSIVE && npc->getState() == NPC::HUNTING) { // the npc is either aggressive and hunting
                    int detector = npc->detects(player);
                    if (detector != -1) { // the npc detects player

                        if      ( (detector == 0 || detector == 3 || detector == 5) && npc->getDirection() != NPC::LEFT
                                 ) npc->setDirection(NPC::LEFT);
                        else if ( (detector == 2 || detector == 4 || detector == 7) && npc->getDirection() != NPC::RIGHT
                                 ) npc->setDirection(NPC::RIGHT);

                        if (instanceof<Bandit, NPC>(npc)) { // the npc is a bandit
                            bool hit = false;
                            switch (((Bandit*) npc)->getType()) {
                                case Bandit::CLUB    : if (chance(ColdWeapon(ColdWeapon::CLUB).getAccuracy()*2, 21)) {
                                                           ((Bandit*) npc)->attack(player);
                                                           hit = true;
                                                       }
                                                       break;

                                case Bandit::CROSSBOW: if (chance(RangedWeapon(RangedWeapon::CROSSBOW).getAccuracy()*2, 21)) {
                                                           ((Bandit*) npc)->attack(player);
                                                           hit = true;
                                                       }
                                                       break;

                                case Bandit::DAGGER  : if (chance(ColdWeapon(ColdWeapon::DAGGER).getAccuracy()*2, 21)) {
                                                           ((Bandit*) npc)->attack(player);
                                                           hit = true;
                                                       }
                                                       break;
                            }

                            if (  hit
                                ) subject.notify(NPC_ATTACK_SUCCESS, npc); // the npc hit the player
                            else  subject.notify(NPC_ATTACK_FAILURE, npc); // the player dodged the attack
                        }
                    }
                }
            }
        }
    }

    void Level::calculateFOV(sf::Vector2i origin, int range) {
        FOV::compute(&shadowMap_, tilesAsInts_, origin, range);
    }

    void Level::generateWorld() {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i=0; i<size_.x; ++i) {
            for (int j=0; j<size_.y; ++j) {
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
        for (int x=rand()%size_.x, y=rand()%size_.y; ; x=rand()%size_.x, y=rand()%size_.y) {
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
        for (int i=0; i<size_.x; ++i) {
            for (int j=0; j<size_.y; ++j) {
                tilesAsInts_[i + j*size_.x] = tiles_[i + j*size_.x];
            }
        }
    }

    void Level::digRooms() {
        for (int i=0; i<100; ++i) {
            sf::Vector2i rsize((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((size_.x-rsize.x)/2)*2+1, rand()%((size_.y-rsize.y)/2)*2+1);

            bool intersects = false;
            for (int i=rpos.x; i<rpos.x+rsize.x; ++i) {
                if (tiles_[i+(rpos.y-1)*size_.x] == ROOM || tiles_[i+(rpos.y+rsize.y+1)*size_.x] == ROOM) {
                    intersects = true;
                    break;
                }
            }
            for (int i=rpos.y; i<rpos.y+rsize.y && !intersects; ++i) {
                if (tiles_[rpos.x-1+i*size_.x] == ROOM || tiles_[rpos.x+rsize.x+i*size_.x] == ROOM) {
                    intersects = true;
                    break;
                }
            }

            if (!intersects) {
                for (int i=rpos.x; i<rpos.x+rsize.x; ++i) {
                    for (int j=rpos.y; j<rpos.y+rsize.y; ++j) {
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

                tiles_  [cell.x+dir.x   + (cell.y+dir.y  )*size_.x] = CORRIDOR;
                tiles_  [cell.x+dir.x*2 + (cell.y+dir.y*2)*size_.x] = CORRIDOR;

                regions_[cell.x+dir.x   + (cell.y+dir.y  )*size_.x] = region_count_;
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
            for (int entrances = rand()%2+2; entrances>0; --entrances) {
                sf::Vector2i position;
                bool found = false;

                int tries = 1000;
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
            for (int i=1; i<size_.x-1; ++i) {
                for (int j=1; j<size_.y-1; ++j) {
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
                switch (tiles_[i + j*size_.x]) { // assigning an appropriate tile number to a given cell
                    case CHASM: tileNumber = 0;
                                break;

                    case WALL : tileNumber = 8;
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
                                             )                                      tileNumber += ALL         *16;
        
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
                                             )                                      tileNumber += NO_RIGHT    *16;
        
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
                                             )                                      tileNumber += TOP_LEFT    *16;
        
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
                                        if      ((tiles_[i+1 + j*size_.x] != WALL)) tileNumber += LEFT_RIGHT  *16;
                                        else if ((tiles_[i+1 + j*size_.x] == WALL)) tileNumber += LEFT        *16;
                                    }
                                    else if (j == 0)                                tileNumber += TOP_LEFT    *16;
                                    else if (j == size_.y-1)                        tileNumber += BOTTOM_LEFT *16;
                                }
                                else if (i == size_.x-1) {
                                    if (j > 0 && j < size_.y-1) {
                                        if      ((tiles_[i-1+j*size_.x] != WALL))   tileNumber += LEFT_RIGHT  *16;
                                        else if ((tiles_[i-1+j*size_.x] == WALL))   tileNumber += RIGHT       *16;
                                    }
                                    else if (j == 0)                                tileNumber += TOP_RIGHT   *16;
                                    else if (j == size_.y-1)                        tileNumber += BOTTOM_RIGHT*16;
                                }
                                else if (j == 0 && i > 0 && i < size_.x-1) {
                                    if      ((tiles_[i+(j+1)*size_.x] != WALL))     tileNumber += TOP_BOTTOM  *16;
                                    else if ((tiles_[i+(j+1)*size_.x] == WALL))     tileNumber += TOP         *16;
                                }
                                else if (j == size_.y-1 && i > 0 && i < size_.x-1) {
                                    if      ((tiles_[i+(j-1)*size_.x] != WALL))     tileNumber += TOP_BOTTOM  *16;
                                    else if ((tiles_[i+(j-1)*size_.x] == WALL))     tileNumber += BOTTOM      *16;
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
        for (int x=1; x<size_.x-1; ++x) {
            for (int y=1; y<size_.y-1; ++y) {
                if (  tiles_[x+y*size_.x] == ENTRANCE
                    ) addEntity(new Door(false), sf::Vector2i(x, y));
            }
        }

        std::stack<sf::Vector2i> toUnOccupy;

     // here we generate the chests
        for (int i=0; i<rand()%5; ++i) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x+y*size_.x] == ROOM && tiles_[x+y*size_.x] != OCCUPIED) {
                    addEntity(new Chest((rand()%20) ? Chest::REGULAR : Chest::SPECIAL), sf::Vector2i(x, y)); // here we choose randomly whether the chest
                    tiles_[x+y*size_.x] = OCCUPIED;                                                          // has to be the special (probability = 5%)
                    toUnOccupy.push(sf::Vector2i(x, y));                                                     // or the regular one (p = 95%)
                    break;
                }
            }
        }

     /* ITEMS */
     // at this moment all we need is just to place random items in random places, we'll deal with the balance later
        for (int i=0; i<rand()%15+15; ++i) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x+y*size_.x] == ROOM && tiles_[x+y*size_.x] != OCCUPIED) {
                    addEntity(getRandomItemBalanced(), sf::Vector2i(x, y));
                    tiles_[x+y*size_.x] = OCCUPIED;
                    toUnOccupy.push(sf::Vector2i(x, y));
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
               case 5 : addEntity(new Teacher(Teacher::SWORDSMAN     ), pos); tiles_[pos.x + pos.y*size_.x] = OCCUPIED; break;
               case 10: addEntity(new Teacher(Teacher::SHARPSHOOTER  ), pos); tiles_[pos.x + pos.y*size_.x] = OCCUPIED; break;
               case 15: addEntity(new Teacher(Teacher::CARPENTER     ), pos); tiles_[pos.x + pos.y*size_.x] = OCCUPIED; break;
               case 20: addEntity(new Teacher(Teacher::MAGE          ), pos); tiles_[pos.x + pos.y*size_.x] = OCCUPIED; break;
               case 25: addEntity(new Teacher(Teacher::KUNG_FU_MASTER), pos); tiles_[pos.x + pos.y*size_.x] = OCCUPIED; break;
           }
        }
     // here we put some enemies
        for (int i=0; i<(int) rand()%15+15; ++i) {
            while (true) {
                int x=rand()%size_.x, y=rand()%size_.y;
                if (tiles_[x + y*size_.x] == ROOM && tiles_[x + y*size_.x] != OCCUPIED) {
                    int weapon = rand()%3;
                    switch (weapon) {
                        case 0: addEntity(new Bandit(Bandit::CLUB    ), sf::Vector2i(x, y)); break;
                        case 1: addEntity(new Bandit(Bandit::CROSSBOW), sf::Vector2i(x, y)); break;
                        case 2: addEntity(new Bandit(Bandit::DAGGER  ), sf::Vector2i(x, y)); break;
                    }
                    tiles_[x + y*size_.x] = OCCUPIED;
                    break;
                }
            }
        }

        while (!toUnOccupy.empty()) {
            tiles_[toUnOccupy.top().x + 77*toUnOccupy.top().y] = ROOM;
            toUnOccupy.pop();
        }
    }

    void Level::onNotify(Observer::Event event, Entity* entity) {
        switch (event) {
            case ITEM_DROPPED: addEntity(entity);
                                         break;

            case PLAYER_DIES : break;
            
            case NPC_DIES    : entities_.remove(entity);
                               break;

            default          : break;
        }
    }

    bool Level::isOnBorder(int x, int y) {
        return x <= 0 || y <= 0 || x >= size_.x-1 || y >= size_.y-1;
    }

    std::ifstream& Level::operator<<(std::ifstream& file) {
        for (auto entity=entities_.begin(); entity!=entities_.end(); ++entity) { // delete the entities
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
                    case  0: entity = new Ammunition  (); readEntity(file, entity); addEntity(entity); break;
                    case  1: entity = new Book        (); readEntity(file, entity); addEntity(entity); break;
                    case  2: entity = new Coin        (); readEntity(file, entity); addEntity(entity); break;
                    case  3: entity = new ColdWeapon  (); readEntity(file, entity); addEntity(entity); break;
                    case  4: entity = new Food        (); readEntity(file, entity); addEntity(entity); break;
                    case  5: entity = new Potion      (); readEntity(file, entity); addEntity(entity); break;
                    case  6: entity = new RangedWeapon(); readEntity(file, entity); addEntity(entity); break;
                    case  7: entity = new Rune        (); readEntity(file, entity); addEntity(entity); break;
                    case 20: entity = new Bandit      (); readEntity(file, entity); addEntity(entity); break;
                    case 21: entity = new Teacher     (); readEntity(file, entity); addEntity(entity); break;
                    case 40: entity = new Chest       (); readEntity(file, entity); addEntity(entity); break;
                    case 41: entity = new Door        (); readEntity(file, entity); addEntity(entity); break;
                    case 42: entity = new Stairs      (); readEntity(file, entity); addEntity(entity); break;
                }
            }

            shadowMap_ << file;

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
             << startingPoint_.y << '\n'  // save the starting point
             << endingPoint_  .x << ' '
             << endingPoint_  .y << '\n'; // save the ending point

        file << entities_.size() << '\n';
        for (auto entity=entities_.begin(); entity!=entities_.end(); ++entity) { // save the entities
            **entity >> file << '\n';
        }
        
        shadowMap_ >> file;
        
        for (int i=0; i<77*43; ++i) { // save the tiles
            file << tiles_[i] << (((i+1)%77 == 0) ? '\n' : ' ');
        }

        return file;
    }

}
