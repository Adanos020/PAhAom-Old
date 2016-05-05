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
        void                           addEntity       (Entity*, sf::Vector2i position);
        void                           removeEntity    (unsigned index);

        std::vector<Entity*>           getEntities     () const { return entities_     ; }
        sf::Vector2i                   getStartingPoint() const { return startingPoint_; }
        sf::Vector2i                   getEndingPoint  () const { return endingPoint_  ; }
        std::vector<std::vector<Cell>> getTiles        () const { return tiles_        ; }
    private:
        virtual void draw           (sf::RenderTarget& target, sf::RenderStates states) const;

        void         digRooms       ();
        void         fillWithMaze   (int, int);
        void         connectRooms   ();
        void         removeDeadEnds ();
        void         placeEntities  ();
        void         generateTileMap();
        bool         isOnBorder     (int, int);

        sf::VertexArray tilemap_;
        sf::Vector2i    size_;
        sf::Vector2i    startingPoint_;
        sf::Vector2i    endingPoint_;

        std::vector<Entity*>           entities_;
        std::vector<std::vector<Cell>> tiles_;
        std::vector<sf::IntRect>       rooms_;
        std::vector<std::vector<int>>  regions_;
        int                            region_count_;
    };

}

#endif // level_hpp
