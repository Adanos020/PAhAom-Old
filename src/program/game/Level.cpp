/**
 * @file src/program/game/Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>
#include <stack>

#include "FOV.hpp"

#include "../Resources.hpp"
#include "../Observer.hpp"
#include "../funcs/files.hpp"
#include "../funcs/items.hpp"

#include "Level.hpp"

extern rr::Subject subject;

namespace rr
{

    Level::Level(int number, Player* player) :
      m_size       (sf::Vector2i(77, 43)),
      m_shadowMap  (ShadowMap(m_size)),
      m_regionCount(0),
      m_levelNumber(number)
    {
        m_tilemap.setPrimitiveType(sf::Quads);
        m_tilemap.resize(m_size.x*m_size.y*4);

        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_regions[i + j*m_size.x] = -1;
            }
        }
    }

    Level::~Level()
    {
        for (auto entity : m_entities)
        {
            delete entity;
        }
        m_entities.clear();
    }

    void
    Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &Resources::texture.tileset;
        target.draw(m_tilemap, states);

        states = sf::RenderStates::Default;

        for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
        {
            target.draw(**it);
        }
        target.draw(m_shadowMap, states);
    }

    void
    Level::addEntity(Entity* e, sf::Vector2i position)
    {
        if (e != nullptr)
        {
            e->setGridPosition(position);
            m_entities.push_back(e);

            if (e->getSpecies() == Entity::N_P_C) m_npcs .push_back((NPC *) e);
            if (e->getSpecies() == Entity::ITEM ) m_items.push_back((Item*) e);
        }
    }

    void
    Level::addEntity(Entity* e)
    {
        if (e != nullptr)
        {
            m_entities.push_back(e);

            if (e->getSpecies() == Entity::N_P_C)
                m_npcs .push_back((NPC*) e);
            if (e->getSpecies() == Entity::ITEM)
                m_items.push_back((Item*) e);
        }
    }

    void
    Level::playerInteract(Game* game)
    {
        std::vector <Item*> toErase;

        for (auto& entity : m_entities)
        {
            if (game->getPlayer()->getGridPosition() == entity->getGridPosition())
            {
                if (entity->getSpecies() == Entity::ITEM)
                {
                    if (game->getInventory()->addItem((Item*) entity))
                    {
                        subject.notify(ITEM_PICKED, entity);
                        toErase.push_back((Item*)entity);
                    }
                    else game->getMessageManager()->addMessage(Message(Resources::dictionary["message.full_inventory"], sf::Color::Red));
                }
                else if (entity->getSpecies() == Entity::CHEST)
                {
                    Entity* temp  = ((Chest*) entity)->getItem()->clone();
                    auto position = entity->getGridPosition();

                    delete entity;
                    entity = temp;
                    entity->setGridPosition(position);
                }
                else if (entity->getSpecies() == Entity::STAIRS)
                {
                    if (((Stairs*) entity)->isUpwards())
                    {
                        game->switchLevel(m_levelNumber+1);
                        return;
                    }
                    else
                    {
                        game->switchLevel(m_levelNumber-1);
                        return;
                    }
                }
            }
            else if (entity->getSpecies() == Entity::N_P_C)
            {
                auto npc = (NPC*) entity;
                if (npc->detects(game->getPlayer()) != -1 && npc->getAttitude() != NPC::HOSTILE)
                {
                    game->getConversationUI()->open(npc);
                    game->pause(true);
                }
            }
        }

        for (auto& ent : toErase)
        {
            m_items.erase( std::find(m_items.begin(), m_items.end(), ent ) );
            m_entities.erase( std::find(m_entities.begin(), m_entities.end(), (Entity*)ent ) );
        }
        
        makeOrdersToNPCs(game->getPlayer());
    }

    void
    Level::playerAttack(Player* player)
    {
        auto it = m_npcs.begin();
        while (it != m_npcs.end())
        {
            auto npc = *it;
            // the npc detects the player
            if ((npc)->detects(player) != -1)
            {
                // the player has a weapon
                if (player->getMeleeWeapon() != nullptr && chance(player->getMeleeWeapon()->getAccuracy()*2, 21))
                {
                    player->attack(npc);
                    subject.notify(PLAYER_ATTACK_SUCCESS, npc);
                }
                // the player has no weapon
                else if (player->getMeleeWeapon() == nullptr && chance(10, 21))
                {
                    player->attack(npc);
                    subject.notify(PLAYER_ATTACK_SUCCESS, npc);
                }
                // the probability didn't let the player attack
                else subject.notify(PLAYER_ATTACK_FAILURE, npc);

                // the npc dies
                if (npc->getAttributes().health <= 0)
                {
                    subject.notify(NPC_DIES, npc);
                    player->addExperience(npc->getAttributes().level*10);
                }

                break;
            }
            ++it;
        }

        makeOrdersToNPCs(player);
    }

    void
    Level::update(Game* game, sf::Time& time)
    {
        for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
        {
            if ((*it)->getSpecies() == Entity::DOOR)
            {
                if (game->getPlayer()->collides(*it) || getEntityAt((*it)->getGridPosition(), Entity::DOOR) != nullptr)
                    ((Door*) *it)->setOpen(true);
                else
                    ((Door*) *it)->setOpen(false);
            }
            else if ((*it)->getSpecies() == Entity::N_P_C)
            {
                auto npc = (NPC*) *it;
                npc->update(m_tilesAsInts, time);
            }
        }
    }

    void
    Level::makeOrdersToNPCs(Player* player)
    {
        std::vector <int> toClear; 
        // clearing all the previously occupied tiles
        for (int i = 0; i < 77*43; ++i)
        {
            if (m_tiles[i] == OCCUPIED)
            {
                toClear.push_back(i);
            }
        }

        for (auto it = m_npcs.begin(); it != m_npcs.end(); ++it)
        {
            (*it)->react(this, player);

            auto pos = (*it)->getGridPosition();

            m_tiles      [pos.x + pos.y*m_size.x] = OCCUPIED;
            m_tilesAsInts[pos.x + pos.y*m_size.x] = 5;
        }

        for (auto i : toClear)
        {
            m_tiles[i] = ROOM;
            m_tilesAsInts[i] = 2;
        }

        for (auto it = m_npcs.begin(); it != m_npcs.end(); ++it)
        {
            auto pos = (*it)->getGridPosition();

            m_tiles      [pos.x + pos.y*m_size.x] = OCCUPIED;
            m_tilesAsInts[pos.x + pos.y*m_size.x] = 5;
        }
    }

    void
    Level::calculateFOV(sf::Vector2i origin, int range)
    {
        FOV::compute(m_shadowMap, *this, origin, range);
    }

    void
    Level::closeDoors()
    {
        for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
        {
            if ((*it)->getSpecies() == Entity::DOOR)
                ((Door*) (*it))->setOpen(false);
        }
    }

    Entity*
    Level::getEntityAt(sf::Vector2i pos, Entity::Species consider, bool include) const
    {
        for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
        {
            if (include != ((*it)->getSpecies() == consider))
                continue;
            if ((*it)->getGridPosition() == pos)
                return *it;
        }
        return nullptr;
    }

    void
    Level::generateWorld()
    {
     // first we create an 2-dimensional array filled with 1's representing a wall
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_tiles[i + j*m_size.x] = WALL;
            }
        }

     // at this point we generate some rooms to our level
        digRooms();

     // then we pick the entrance cells to be our starting points and start digging corridors among the rooms
        for (int i = 1; i < m_size.x; i += 2)
        {
            for (int j = 1; j < m_size.y; j += 2)
            {
                if (m_tiles[i + j*m_size.x] == WALL)
                {
                    fillWithMaze(i, j);
                }
            }
        }

     // after that we generate the entrances between the rooms and corridors
        connectRooms();

     // and then we can get rid of the dead ends of the corridors
        removeDeadEnds();

     // here we place the starting point
        for (int x = rand()%m_size.x, y = m_size.y; ; x = rand()%m_size.x, y = rand()%m_size.y)
        {
            if (m_tiles[x + y*m_size.x] == ROOM)
            {
                m_startingPoint = sf::Vector2i(x, y);
                m_tiles[x + y*m_size.x] = EXIT;

                if (m_levelNumber >= 1)
                    addEntity(new Stairs(false), m_startingPoint);
                break;
            }
        }

     // here we place the ending point
        if (m_levelNumber < 29)
        for (int x=rand()%m_size.x, y=rand()%m_size.y; ; x=rand()%m_size.x, y=rand()%m_size.y)
        {
            if (m_tiles[x + y*m_size.x] == ROOM && (m_levelNumber == 1 || (abs(x-m_startingPoint.x) > 30 || abs(y-m_startingPoint.y) > 30)))
            {
                m_endingPoint = sf::Vector2i(x, y);
                m_tiles[x + y*m_size.x] = EXIT;
                addEntity(new Stairs(true), m_endingPoint);
                break;
            }
        }

     // here we generate the entities
        placeEntities();

     // in the end we generate the tile map from the created array
        generateTileMap();

     // and just transform the table of cells to a table of ints
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_tilesAsInts[i + j*m_size.x] = m_tiles[i + j*m_size.x];
            }
        }
    }

    void
    Level::digRooms()
    {
        for (int i = 0; i < 100; ++i)
        {
            sf::Vector2i rsize((rand()%4+1)*2+1, (rand()%4+1)*2+1);
            sf::Vector2i rpos(rand()%((m_size.x-rsize.x)/2)*2+1, rand()%((m_size.y-rsize.y)/2)*2+1);

            bool intersects = false;
            for (int i = rpos.x; i < rpos.x+rsize.x; ++i)
            {
                if (m_tiles[i + (rpos.y-1)*m_size.x] == ROOM || m_tiles[i+(rpos.y+rsize.y+1)*m_size.x] == ROOM)
                {
                    intersects = true;
                    break;
                }
            }
            for (int i = rpos.y; i < rpos.y+rsize.y && !intersects; ++i)
            {
                if (m_tiles[rpos.x-1 + i*m_size.x] == ROOM || m_tiles[rpos.x+rsize.x+i*m_size.x] == ROOM)
                {
                    intersects = true;
                    break;
                }
            }

            if (!intersects)
            {
                for (int i = rpos.x; i < rpos.x+rsize.x; ++i)
                {
                    for (int j = rpos.y; j < rpos.y+rsize.y; ++j)
                    {
                        m_tiles  [i + j*m_size.x] = ROOM;
                        m_regions[i + j*m_size.x] = m_regionCount;
                    }
                }

                m_rooms.push_back(sf::IntRect(rpos, rsize));
                m_regionCount++;
            }
        }
    }

    void
    Level::fillWithMaze(int r, int c)
    {
        m_regionCount++;

        m_tiles  [r + c*m_size.x] = CORRIDOR;
        m_regions[r + c*m_size.x] = m_regionCount;

        std::vector<sf::Vector2i> cells;
        cells.push_back(sf::Vector2i(r, c));

        sf::Vector2i lastDir = sf::Vector2i(0, 0);

        std::vector<sf::Vector2i> directions;
        directions.push_back(sf::Vector2i(-1,  0));
        directions.push_back(sf::Vector2i( 0, -1));
        directions.push_back(sf::Vector2i( 1,  0));
        directions.push_back(sf::Vector2i( 0,  1));

        while (!cells.empty())
        {
            sf::Vector2i cell = cells.back();

            std::vector<sf::Vector2i> unmadeCells;

            for (auto dir : directions)
            {
                if (!isOnBorder(cell.x+dir.x*3, cell.y+dir.y*3) && m_tiles[cell.x+dir.x*2+(cell.y+dir.y*2)*m_size.x] == WALL)
                    unmadeCells.push_back(dir);
            }

            if (!unmadeCells.empty())
            {
                sf::Vector2i dir;

                bool found = false;
                for (auto x : unmadeCells)
                {
                    if (x == lastDir)
                    {
                        found = true;
                        break;
                    }
                }
                if (found && rand()%100 > 0)
                    dir = lastDir;
                else
                    dir = unmadeCells[rand()%unmadeCells.size()];

                m_tiles  [cell.x+dir.x   + (cell.y+dir.y  )*m_size.x] = CORRIDOR;
                m_tiles  [cell.x+dir.x*2 + (cell.y+dir.y*2)*m_size.x] = CORRIDOR;

                m_regions[cell.x+dir.x   + (cell.y+dir.y  )*m_size.x] = m_regionCount;
                m_regions[cell.x+dir.x*2 + (cell.y+dir.y*2)*m_size.x] = m_regionCount;

                cells.push_back(cell+dir*2);
                lastDir = dir;
            }
            else
            {
                cells.pop_back();
                lastDir = sf::Vector2i(0, 0);
            }
        }
    }

    void
    Level::connectRooms()
    {
     // a container of tiles which can connect two regions
        std::vector<sf::Vector2i> connectors;

     // we have to place the conectors on every tile on whose two opposite sides is no wall
        for (sf::Vector2i pos(1, 1); pos.x<m_size.x-1 && pos.y<m_size.y-1; pos += (pos.x >= m_size.x-2 ? sf::Vector2i(-(m_size.x-3), 1) : sf::Vector2i(1, 0)))
        {

         // we cannot place a connector on a tile which is not a wall
            if (m_tiles[pos.x+pos.y*m_size.x] == WALL)
            {
                if (m_regions[pos.x-1+pos.y*m_size.x] != -1 && m_regions[pos.x+1+pos.y*m_size.x] != -1)
                {
                 // are there walls neither on the right nor on the left?
                    if (m_tiles[pos.x-1+pos.y*m_size.x] == CORRIDOR || m_tiles[pos.x+1+pos.y*m_size.x] == CORRIDOR)
                    {
                     // the regions on both sides cannot be the same if one of them is a corridor
                        if (m_regions[pos.x-1+pos.y*m_size.x] != m_regions[pos.x+1+pos.y*m_size.x])
                            connectors.push_back(pos);
                    }
                    else connectors.push_back(pos);
                }

             // are there walls neither above nor below?
                else if (m_regions[pos.x+(pos.y-1)*m_size.x] != -1 && m_regions[pos.x+(pos.y+1)*m_size.x] != -1)
                {
                    if (m_tiles[pos.x+(pos.y-1)*m_size.x] == CORRIDOR || m_tiles[pos.x+(pos.y+1)*m_size.x] == CORRIDOR)
                    {
                     // the regions on both sides cannot be the same if one of them is a corridor
                        if (m_regions[pos.x+(pos.y-1)*m_size.x] != m_regions[pos.x+(pos.y+1)*m_size.x])
                            connectors.push_back(pos);
                    }
                    else connectors.push_back(pos);
                }
            }
        }

     // then we iterate on each room and give it a random numbers of entrances
        for (auto room = m_rooms.begin(); room != m_rooms.end(); ++room)
        {
            for (int entrances = rand()%2+2; entrances > 0; --entrances)
            {
                sf::Vector2i position;
                bool found = false;

                int tries = 1000;
                while (!found && tries > 0)
                {
                    switch (rand()%2)
                    {
                        // LEFT OR RIGHT
                        case 0: position = (rand()%2) ? sf::Vector2i(room->left - 1          , room->top + rand()%room->height)
                                                      : sf::Vector2i(room->left + room->width, room->top + rand()%room->height); break;
                        // UP OR DOWN
                        case 1: position = (rand()%2) ? sf::Vector2i(room->left + rand()%room->width, room->top - 1)
                                                      : sf::Vector2i(room->left + rand()%room->width, room->top + room->height); break;
                    }

                    for (auto x : connectors)
                    {
                        if (x == position)
                        {
                            found = true;
                            m_tiles[position.x+position.y*m_size.x] = ENTRANCE;
                            break;
                        }
                    }
                    tries--;
                }
            }
        }

     // after that we check if there appear any doors placed next to each other
     // if so-then we delete one of them
        for (sf::Vector2i pos(1, 1); pos.x<m_size.x-1 && pos.y<m_size.y-1; pos += (pos.x >= m_size.x-2 ? sf::Vector2i(-(m_size.x-3), 1) : sf::Vector2i(1, 0)))
        {
            if (m_tiles[pos.x + pos.y*m_size.x] == ENTRANCE)
            {
                if (m_tiles[pos.x-1 + pos.y*m_size.x] == ENTRANCE)
                {
                    if (rand()%2)
                        m_tiles[ pos.x  + pos.y*m_size.x] = WALL;
                    else
                        m_tiles[pos.x-1 + pos.y*m_size.x] = WALL;
                }
                if (m_tiles[pos.x+1 + pos.y*m_size.x] == ENTRANCE)
                {
                    if (rand()%2)
                        m_tiles[ pos.x  + pos.y*m_size.x] = WALL;
                    else
                        m_tiles[pos.x+1 + pos.y*m_size.x] = WALL;
                }
                if (m_tiles[pos.x+(pos.y-1)*m_size.x] == ENTRANCE)
                {
                    if (rand()%2)
                        m_tiles[pos.x +   pos.y*m_size.x  ] = WALL;
                    else
                        m_tiles[pos.x + (pos.y-1)*m_size.x] = WALL;
                }
                if (m_tiles[pos.x + (pos.y+1)*m_size.x] == ENTRANCE)
                {
                    if (rand()%2)
                        m_tiles[pos.x +   pos.y*m_size.x  ] = WALL;
                    else
                        m_tiles[pos.x + (pos.y+1)*m_size.x] = WALL;
                }
            }
        }
    }

    void
    Level::removeDeadEnds()
    {
        bool done = false;

        while (!done)
        {
            done = true;
            for (int i = 1; i < m_size.x-1; ++i)
            {
                for (int j = 1; j < m_size.y-1; ++j)
                {
                    if (m_tiles[i + j*m_size.x] == WALL)
                        continue;

                    // if it only has one exit, it's a dead end.
                    int exits = 0;
                    if (m_tiles[(i-1) + j*m_size.x] != WALL) exits++;
                    if (m_tiles[(i+1) + j*m_size.x] != WALL) exits++;
                    if (m_tiles[i + (j-1)*m_size.x] != WALL) exits++;
                    if (m_tiles[i + (j+1)*m_size.x] != WALL) exits++;

                    if (exits > 1)
                        continue;

                    done = false;
                    m_tiles[i + j*m_size.x] = WALL;
                }
            }
        }
    }

    void
    Level::generateTileMap()
    {
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                int tileNumber;
                switch (m_tiles[i + j*m_size.x]) // assigning an appropriate tile number to a given cell
                {
                    case CHASM: tileNumber = 0;
                                break;

                    case WALL : tileNumber = 8;
                                enum Neighbour
                                {
                                    NONE,
                                    TOP, BOTTOM, LEFT, RIGHT,
                                    TOP_BOTTOM, TOP_LEFT, TOP_RIGHT, LEFT_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                                    NO_TOP, NO_RIGHT, NO_LEFT, NO_BOTTOM,
                                    ALL
                                };
                                if (!isOnBorder(i, j))
                                {
                                    if      (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += ALL         *16;

                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += NO_TOP      *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += NO_BOTTOM   *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += NO_LEFT     *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += NO_RIGHT    *16;

                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += LEFT_RIGHT  *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += BOTTOM_RIGHT*16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += BOTTOM_LEFT *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += TOP_BOTTOM  *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += TOP_RIGHT   *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += TOP_LEFT    *16;

                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] != WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += TOP         *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] != WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += BOTTOM      *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] != WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] == WALL)
                                             )                                      tileNumber += LEFT        *16;
                                    else if (  (m_tiles[ i  + (j-1)*m_size.x] == WALL)
                                            && (m_tiles[ i  + (j+1)*m_size.x] == WALL)
                                            && (m_tiles[i-1 +   j*m_size.x  ] == WALL)
                                            && (m_tiles[i+1 +   j*m_size.x  ] != WALL)
                                             )                                      tileNumber += RIGHT       *16;
                                }
                                else if (i == 0)
                                {
                                    if (j > 0 && j < m_size.y-1)
                                    {
                                        if      ((m_tiles[i+1 + j*m_size.x] != WALL)) tileNumber += LEFT_RIGHT  *16;
                                        else if ((m_tiles[i+1 + j*m_size.x] == WALL)) tileNumber += LEFT        *16;
                                    }
                                    else if (j == 0)                                tileNumber += TOP_LEFT    *16;
                                    else if (j == m_size.y-1)                        tileNumber += BOTTOM_LEFT *16;
                                }
                                else if (i == m_size.x-1)
                                {
                                    if (j > 0 && j < m_size.y-1)
                                    {
                                        if      ((m_tiles[i-1+j*m_size.x] != WALL))   tileNumber += LEFT_RIGHT  *16;
                                        else if ((m_tiles[i-1+j*m_size.x] == WALL))   tileNumber += RIGHT       *16;
                                    }
                                    else if (j == 0)                                tileNumber += TOP_RIGHT   *16;
                                    else if (j == m_size.y-1)                        tileNumber += BOTTOM_RIGHT*16;
                                }
                                else if (j == 0 && i > 0 && i < m_size.x-1)
                                {
                                    if      ((m_tiles[i+(j+1)*m_size.x] != WALL))     tileNumber += TOP_BOTTOM  *16;
                                    else if ((m_tiles[i+(j+1)*m_size.x] == WALL))     tileNumber += TOP         *16;
                                }
                                else if (j == m_size.y-1 && i > 0 && i < m_size.x-1)
                                {
                                    if      ((m_tiles[i+(j-1)*m_size.x] != WALL))     tileNumber += TOP_BOTTOM  *16;
                                    else if ((m_tiles[i+(j-1)*m_size.x] == WALL))     tileNumber += BOTTOM      *16;
                                }
                                break;

                    default   : tileNumber = 17;
                                break;
                }

                int tu = tileNumber%(Resources::texture.tileset.getSize().x/16);
                int tv = tileNumber/(Resources::texture.tileset.getSize().y/16);

                sf::Vertex* quad = &m_tilemap[(i + j*m_size.x)*4];

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

    void
    Level::placeEntities()
    {
     /* OBJECTS */
     // here we place the doors
        for (int x = 1; x < m_size.x-1; ++x)
        {
            for (int y = 1; y < m_size.y-1; ++y)
            {
                if (m_tiles[x + y*m_size.x] == ENTRANCE)
                    addEntity(new Door(false), sf::Vector2i(x, y));
            }
        }

        std::stack<sf::Vector2i> toUnOccupy;

     // here we generate the chests
        for (int i = 0; i < rand()%5; ++i)
        {
            while (true)
            {
                int x=rand()%m_size.x, y=rand()%m_size.y;
                if (m_tiles[x+y*m_size.x] == ROOM && m_tiles[x+y*m_size.x] != OCCUPIED)
                {
                    addEntity(new Chest((rand()%20) ? Chest::REGULAR : Chest::SPECIAL), sf::Vector2i(x, y)); // here we choose randomly whether the chest
                    m_tiles[x+y*m_size.x] = OCCUPIED;                                                          // has to be the special (probability = 5%)
                    toUnOccupy.push(sf::Vector2i(x, y));                                                     // or the regular one (p = 95%)
                    break;
                }
            }
        }

     /* ITEMS */
     // at this moment all we need is just to place random items in random places, we'll deal with the balance later
        for (int i = 0; i < rand()%15+15; ++i)
        {
            while (true)
            {
                int x=rand()%m_size.x, y=rand()%m_size.y;
                if (m_tiles[x+y*m_size.x] == ROOM && m_tiles[x+y*m_size.x] != OCCUPIED)
                {
                    addEntity(getRandomItemBalanced(), sf::Vector2i(x, y));
                    m_tiles[x+y*m_size.x] = OCCUPIED;
                    toUnOccupy.push(sf::Vector2i(x, y));
                    break;
                }
            }
        }

     /* NPCs */
     // here we place the teachers every 5th level
        if (m_levelNumber%5 == 0)
        {
           sf::Vector2i pos;
           while (true)
           {
               pos = sf::Vector2i(rand()%10-5, rand()%10-5)+m_startingPoint;
               if ( !isOnBorder(pos.x, pos.y) && m_tiles[pos.x+pos.y*m_size.x] == ROOM
                  && m_startingPoint+pos != m_startingPoint
                   ) break;
           }
           switch (m_levelNumber)
           {
               case 5 : addEntity(new Teacher(Teacher::SWORDSMAN     ), pos); m_tiles[pos.x + pos.y*m_size.x] = OCCUPIED; break;
               case 10: addEntity(new Teacher(Teacher::SHARPSHOOTER  ), pos); m_tiles[pos.x + pos.y*m_size.x] = OCCUPIED; break;
               case 15: addEntity(new Teacher(Teacher::CARPENTER     ), pos); m_tiles[pos.x + pos.y*m_size.x] = OCCUPIED; break;
               case 20: addEntity(new Teacher(Teacher::MAGE          ), pos); m_tiles[pos.x + pos.y*m_size.x] = OCCUPIED; break;
               case 25: addEntity(new Teacher(Teacher::KUNG_FU_MASTER), pos); m_tiles[pos.x + pos.y*m_size.x] = OCCUPIED; break;
           }
        }
     // here we put some enemies
        for (int i = 0; i < (int) rand()%15+15; ++i)
        {
            while (true)
            {
                int x=rand()%m_size.x, y=rand()%m_size.y;
                if (m_tiles[x + y*m_size.x] == ROOM && m_tiles[x + y*m_size.x] != OCCUPIED)
                {
                    int weapon = rand()%3;
                    switch (weapon)
                    {
                        case 0: addEntity(new Bandit(Bandit::CLUB    ), sf::Vector2i(x, y)); break;
                        case 1: addEntity(new Bandit(Bandit::CROSSBOW), sf::Vector2i(x, y)); break;
                        case 2: addEntity(new Bandit(Bandit::DAGGER  ), sf::Vector2i(x, y)); break;
                    }
                    m_tiles[x + y*m_size.x] = OCCUPIED;
                    break;
                }
            }
        }

        while (!toUnOccupy.empty())
        {
            m_tiles[toUnOccupy.top().x + 77*toUnOccupy.top().y] = ROOM;
            toUnOccupy.pop();
        }
    }

    void
    Level::onNotify(Observer::Event event, Entity* entity)
    {
        switch (event)
        {
            case ITEM_DROPPED:
            {
                addEntity(entity);
            }
            break;

            case NPC_DIES:
            {
                m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity));
                if (entity->getSpecies() == Entity::N_P_C)
                {
                    m_npcs.erase(std::find(m_npcs.begin(), m_npcs.end(), (NPC*) entity));
                    delete entity;
                }
                else if (entity->getSpecies() == Entity::ITEM)
                    m_items.erase(std::find(m_items.begin(), m_items.end(), (Item*) entity));
            }
            break;

            default: break;
        }
    }

    bool
    Level::isOnBorder(int x, int y)
    {
        return x <= 0 || y <= 0 || x >= m_size.x-1 || y >= m_size.y-1;
    }

    std::ifstream&
    Level::operator<<(std::ifstream& file)
    {
        for (auto entity = m_entities.begin(); entity != m_entities.end(); ++entity) // delete the entities
        {
            delete *entity;
        }
        m_entities.clear();

        try
        {
            readFile <int> (file, m_startingPoint.x);
            readFile <int> (file, m_startingPoint.y);
            readFile <int> (file, m_endingPoint  .x);
            readFile <int> (file, m_endingPoint  .y);

            int number;
            readFile <int> (file, number);

            for (int i = 0; i < number; ++i) // load the entities
            {
                int identificator;
                readFile <int> (file, identificator);

                Entity* entity;

                switch (identificator)
                {
                    case  0: entity = new Ammunition  (); readEntity(file, entity); addEntity(entity); break;
                    case  1: entity = new Book        (); readEntity(file, entity); addEntity(entity); break;
                    case  2: entity = new Coin        (); readEntity(file, entity); addEntity(entity); break;
                    case  3: entity = new MeleeWeapon (); readEntity(file, entity); addEntity(entity); break;
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

            m_shadowMap << file;

            for (int i = 0; i < 77*43; ++i) // load the tiles
            {
                file >> m_tilesAsInts[i];
                m_tiles[i] = (Cell) m_tilesAsInts[i];
            }
            generateTileMap();
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream&
    Level::operator>>(std::ofstream& file)
    {
        file << m_startingPoint.x << ' '
             << m_startingPoint.y << '\n'  // save the starting point
             << m_endingPoint  .x << ' '
             << m_endingPoint  .y << '\n'; // save the ending point

        file << m_entities.size() << '\n';
        for (auto entity = m_entities.begin(); entity != m_entities.end(); ++entity) // save the entities
        {
            **entity >> file << '\n';
        }

        m_shadowMap >> file;

        for (int i = 0; i < 77*43; ++i) // save the tiles
        {
            file << m_tilesAsInts[i] << (((i+1)%77 == 0) ? '\n' : ' ');
        }

        return file;
    }

}
