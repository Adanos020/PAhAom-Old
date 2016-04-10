/**
 * @file src/main.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program/program.hpp"
#include <cstdlib>
#include <ctime>
#include <map>
#include <SFML/Graphics.hpp>

rr::Dictionary dictionary;
rr::Resources  resources;
rr::Settings   settings;

int main() {
    srand(time(0));
    auto p = new rr::Program();

    delete p;
    return 0;
}
