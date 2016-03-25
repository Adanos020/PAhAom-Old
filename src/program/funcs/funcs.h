#ifndef funcs_h
#define funcs_h

#include <string>
#include <vector>
#include <sstream>

namespace rr {

    template<class Base, class T>
    inline bool instanceof(const T* ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

    inline std::string wtoa(const std::wstring& wide) {
        std::string out;
        std::transform(wide.begin(), wide.end(), std::back_inserter(out), [](wchar_t ch) -> char { return static_cast<char>(ch); });
        return out;
    }

    inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    inline std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

}

#endif // funcs_h
