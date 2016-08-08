/**
 * @file src/program/game/level/Level.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>

#include "../../observer/Observer.hpp"

#include "../Game.hpp"

#include "ShadowMap.hpp"
#include "../entity/Player.hpp"

namespace sf {
    typedef Rect<unsigned> UintRect;
}

namespace rr {

/// Class for the level
    class Level : public Observer, public sf::Drawable, public sf::Transformable {
    public:  Level(int number);
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
 
             virtual void         onNotify        (Event         , Entity*) override;
 
             void                 generateWorld   ();

             void                 addEntity       (Entity*       , sf::Vector2u position);
             void                 addEntity       (Entity*);
             void                 playerInteract  (Game*);
             void                 playerAttack    (Player*);
             void                 update          (Game*, sf::Time);
 
             void                 calculateFOV    (sf::Vector2u origin, int range);

             sf::Vector2u         getStartingPoint()                  const { return startingPoint_; }
             sf::Vector2u         getEndingPoint  ()                  const { return endingPoint_  ; }
             int*                 getTiles        ()                        { return tilesAsInts_  ; }
             Cell*                getTilesAsCells ()                        { return tiles_        ; }

             std::ifstream&       operator<<      (std::ifstream&);
             std::ofstream&       operator>>      (std::ofstream&);
    
    private: virtual void         draw            (sf::RenderTarget& target, sf::RenderStates states) const;
     
             void                 digRooms        ();
             void                 fillWithMaze    (unsigned, unsigned);
             void                 connectRooms    ();
             void                 removeDeadEnds  ();
             void                 placeEntities   ();
             void                 generateTileMap ();
             bool                 isOnBorder      (unsigned, unsigned);
         
             sf::VertexArray          tilemap_;
             sf::Vector2u             size_;
             sf::Vector2u             startingPoint_;
             sf::Vector2u             endingPoint_;
         
             int                      regions_    [77*43];
             int                      tilesAsInts_[77*43];
             Cell                     tiles_      [77*43];
             ShadowMap*               shadowMap_;
             std::list<Entity*>       entities_;
             std::vector<sf::UintRect>rooms_;
             int                      region_count_;
             int                      levelNumber_;
    };

}

#endif // LEVEL_HPP
