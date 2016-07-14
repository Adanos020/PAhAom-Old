/**
 * @file src/main.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "program/program.hpp"

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

rr::Resources resources;
rr::Settings  settings;
rr::Subject   subject;
sf::Color     itemColors[9];
int           spellSymbols[12];

int main() {
    auto seed = time(0);
    srand(seed);

    auto p = new rr::Program(seed);

    delete p;
    return EXIT_SUCCESS;
}
