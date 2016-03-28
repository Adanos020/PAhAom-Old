/**
 * @file src/program/Settings.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "program.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

namespace rr {

    void Settings::print() {
        std::cout << "===PARAMETER===" << std::setw(40) << "======VALUE======\n";
        std::cout << "width"       << std::setw(32+std::to_string(resolution.x).size())
                                   << resolution.x << '\n';
        std::cout << "height"      << std::setw(31+std::to_string(resolution.y).size())
                                   << resolution.y << '\n';
        std::cout << "fullscreen"  << std::setw(27+std::to_string(fullscreen).size())
                                   << fullscreen << '\n';
        std::cout << "vsync"       << std::setw(32+std::to_string(vsync).size())
                                   << vsync << '\n';
        std::cout << "lang"        << std::setw(34+language.size())
                                   << language+"\n";
        std::cout << "antialiasing"<< std::setw(25+std::to_string(csettings.antialiasingLevel).size())
                                   << csettings.antialiasingLevel << '\n';
        std::cout << "depthbits"   << std::setw(28+std::to_string(csettings.depthBits).size())
                                   << csettings.depthBits << '\n';
        std::cout << "stencilbits" << std::setw(26+std::to_string(csettings.stencilBits).size())
                                   << csettings.stencilBits << '\n';
    }

    void Settings::save() {
        puts(">Saving the settings...");

        std::ofstream oconfig("config.cfg");
        oconfig.clear();

        oconfig << ";--------------;\n";
        oconfig << ";video settings;\n";
        oconfig << ";----screen----;\n";
        oconfig << "width:\t\t"+std::to_string(resolution.x)+"\n";
        oconfig << "height:\t\t"+std::to_string(resolution.y)+"\n";
        oconfig << "fullscreen:\t"+std::to_string(fullscreen)+"\n";
        oconfig << "vsync:\t\t"+std::to_string(vsync)+"\n";
        oconfig << "lang:\t\t"+language+"\n";
        oconfig << ";---graphics---;\n";
        oconfig << "antialiasing:\t"+std::to_string(csettings.antialiasingLevel)+"\n";
        oconfig << "depthbits:\t"+std::to_string(csettings.depthBits)+"\n";
        oconfig << "stencilbits:\t"+std::to_string(csettings.stencilBits)+"\n";
        oconfig << ";--------------;";

        oconfig.close();
    }

}
