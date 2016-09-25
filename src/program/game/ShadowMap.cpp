/**
 * @file src/program/game/ShadowMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <iostream>

#include "../funcs/files.hpp"
#include "../Resources.hpp"

#include "ShadowMap.hpp"

namespace rr
{

    ShadowMap::ShadowMap(sf::Vector2i size) :
      m_size(size)
    {
        m_shadowImage.create(m_size.x*3, m_size.y*3, sf::Color::Black);

        m_shadowTexture.loadFromImage(m_shadowImage);
        m_shadowTexture.setSmooth(true);

        m_shadowSprite.resize(4);
        m_shadowSprite.setPrimitiveType(sf::Quads);

        m_shadowSprite[0].position  = sf::Vector2f(0        , 0        );
        m_shadowSprite[1].position  = sf::Vector2f(80*size.x, 0        );
        m_shadowSprite[2].position  = sf::Vector2f(80*size.x, 80*size.y);
        m_shadowSprite[3].position  = sf::Vector2f(0        , 80*size.y);

        m_shadowSprite[0].texCoords = sf::Vector2f(0       , 0       );
        m_shadowSprite[1].texCoords = sf::Vector2f(3*size.x, 0       );
        m_shadowSprite[2].texCoords = sf::Vector2f(3*size.x, 3*size.y);
        m_shadowSprite[3].texCoords = sf::Vector2f(0       , 3*size.y);

        for (int i = 0; i < m_size.x*m_size.y; ++i)
        {
            m_discovered[i] = false;
        }

        for (int i = 0; i < m_size.x*m_size.y*9; ++i)
        {
            m_cellIDs[i] = 0;
        }
    }

    bool
    ShadowMap::isFilled(int x, int y, unsigned char id) const
    {
        if (  x < 0 || x > m_size.x-1
           || y < 0 || y > m_size.y-1
            ) return false;

        int tx = 3*x, ty = 3*y;

        bool filled = true;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (m_cellIDs[tx+i + (ty+j)*m_size.x*3] == id)
                {
                    filled = false;
                    break;
                } 
            }
            if (!filled)
                break;
        }
        return filled;
    }

    void
    ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = &m_shadowTexture;
        target.draw(m_shadowSprite, states);
    }

    void
    ShadowMap::setLit(int x, int y)
    {
        m_discovered[x + y*m_size.x] = true;

        int tx = 3*x + 1, ty = 3*y + 1;

        m_cellIDs[tx + ty*m_size.x*3] = 2;
        m_lastlyLit.push_back(sf::Vector2i(tx, ty));

        if (x < m_size.x-1)
        {
            if (y > 0)
            {
                if (m_cellIDs[tx+3 + (ty-3)*m_size.x*3] == 2) // TOP RIGHT
                {
                    m_cellIDs[tx+1 + (ty-1)*m_size.x*3] =  2;
                    m_cellIDs[tx+1 + ( ty )*m_size.x*3] =  2;
                    m_cellIDs[ tx  + (ty-1)*m_size.x*3] =  2;

                    m_cellIDs[tx+2 + (ty-2)*m_size.x*3] =  2;

                    m_lastlyLit.push_back(sf::Vector2i(tx+1, ty-1));
                    m_lastlyLit.push_back(sf::Vector2i(tx+1,  ty ));
                    m_lastlyLit.push_back(sf::Vector2i( tx , ty-1));
                    m_lastlyLit.push_back(sf::Vector2i(tx+2, ty-2));
                }
            }

            if (y < m_size.y-1)
            {
                if (m_cellIDs[tx+3 + (ty+3)*m_size.x*3] == 2) // BOTTOM RIGHT
                {
                    m_cellIDs[tx+1 + (ty+1)*m_size.x*3] =  2;
                    m_cellIDs[tx+1 + ( ty )*m_size.x*3] =  2;
                    m_cellIDs[ tx  + (ty+1)*m_size.x*3] =  2;

                    m_cellIDs[tx+2 + (ty+2)*m_size.x*3] =  2;

                    m_lastlyLit.push_back(sf::Vector2i(tx+1, ty+1));
                    m_lastlyLit.push_back(sf::Vector2i(tx+1,  ty ));
                    m_lastlyLit.push_back(sf::Vector2i( tx , ty+1));
                    m_lastlyLit.push_back(sf::Vector2i(tx+2, ty+2));
                }
            }

            if (m_cellIDs[tx+3 + ty*m_size.x*3] == 2) // RIGHT
            {
                m_cellIDs[tx+1 + ty*m_size.x*3] =  2;
                m_cellIDs[tx+2 + ty*m_size.x*3] =  2;

                m_lastlyLit.push_back(sf::Vector2i(tx+1, ty));
                m_lastlyLit.push_back(sf::Vector2i(tx+2, ty));
            }
        }

        if (x > 0)
        {
            if (y > 0)
            {
                if (m_cellIDs[tx-3 + (ty-3)*m_size.x*3] == 2) // TOP LEFT
                {
                    m_cellIDs[tx-1 + (ty-1)*m_size.x*3] =  2;
                    m_cellIDs[tx-1 + ( ty )*m_size.x*3] =  2;
                    m_cellIDs[ tx  + (ty-1)*m_size.x*3] =  2;

                    m_cellIDs[tx-2 + (ty-2)*m_size.x*3] =  2;

                    m_lastlyLit.push_back(sf::Vector2i(tx-1, ty-1));
                    m_lastlyLit.push_back(sf::Vector2i(tx-1,  ty ));
                    m_lastlyLit.push_back(sf::Vector2i( tx , ty-1));
                    m_lastlyLit.push_back(sf::Vector2i(tx-2, ty-2));
                }
            }

            if (y < m_size.y-1)
            {
                if (m_cellIDs[tx-3 + (ty+3)*m_size.x*3] == 2) // BOTTOM LEFT
                {
                    m_cellIDs[tx-1 + (ty+1)*m_size.x*3] =  2;
                    m_cellIDs[tx-1 + ( ty )*m_size.x*3] =  2;
                    m_cellIDs[ tx  + (ty+1)*m_size.x*3] =  2;

                    m_cellIDs[tx-2 + (ty+2)*m_size.x*3] =  2;

                    m_lastlyLit.push_back(sf::Vector2i(tx-1, ty+1));
                    m_lastlyLit.push_back(sf::Vector2i(tx-1,  ty ));
                    m_lastlyLit.push_back(sf::Vector2i( tx , ty+1));
                    m_lastlyLit.push_back(sf::Vector2i(tx-2, ty+2));
                }
            }

            if (m_cellIDs[tx-3 + ty*m_size.x*3] == 2) // LEFT
            {
                m_cellIDs[tx-1 + ty*m_size.x*3] =  2;
                m_cellIDs[tx-2 + ty*m_size.x*3] =  2;

                m_lastlyLit.push_back(sf::Vector2i(tx-1, ty));
                m_lastlyLit.push_back(sf::Vector2i(tx-2, ty));
            }
        }

        if (y > 0)
        {
            if (m_cellIDs[tx + (ty-3)*m_size.x*3] == 2) // TOP
            {
                m_cellIDs[tx + (ty-1)*m_size.x*3] =  2;
                m_cellIDs[tx + (ty-2)*m_size.x*3] =  2;

                m_lastlyLit.push_back(sf::Vector2i(tx, ty-1));
                m_lastlyLit.push_back(sf::Vector2i(tx, ty-2));
            }
        }

        if (y < m_size.y-1)
        {
            if (m_cellIDs[tx + (ty+3)*m_size.x*3] == 2) // BOTTOM
            {
                m_cellIDs[tx + (ty+1)*m_size.x*3] =  2;
                m_cellIDs[tx + (ty+2)*m_size.x*3] =  2;

                m_lastlyLit.push_back(sf::Vector2i(tx, ty+1));
                m_lastlyLit.push_back(sf::Vector2i(tx, ty+2));
            }
        }

// CORRECTING THE FINAL SHAPE OF THE SHADOWS

        if (isFilled(x, y, 2))
            return;

        if (  isFilled(x-1, y-1, 2)
           && isFilled( x , y-1, 2)
           && isFilled(x+1, y-1, 2)
           && isFilled(x+1,  y , 2)
           && isFilled(x+1, y+1, 2)
           && isFilled( x , y+1, 2)
           && isFilled(x-1, y+1, 2)
           && isFilled(x-1,  y , 2)
            ) return;

        std::vector<unsigned char> neighbors;
        if (x > 0)
        {
            if (y > 0)          neighbors.push_back(1);
            if (y < m_size.y-1) neighbors.push_back(7);

            neighbors.push_back(8);
        }

        if (x < m_size.x-1)
        {
            if (y > 0)         neighbors.push_back(3);

            if (y < m_size.y-1) neighbors.push_back(5);

            neighbors.push_back(4);
        }
        
        if (y > 0)         neighbors.push_back(2);

        if (y < m_size.y-1) neighbors.push_back(6);

        for (unsigned i = 0; i < neighbors.size(); ++i)
        {
            switch (neighbors[i])
            { // here we switch between the central cell and the cells next to it
                case 0: tx = 3*( x ) + 1; ty = 3*( y ) + 1; break;  // CENTER
                case 1: tx = 3*(x-1) + 1; ty = 3*(y-1) + 1; break;  // TOP LEFT
                case 2: tx = 3*( x ) + 1; ty = 3*(y-1) + 1; break;  // TOP
                case 3: tx = 3*(x+1) + 1; ty = 3*(y-1) + 1; break;  // TOP RIGHT
                case 4: tx = 3*(x+1) + 1; ty = 3*( y ) + 1; break;  // RIGHT
                case 5: tx = 3*(x+1) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM RIGHT
                case 6: tx = 3*( x ) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM
                case 7: tx = 3*(x-1) + 1; ty = 3*(y+1) + 1; break;  // BOTTOM LEFT
                case 8: tx = 3*(x-1) + 1; ty = 3*( y ) + 1; break;  // LEFT
            }

            if (  m_cellIDs[tx-1 + ( ty )*m_size.x*3] == 2            // IF LEFT
               && m_cellIDs[ tx  + (ty-1)*m_size.x*3] == 2)           // AND TOP ARE TRANSPARENT
            {
                  m_cellIDs[tx-1 + (ty-1)*m_size.x*3] =  2;           // THEN SET TOP LEFT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx-1, ty-1));
            }

            if (  m_cellIDs[tx-1 + ( ty )*m_size.x*3] == 2            // IF LEFT
               && m_cellIDs[ tx  + (ty+1)*m_size.x*3] == 2)           // AND BOTTOM ARE TRANSPARENT
            {
                  m_cellIDs[tx-1 + (ty+1)*m_size.x*3] =  2;           // THEN SET BOTTOM LEFT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx-1, ty+1));
            }

            if (  m_cellIDs[tx+1 + ( ty )*m_size.x*3] == 2            // IF RIGHT
               && m_cellIDs[ tx  + (ty-1)*m_size.x*3] == 2)           // AND TOP ARE TRANSPARENT
            {
                  m_cellIDs[tx+1 + (ty-1)*m_size.x*3] =  2;           // THEN SET TOP RIGHT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx+1, ty-1));
            }

            if (  m_cellIDs[tx+1 + ( ty )*m_size.x*3] == 2            // IF RIGHT
               && m_cellIDs[ tx  + (ty+1)*m_size.x*3] == 2)           // AND BOTTOM ARE TRANSPARENT
            {
                  m_cellIDs[tx+1 + (ty+1)*m_size.x*3] =  2;           // THEN SET BOTTOM RIGHT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx+1, ty+1));
            }

            if (  m_cellIDs[tx-1 + (ty-1)*m_size.x*3] == 2            // IF TOP LEFT
               && m_cellIDs[tx-1 + (ty+1)*m_size.x*3] == 2)           // AND BOTTOM LEFT ARE TRANSPARENT
            {
                  m_cellIDs[tx-1 + ( ty )*m_size.x*3] =  2;           // THEN SET LEFT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx-1, ty));
            }

            if (  m_cellIDs[tx-1 + (ty-1)*m_size.x*3] == 2            // IF TOP LEFT
               && m_cellIDs[tx+1 + (ty-1)*m_size.x*3] == 2)           // AND TOP RIGHT ARE TRANSPARENT
            {
                  m_cellIDs[ tx  + (ty-1)*m_size.x*3] =  2;           // THEN SET TOP TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx, ty-1));
            }

            if (  m_cellIDs[tx+1 + (ty+1)*m_size.x*3] == 2            // IF BOTTOM RIGHT
               && m_cellIDs[tx+1 + (ty-1)*m_size.x*3] == 2)           // AND TOP RIGHT ARE TRANSPARENT
            {
                  m_cellIDs[tx+1 + ( ty )*m_size.x*3] =  2;           // THEN SET RIGHT TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx+1, ty));
            }

            if (  m_cellIDs[tx+1 + (ty+1)*m_size.x*3] == 2            // IF BOTTOM RIGHT
               && m_cellIDs[tx-1 + (ty+1)*m_size.x*3] == 2)           // AND BOTTOM LEFT ARE TRANSPARENT
            {
                  m_cellIDs[ tx  + (ty+1)*m_size.x*3] =  2;           // THEN SET BOTTOM TO TRANSPARENT
                  m_lastlyLit.push_back(sf::Vector2i(tx, ty+1));
            }
        }
    }

    void
    ShadowMap::darken()
    {
        for (unsigned i = 0; i < m_lastlyLit.size(); ++i)
        {
            m_cellIDs[m_lastlyLit[i].x + m_lastlyLit[i].y*m_size.x*3] = 1;
        }
        m_lastlyLit.clear();
    }

    void
    ShadowMap::update()
    {
        for (int x=0; x<3*m_size.x; ++x)
        {
            for (int y=0; y<3*m_size.y; ++y)
            {
                if      (m_cellIDs[x + y*3*m_size.x] == 1) m_shadowImage.setPixel(x, y, sf::Color(0, 0, 0, 200));
                else if (m_cellIDs[x + y*3*m_size.x] == 2) m_shadowImage.setPixel(x, y, sf::Color(0, 0, 0,   0));
            }
        }

        m_shadowTexture.update(m_shadowImage);
    }

    std::ifstream&
    ShadowMap::operator<<(std::ifstream& file)
    {
        try
        {
            for (int x = 0; x < m_size.x; ++x)
            {
                for (int y = 0; y < m_size.y; ++y)
                {
                    readFile <bool> (file, m_discovered[x + y*m_size.x]);
                    if (m_discovered[x + y*m_size.x])
                        setLit(x, y);
                }
            }
        }
        catch (std::invalid_argument ex)
        {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream&
    ShadowMap::operator>>(std::ofstream& file)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            for (int y = 0; y < m_size.y; ++y)
            {
                file << m_discovered[x + y*m_size.x] << ' ';
            }
            file << '\n';
        }

        return file;
    }

}
