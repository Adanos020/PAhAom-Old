/**
 * @file src/program/funcs/images.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef images_hpp
#define images_hpp

#include <SFML/Graphics.hpp>

namespace rr {

    inline void setIcon(sf::VertexArray& body, int layers, int icons[]) {
        body.resize(4*layers);
        body.setPrimitiveType(sf::Quads);

        for (int i=0; i<layers; i++) {
            int tu = icons[i]%16;
            int tv = icons[i]/16;

            body[4*i+0].texCoords =  sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
            body[4*i+1].texCoords =  sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
            body[4*i+2].texCoords =  sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
            body[4*i+3].texCoords =  sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
        }
    }

    inline void setIcon(sf::VertexArray& body, int icon) {
        body.resize(4);
        body.setPrimitiveType(sf::Quads);

        int hor = icon%16;
        int ver = icon/16;

        body[0].texCoords =  sf::Vector2f(  hor  *16+0.03125f,   ver  *16+0.03125f);
        body[1].texCoords =  sf::Vector2f((hor+1)*16-0.03125f,   ver  *16+0.03125f);
        body[2].texCoords =  sf::Vector2f((hor+1)*16-0.03125f, (ver+1)*16-0.03125f);
        body[3].texCoords =  sf::Vector2f(  hor  *16+0.03125f, (ver+1)*16-0.03125f);
    }

    inline void setColor(sf::VertexArray& body, int layer, sf::Color color) {
        for (int i=0; i<4; i++) {
            body[4*layer+i].color = color;
        }
    }

    inline void setColor(sf::VertexArray& body, sf::Color color) {
        for (unsigned i=0; i<body.getVertexCount(); i++) {
            body[i].color = color;
        }
    }

    inline void setGradient(sf::VertexArray& body, sf::Color colors[]) {
        body[0].color = colors[0];
        body[1].color = colors[1];
        body[2].color = colors[2];
        body[3].color = colors[3];
    }

    inline void setPosition(sf::VertexArray& body, sf::Vector2f pos) {
        body[1].position = pos+(body[1].position-body[0].position);
        body[2].position = pos+(body[2].position-body[0].position);
        body[3].position = pos+(body[3].position-body[0].position);
        body[0].position = pos;

        if (body.getVertexCount() > 4) {
            for (unsigned i=4; i<body.getVertexCount(); i++) {
                body[i].position = body[i%4].position;
            }
        }
    }

    inline void setSize(sf::VertexArray& body, sf::Vector2f siz) {
        body[1].position = body[0].position+sf::Vector2f(siz.x,     0);
        body[2].position = body[0].position+sf::Vector2f(siz.x, siz.y);
        body[3].position = body[0].position+sf::Vector2f(0    , siz.y);
    }

    inline void flipVertically(sf::VertexArray& body) {
        sf::Vector2f position_0 = body[0].position,
                     position_1 = body[1].position,
                     position_2 = body[2].position,
                     position_3 = body[3].position;

        body[0].position = position_3;
        body[1].position = position_2;
        body[2].position = position_1;
        body[3].position = position_0;
    }

    inline void flipHorizontally(sf::VertexArray& body) {
        sf::Vector2f position_0 = body[0].position,
                     position_1 = body[1].position,
                     position_2 = body[2].position,
                     position_3 = body[3].position;

        body[0].position = position_1;
        body[3].position = position_2;
        body[1].position = position_0;
        body[2].position = position_3;
    }

}

#endif // images_hpp
