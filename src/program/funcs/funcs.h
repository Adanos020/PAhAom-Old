#ifndef funcs_h
#define funcs_h

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

}

#endif // funcs_h
