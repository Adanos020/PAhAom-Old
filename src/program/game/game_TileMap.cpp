/**
 * @file src/program/game/menus/game_TileMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "game.hpp"

namespace rr {

    bool TileMap::load(sf::Vector2u tileSize, const int* tiles, sf::Vector2u mapSize) {
        if (!m_tileset.loadFromFile("data/graphics/tileset.png"))
            return false;

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(mapSize.x*mapSize.y*4);

        for (unsigned int i=0; i<mapSize.x; ++i) {
            for (unsigned int j=0; j<mapSize.y; ++j) {
                int tileNumber = tiles[i+j*mapSize.x];

                int tu = tileNumber%(m_tileset.getSize().x/tileSize.x);
                int tv = tileNumber/(m_tileset.getSize().x/tileSize.x);

                sf::Vertex* quad = &m_vertices[(i+j*mapSize.x)*4];

                quad[0].position = sf::Vector2f(  i  *tileSize.x*5,   j  *tileSize.y*5);
                quad[1].position = sf::Vector2f((i+1)*tileSize.x*5,   j  *tileSize.y*5);
                quad[2].position = sf::Vector2f((i+1)*tileSize.x*5, (j+1)*tileSize.y*5);
                quad[3].position = sf::Vector2f(  i  *tileSize.x*5, (j+1)*tileSize.y*5);

                quad[0].texCoords = sf::Vector2f(  tu  *tileSize.x+0.03125f,   tv  *tileSize.y+0.03125f);
                quad[1].texCoords = sf::Vector2f((tu+1)*tileSize.x-0.03125f,   tv  *tileSize.y+0.03125f);
                quad[2].texCoords = sf::Vector2f((tu+1)*tileSize.x-0.03125f, (tv+1)*tileSize.y-0.03125f);
                quad[3].texCoords = sf::Vector2f(  tu  *tileSize.x+0.03125f, (tv+1)*tileSize.y-0.03125f);
            }
        }
        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

}
