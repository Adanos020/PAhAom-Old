/**
 * @file src/program/game/level.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef level_hpp
#define level_hpp

#include "../observer/observer.hpp"

namespace rr {

/// Class for the level
    class Level : public Observer, public sf::Drawable, public sf::Transformable {
    public:
         Level(int number);
        ~Level();

        enum Cell {
            CHASM,
            WALL,
            ROOM,
            CORRIDOR,
            ENTRANCE,
            OCCUPIED,
            EXIT
        };

        Mask masks_      [77*43];
        int  tilesAsInts_[77*43];

        virtual void         onNotify        (Event, Entity*) override;

        void                 generateWorld   ();
        void                 drawObjects     (sf::RenderWindow&) const;
        void                 addEntity       (Entity*            , sf::Vector2i position);
        void                 addEntity       (Entity*);
        void                 replaceEntity   (unsigned index     , Entity*);
        void                 removeEntity    (unsigned index);

        void                 calculateFOV    (sf::Vector2u origin, int range);

        std::vector<Entity*> getEntities     ()                  const { return entities_     ; }
        Mask*                getMasks        ()                        { return masks_        ; }
        sf::Vector2i         getStartingPoint()                  const { return startingPoint_; }
        sf::Vector2i         getEndingPoint  ()                  const { return endingPoint_  ; }
        int*                 getTiles        ()                        { return tilesAsInts_  ; }
        Cell*                getTilesAsCells ()                        { return tiles_        ; }

        std::ifstream& operator<<(std::ifstream&);
        std::ofstream& operator>>(std::ofstream&);
    private:
        virtual void         draw            (sf::RenderTarget& target, sf::RenderStates states) const;

        void                 digRooms        ();
        void                 fillWithMaze    (int, int);
        void                 connectRooms    ();
        void                 removeDeadEnds  ();
        void                 placeEntities   ();
        void                 generateTileMap ();
        bool                 isOnBorder      (int, int);

        sf::VertexArray          tilemap_;
        sf::Vector2i             size_;
        sf::Vector2i             startingPoint_;
        sf::Vector2i             endingPoint_;

        int                      regions_[77*43];
        Cell                     tiles_  [77*43];
        std::vector<Entity*>     entities_;
        std::vector<sf::IntRect> rooms_;
        int                      region_count_;
        int                      levelNumber_;
    };

}

#endif // level_hpp
