/**
 * @file src/program/funcs/files.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef files_h
#define files_h

#include <fstream>

namespace rr {

/// Reads a bool variable from file
    inline void readFile(std::ifstream& f, bool& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a char from file
    inline void readFile(std::ifstream& f, char& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a double from file
    inline void readFile(std::ifstream& f, double& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a float from file
    inline void readFile(std::ifstream& f, float& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads an int from file
    inline void readFile(std::ifstream& f, int& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a long from file
    inline void readFile(std::ifstream& f, long& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a long long from file
    inline void readFile(std::ifstream& f, long long& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a long double from file
    inline void readFile(std::ifstream& f, long double& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads a short from file
    inline void readFile(std::ifstream& f, short& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

/// Reads an unsigned int from file
    inline void readFile(std::ifstream& f, unsigned& x) {
        std::string param;
        f >> x;
        if (f.fail()) {
            f.clear();
            f.sync();
            f >> param;
            throw ("Wrong data: " + param);
        }
    }

}

#endif // files_h
