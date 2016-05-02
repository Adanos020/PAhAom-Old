/**
 * @file src/program/game/game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef game_hpp
#define game_hpp

#include <ctime>
#include <vector>

#include "../program.hpp"
#include "menus/menus.hpp"
#include "entities/player/player.hpp"
#include "entities/entities.hpp"

namespace rr {

    class MainMenu;
    class PauseMenu;
    class Inventory;
    class Attributes;
    class Quests;
    class GameMap;

/// Class for the HUD
    class HUD {
    private:
        Bar*  bHP;
        Bar*  bMP;
        Bar*  bXP;
        Slot* sCarryOn[5];
        Text* tXPlevel;
    public:
         HUD();
        ~HUD();

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Updates the HUD state
        void update      (Player*);

    /// Method drawing the HUD components
        void draw        (sf::RenderWindow&);
    };

/// Class for the tile map
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
        sf::Vector2f                   getStartingPoint() const { return startingPoint; }
        sf::Vector2f                   getEndingPoint  () const { return endingPoint  ; }
        std::vector<std::vector<Cell>> getTiles        () const { return tiles        ; }
    private:
        virtual void draw           (sf::RenderTarget& target, sf::RenderStates states) const;

        void         digRooms       ();
        void         fillWithMaze   (int, int);
        void         connectRooms   ();
        void         removeDeadEnds ();
        void         placeEntities  ();
        void         addEntity      (Entity*, sf::Vector2f position);
        void         generateTileMap();
        bool         isOnBorder     (int, int);

        sf::VertexArray tilemap;
        sf::Vector2i    size;
        sf::Vector2f    startingPoint;
        sf::Vector2f    endingPoint;

        std::vector<Entity*>           entities;
        std::vector<std::vector<Cell>> tiles;
        std::vector<sf::IntRect>       rooms;
        std::vector<std::vector<int>>  regions;
        int                            region_count;
    };

/// Class for the game
    class Game {
    private:
        sf::View             gameView;
        sf::View             mapView;

        MainMenu*            mainMenu;
        PauseMenu*           pauseMenu;
        Attributes*          attributes;
        Inventory*           inventory;
        Quests*              quests;
        GameMap*             gameMap;
        HUD*                 hud;
        std::vector<Level*>  level;
        Player*              player;

        bool                 started;
        bool                 paused;
        unsigned             levelNumber;

    /// Method for the keyboard controls
        void controls      (float);

    /// Method randomizing the disposable items' colors/symbols
        void randomizeItems();
    public:
         Game();
        ~Game();

    /// Method drawing the game components
        void draw        (sf::RenderWindow&);

    /// Method for handling the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&);

    /// Method drawing the game components
        void update      (float);

    /// Method starting the game or not, depending on the argument's value
        void start       (bool);

    /// Method pause the game or not, depending on the argument's value
        void pause       (bool);

    /// Method saving the game progress
        void save        ();

    /// Method loading the game progress
        bool load        ();

    /// Method the new game
        bool loadNewGame ();

    /// Method telling if the game is started
        bool isStarted   ();

    /// Method telling if the game is paused
        bool isPaused    ();
    };

}

#endif // game_h
