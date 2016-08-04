/**
 * @file src/program/game/shadowmap/ShadowMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../funcs/files.hpp"
#include "../../Resources.hpp"

#include "ShadowMap.hpp"

namespace rr {

    ShadowMap::ShadowMap(sf::Vector2i size) :
      size_(size)
    {
        shadows_.setPrimitiveType(sf::Quads);
        shadows_.resize(size.x*size.y*4);
        
        for (int x=0; x<size.x; ++x) {
            for (int y=0; y<size.y; ++y) {
                int index = (x + y*size.x)*4;
                
                shadows_[index + 0].position = sf::Vector2f(  x * 80,   y * 80);
                shadows_[index + 1].position = sf::Vector2f((x+1)*80,   y * 80);
                shadows_[index + 2].position = sf::Vector2f((x+1)*80, (y+1)*80);
                shadows_[index + 3].position = sf::Vector2f(  x * 80, (y+1)*80);
            }
        }

        for (int i=0; i<size.x*size.y; ++i) {
            discovered_[i] = false;
        }
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (false && sf::Shader::isAvailable()) {
            //Resources::shader.shadowSmoothener.setParameter("position", 0.f, 0.5f, 0.f);
            //Resources::shader.shadowSmoothener.setParameter("color", 0.f, 0.f, 0.f);

            states.shader = &Resources::shader.shadowSmoothener;
        }
        target.draw(shadows_, states);
    }

    void ShadowMap::setLit(int x, int y) {
        int index = (x + size_.x*y)*4;

        shadows_[index + 0].color = sf::Color::Transparent;
        shadows_[index + 1].color = sf::Color::Transparent;
        shadows_[index + 2].color = sf::Color::Transparent;
        shadows_[index + 3].color = sf::Color::Transparent;

        discovered_[index/4] = true;
    }

    void ShadowMap::darken() {
        int index = 0;
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                index = (x + y*size_.x)*4;
                if (discovered_[index/4]) {
                    shadows_[index + 0].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 1].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 2].color = sf::Color(0, 0, 0, 200);
                    shadows_[index + 3].color = sf::Color(0, 0, 0, 200);
                }
                else {
                    shadows_[index + 0].color = sf::Color::Black;
                    shadows_[index + 1].color = sf::Color::Black;
                    shadows_[index + 2].color = sf::Color::Black;
                    shadows_[index + 3].color = sf::Color::Black;
                }
            }
        }
    }

    std::ifstream& ShadowMap::operator<<(std::ifstream& file) {
        try {
            for (int x=0; x<size_.x; ++x) {
                for (int y=0; y<size_.y; ++y) {
                    readFile <bool> (file, discovered_[x + y*size_.x]);
                }
            }
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream& ShadowMap::operator>>(std::ofstream& file) {
        for (int x=0; x<size_.x; ++x) {
            for (int y=0; y<size_.y; ++y) {
                file << discovered_[x + y*size_.x] << ' ';
            }
            file << '\n';
        }

        return file;
    }

}
