#ifndef files_h
#define files_h

#include <fstream>

namespace rr {

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
