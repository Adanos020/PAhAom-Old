#include "program/program.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

std::map<std::string, std::wstring> dictionary;
sf::Font pixelFont;

int main() {
    srand(time(0));
    auto p = new rr::Program();

    delete p;
    return 0;
}
