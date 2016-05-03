/**
 * @file src/program/game/level.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef level_hpp
#define level_hpp

#include "entities/entities.hpp"

namespace rr {

/// Class for the level
    class Level : public sf::Drawable, public sf::Transformable {
    public:
         Level();
        ~Level();

        enum Cell {
            CHASM,
            WALL,
            ROOM,
            CORRIDOR,
            ENTRANCE,
            OCCUPIED
        };

        void                           generateWorld   ();
        bool                           loadFromFile    (const char* pathToFolder);
        void                           drawObjects     (sf::RenderWindow&) const;

        std::vector<Entity*>           getEntities     () const { return entities     ; }
        sf::Vector2i                   getStartingPoint() const { return startingPoint; }
        sf::Vector2i                   getEndingPoint  () const { return endingPoint  ; }
        std::vector<std::vector<Cell>> getTiles        () const { return tiles        ; }
    private:
        virtual void draw           (sf::RenderTarget& target, sf::RenderStates states) const;

        void         digRooms       ();
        void         fillWithMaze   (int, int);
        void         connectRooms   ();
        void         removeDeadEnds ();
        void         placeEntities  ();
        void         addEntity      (Entity*, sf::Vector2i position);
        void         generateTileMap();
        bool         isOnBorder     (int, int);

        sf::VertexArray tilemap;
        sf::Vector2i    size;
        sf::Vector2i    startingPoint;
        sf::Vector2i    endingPoint;

        std::vector<Entity*>           entities;
        std::vector<std::vector<Cell>> tiles;
        std::vector<sf::IntRect>       rooms;
        std::vector<std::vector<int>>  regions;
        int                            region_count;
    };

}

#endif // level_hpp
