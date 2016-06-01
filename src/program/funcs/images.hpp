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

    inline void setGradient(sf::VertexArray& body, sf::Color colors[], int vertices[]) {
        body[vertices[0]].color = colors[0];
        body[vertices[1]].color = colors[1];
        body[vertices[2]].color = colors[2];
        body[vertices[3]].color = colors[3];
    }

}

#endif // images_hpp
