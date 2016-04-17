/**
 * @file src/program/game/menus/game_TileMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"

namespace rr {

    bool TileMap::load(sf::Vector2u tileSize, const int* tiles, sf::Vector2u mapSize) {
        // load the tileset texture
        if (!m_tileset.loadFromFile("data/graphics/tileset.png"))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(mapSize.x*mapSize.y*4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i=0; i<mapSize.x; ++i)
            for (unsigned int j=0; j<mapSize.y; ++j) {
                // get the current tile number
                int tileNumber = tiles[i+j*mapSize.x];

                // find its position in the tileset texture
                int tu = tileNumber%(m_tileset.getSize().x/tileSize.x);
                int tv = tileNumber/(m_tileset.getSize().x/tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i+j*mapSize.x)*4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i*tileSize.x*5    , j*tileSize.y*5);
                quad[1].position = sf::Vector2f((i+1)*tileSize.x*5, j*tileSize.y*5);
                quad[2].position = sf::Vector2f((i+1)*tileSize.x*5, (j+1)*tileSize.y*5);
                quad[3].position = sf::Vector2f(i*tileSize.x*5    , (j+1)*tileSize.y*5);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu*tileSize.x    , tv*tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu+1)*tileSize.x, tv*tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu+1)*tileSize.x, (tv+1)*tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu*tileSize.x    , (tv+1)*tileSize.y);
            }
            return true;
        }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();
        // apply the tileset texture
        states.texture = &m_tileset;
        // draw the vertex array
        target.draw(m_vertices, states);
    }

}
