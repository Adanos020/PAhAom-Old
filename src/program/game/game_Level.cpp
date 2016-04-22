/**
 * @file src/program/game/menus/game_Level.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"
#include "../program.hpp"
#include "../funcs/files.hpp"
#include "../funcs/items.hpp"

extern rr::Resources resources;

namespace rr {

    Level::Level(sf::Vector2i levelSize) {
        size = levelSize;
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(size.x*size.y*4);

        grid.setPrimitiveType(sf::Points);
        grid.resize(size.x*size.y);
    }

    Level::~Level() {
        entities.clear();
    }

    void Level::addEntity(Entity* e, sf::Vector2f position) {
        if (e != nullptr) {
            entities.push_back(e);
            entities.back()->setPosition(position);
        }
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &resources.texture.tileset;
        target.draw(m_vertices, states);
    }

    void Level::drawObjects(sf::RenderWindow& rw) const {
        for (auto x : entities)
            x->draw(rw);
    }

    int* Level::genDirections(int num) {
        int* directions = new int[num];
        for (int i=0; i<num; i++) {
            directions[i] = rand()%4+1;
        }
        return directions;
    }

    void Level::mazeDigger(int** maze, int r, int c) {
     // at this point we generate an array of random directions
        int number = rand()%100+100;
        int* directions = genDirections(number);
     // and now let's start digging
        for (int i = 0; i<number; i++) {
            switch(directions[i]) {
            case 1:
                if (r-2 <= 0)
                    continue;
                if (maze[r-2][c] != 2) {
                    maze[r-2][c] = 2;
                    maze[r-1][c] = 2;
                    mazeDigger(maze, r-2, c);
                }
                break;
            case 2:
                if (c+2 >= size.y-1)
                    continue;
                if (maze[r][c+2] != 2) {
                    maze[r][c+2]  = 2;
                    maze[r][c+1]  = 2;
                    mazeDigger(maze, r, c+2);
                }
                break;
            case 3:
                if (r+2 >= size.x-1)
                    continue;
                if (maze[r+2][c] != 2) {
                    maze[r+2][c]  = 2;
                    maze[r+1][c]  = 2;
                    mazeDigger(maze, r+2, c);
                }
                break;
            case 4:
                if (c-2 <= 0)
                    continue;
                if (maze[r][c-2] != 2) {
                    maze[r][c-2]  = 2;
                    maze[r][c-1]  = 2;
                    mazeDigger(maze, r, c-2);
                }
                break;
            }
        }
    }

    void Level::generateWorld() {
        /* generate the tile map */ {
         // GENERATING A MAZE
         // first we create an 2-dimensional array filled with 1's representing a wall
            int** tiles = new int*[size.x];
            for (int i=0; i<size.x; i++)
                tiles[i] = new int[size.y];

            for (int i=0; i<size.x; i++)
                for (int j=0; j<size.y; j++)
                    tiles[i][j] = 1;
         // then we pick a random cell with an odd number to be our starting point
            int row = rand()%((int)size.y/2)*2+1;
            int col = rand()%((int)size.x/2)*2+1;
            tiles[row][col] = 2;
         // now this point we start digging a maze with a recursive method
            mazeDigger(tiles, row, col);

         // GENERATING A GRID
            for (int i=0; i<size.x; i++) {
                for (int j=0; j<size.y; j++) {
                    int cell = i+j*size.x;
                    grid[cell].position = sf::Vector2f(i*80, j*80);
                    switch (tiles[i][j]) {
                         // giving the grid points a color to distinguish whether a cell is a wall/floor/chasm
                    case 0: grid[cell].color = sf::Color::Black; break; // black cell means there is a chasm
                    case 1: grid[cell].color = sf::Color::White; break; // white stands for a wall
                    case 2: grid[cell].color = sf::Color::Green; break; // and green represents the floor
                    }
                }
            }

         // TURNING A MAZE INTO A TILE MAP
            for (int i=0; i<size.x; ++i) {
                for (int j=0; j<size.y; ++j) {
                    int tileNumber;

                 // assigning an appropriate tile number to a given cell
                    switch (tiles[i][j]) {
                 // chasm
                    case 0: tileNumber = 0 ; break;
                 // wall
                    case 1:
                        tileNumber = rand()%14+2;
                        enum Neighbour {
                            NONE,
                            TOP, BOTTOM, LEFT, RIGHT,
                            TOP_BOTTOM, TOP_LEFT, TOP_RIGHT, LEFT_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                            NO_TOP, NO_RIGHT, NO_LEFT, NO_BOTTOM,
                            ALL
                        };
                        if ((i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] == 1) && (j>0 && tiles[i][j-1] == 1) && (j<size.y-1 && tiles[i][j+1] == 1))
                            tileNumber += Neighbour::ALL*16;

                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::NO_TOP*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::NO_BOTTOM*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::NO_LEFT*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::NO_RIGHT*16;

                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::LEFT_RIGHT*16;
                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::BOTTOM_RIGHT*16;
                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::BOTTOM_LEFT*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::TOP_BOTTOM*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::TOP_RIGHT*16;
                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::TOP_LEFT*16;

                        else if ((j>0 && tiles[i][j-1] != 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::TOP*16;
                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] != 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::BOTTOM*16;
                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] != 1) && (i<size.x-1 && tiles[i+1][j] == 1))
                            tileNumber += Neighbour::LEFT*16;
                        else if ((j>0 && tiles[i][j-1] == 1) && (j<size.x-1 && tiles[i][j+1] == 1) && (i>0 && tiles[i-1][j] == 1) && (i<size.x-1 && tiles[i+1][j] != 1))
                            tileNumber += Neighbour::RIGHT*16;

                        break;
                 // floor
                    case 2: tileNumber = 32; break;
                    }

                    int tu = tileNumber%(resources.texture.tileset.getSize().x/16);
                    int tv = tileNumber/(resources.texture.tileset.getSize().y/16);

                    sf::Vertex* quad = &m_vertices[(i+j*size.x)*4];

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

        #if 1
        /* generate the objects */ {
         // here we generate the items
            for (int i=0; i<rand()%10; i++) {
                while (true) {
                    int x=rand()%(size.x*size.y);
                 // now we use the cell's color to distinguish which type of tile is in a randomised cell
                 // - if the cell is green (floor) and not cyan (occupied) then you can place an item on it
                    if (grid[x].color == sf::Color::Green && grid[x].color != sf::Color::Cyan) {
                        addEntity(getItemFromID(100 + (rand()%3)*10 + rand()%9, 1), grid[x].position);
                        grid[x].color = sf::Color::Cyan; // cyan means that the cell is occupied by an object
                        break;
                    }
                }
            }
         // here we generate the chests
            for (int i=0; i<rand()%5; i++) {
                while (true) {
                    int x=rand()%(size.x*size.y);
                    // just doing the same checking as in the item generating section
                    if (grid[x].color == sf::Color::Green && grid[x].color != sf::Color::Cyan) {
                        // here we choose randomly whether the chest has to be the special (probability = 5%) or the regular one (p = 95%)
                        addEntity(new Chest((rand()%20)?Chest::REGULAR:Chest::SPECIAL,
                                            getItemFromID(100+(rand()%3)*10+rand()%9, 1)), grid[x].position);
                        grid[x].color = sf::Color::Cyan;
                        break;
                    }
                }
            }
         // here we generate the cash
            for (int i=0; i<15; i++) {
                while (true) {
                    int x=rand()%(size.x*size.y);
                    // same story here
                    if (grid[x].color == sf::Color::Green && grid[x].color != sf::Color::Cyan) {
                        // here we choose randomly the type of a coin
                        addEntity(getItemFromID(rand()%3+1, rand()%100), grid[x].position);
                        grid[x].color = sf::Color::Cyan;
                        break;
                    }
                }
            }
        }
        #endif // 0
    }

    bool Level::loadFromFile(const char*) {
        return true;
    }

}
