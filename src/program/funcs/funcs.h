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

    inline std::wstring atow(const std::string& str) {
        std::wstring out;
        std::transform(str.begin(), str.end(), std::back_inserter(out), [](char ch) -> wchar_t { return static_cast<wchar_t>(ch); });
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

    inline sf::String std8ToSf32(const std::string& str) {
        sf::String ret;
        sf::Uint32 c;

        auto it=str.begin();
        while (it!=str.end()) {
            it = sf::Utf8::decode(it,str.end(), c, 0u);
            if (c!=0u)
                ret+=c;
        }
        return ret;
    }

    inline std::string sf32toStd8(const sf::String& str) {
        std::string ret;
        char buf[5];

        for (auto it=str.begin(); it!=str.end(); ++it) {
            auto end = sf::Utf8::encode(*it, buf);
            *end = '\0';
            ret+=buf;
        }
        return ret;
    }

}

#endif // funcs_h
