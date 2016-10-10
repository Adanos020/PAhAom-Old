/**
 * @file src/program/game/Level.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>

#include "../Observer.hpp"

#include "ShadowMap.hpp"
#include "entity/Player.hpp"

#include "entity/npc/ai/AIManager.hpp"

namespace rr
{

    class AIManager;
    class Game;

/// Class for the level
    class Level : public Observer, public sf::Drawable, public sf::Transformable
    {
    public:  enum Cell
             {
                 CHASM,
                 WALL,
                 ROOM,
                 CORRIDOR,
                 ENTRANCE,
                 OCCUPIED,
                 EXIT
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Level(int number, Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Level();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Generates procedurally the whole level.
             ///
             /// This is done by:
             /// 1. Filling the map with wall blocks
             /// 2. Spreading randomly placed and sized rooms that don't intersect
             /// with each other
             /// 3. Carving a labirynth between the rooms
             /// 4. Connecting each room to the rooms or corridors placed next to it
             /// by placing an entrance on the wall dividing them
             /// 5. Generating a tile map from the matrix created in the previous
             /// steps
             /// 6. Spreading some entities in random places and placing the doors
             /// in the entrances
             ////////////////////////////////////////////////////////////////////////
             void generateWorld();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an entity to the list and sets its position initial.
             ////////////////////////////////////////////////////////////////////////
             void addEntity(Entity*, sf::Vector2i position);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an entity to the list.
             ////////////////////////////////////////////////////////////////////////
             void addEntity(Entity*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the player's interactions between the other entities.
             ////////////////////////////////////////////////////////////////////////
             void playerInteract(Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the player's attacks on the NPCs.
             ////////////////////////////////////////////////////////////////////////
             void playerAttack(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the state of each entity in the list.
             ////////////////////////////////////////////////////////////////////////
             void update(Game*, sf::Time&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Gives orders to the NPCs if they are waiting for any.
             ////////////////////////////////////////////////////////////////////////
             void makeOrdersToNPCs(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Calculates the FOV of the player.
             ////////////////////////////////////////////////////////////////////////
             void calculateFOV(sf::Vector2i origin, int range);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the level's starting point.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2i getStartingPoint() const { return m_startingPoint; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the level's ending point.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2i getEndingPoint() const { return m_endingPoint; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the level's size.
             ////////////////////////////////////////////////////////////////////////
             sf::Vector2i getSize() const { return m_size; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the level's list of tiles converted into integers.
             ////////////////////////////////////////////////////////////////////////
             int* getTiles() { return m_tilesAsInts; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the level's list of tiles.
             ////////////////////////////////////////////////////////////////////////
             Cell* getTilesAsCells() { return m_tiles; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the level from a file.
             ////////////////////////////////////////////////////////////////////////
             std::ifstream& operator<<(std::ifstream&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the level to a file.
             ////////////////////////////////////////////////////////////////////////
             std::ofstream& operator>>(std::ofstream&);

    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the tile map and the entities in the level's list.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reacts to a specific event. It can either do something with
             /// a given entity or just ignore it.
             ////////////////////////////////////////////////////////////////////////
     virtual void onNotify(Event, Entity*) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Spreads the randomly placed and sized rooms in the level.
             ////////////////////////////////////////////////////////////////////////
             void digRooms();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Carves a maze between the rooms in the level.
             ////////////////////////////////////////////////////////////////////////
             void fillWithMaze(int, int);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Connects all the rooms with other rooms or corridors placed
             /// next to them.
             ////////////////////////////////////////////////////////////////////////
             void connectRooms();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes the dead ends in the generated corridors.
             ////////////////////////////////////////////////////////////////////////
             void removeDeadEnds();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Spreads the randomly placed and chosen entities.
             ////////////////////////////////////////////////////////////////////////
             void placeEntities();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Generates the tile map.
             ////////////////////////////////////////////////////////////////////////
             void generateTileMap();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the given position is out of or on the border of the
             /// level.
             ////////////////////////////////////////////////////////////////////////
             bool isOnBorder(int, int);

             sf::VertexArray          m_tilemap;
             sf::Vector2i             m_size;
             sf::Vector2i             m_startingPoint;
             sf::Vector2i             m_endingPoint;

             int                      m_regions    [77*43];
             int                      m_tilesAsInts[77*43];
             Cell                     m_tiles      [77*43];
             ShadowMap                m_shadowMap;

             AIManager                m_AIManager;

             std::vector<Entity*>     m_entities;
             std::vector<NPC*>        m_npcs;
             std::vector<Item*>       m_items;
             
             std::vector<sf::IntRect> m_rooms;
             int                      m_regionCount;
             int                      m_levelNumber;
    };

}

#include "../Game.hpp"

#endif // LEVEL_HPP
