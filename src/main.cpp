/**
 * @file src/main.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include <SFML/Graphics.hpp>

#include "Program.hpp"
#include "program/Observer.hpp"

rr::Subject subject;
sf::Color   itemColors[9];
int         spellSymbols[12];

int main()
{
    auto p = new rr::Program();
    
    if (p->loadResources())
        p->runGame();
    else
    {
        delete p;
        return EXIT_FAILURE;
    }

    delete p;
    return EXIT_SUCCESS;
}
