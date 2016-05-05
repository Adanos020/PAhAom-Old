/**
 * @file src/program/funcs/keys.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef keys_hpp
#define keys_hpp

#include <SFML/Window/Keyboard.hpp>

namespace rr {

/// Returns a key name from a key code
    inline sf::String getKeyName(sf::Keyboard::Key keyCode) {
        switch (keyCode) {
        case sf::Keyboard::A:         return "A";
        case sf::Keyboard::B:         return "B";
        case sf::Keyboard::C:         return "C";
        case sf::Keyboard::D:         return "D";
        case sf::Keyboard::E:         return "E";
        case sf::Keyboard::F:         return "F";
        case sf::Keyboard::G:         return "G";
        case sf::Keyboard::H:         return "H";
        case sf::Keyboard::I:         return "I";
        case sf::Keyboard::J:         return "J";
        case sf::Keyboard::K:         return "K";
        case sf::Keyboard::L:         return "L";
        case sf::Keyboard::M:         return "M";
        case sf::Keyboard::N:         return "N";
        case sf::Keyboard::O:         return "O";
        case sf::Keyboard::P:         return "P";
        case sf::Keyboard::Q:         return "Q";
        case sf::Keyboard::R:         return "R";
        case sf::Keyboard::S:         return "S";
        case sf::Keyboard::T:         return "T";
        case sf::Keyboard::U:         return "U";
        case sf::Keyboard::V:         return "V";
        case sf::Keyboard::W:         return "W";
        case sf::Keyboard::X:         return "X";
        case sf::Keyboard::Y:         return "Y";
        case sf::Keyboard::Z:         return "Z";
        case sf::Keyboard::Num0:      return "0";
        case sf::Keyboard::Num1:      return "1";
        case sf::Keyboard::Num2:      return "2";
        case sf::Keyboard::Num3:      return "3";
        case sf::Keyboard::Num4:      return "4";
        case sf::Keyboard::Num5:      return "5";
        case sf::Keyboard::Num6:      return "6";
        case sf::Keyboard::Num7:      return "7";
        case sf::Keyboard::Num8:      return "8";
        case sf::Keyboard::Num9:      return "9";
        case sf::Keyboard::Escape:    return "Esc";
        case sf::Keyboard::LControl:  return L"←Ctrl";
        case sf::Keyboard::LShift:    return L"←Shift";
        case sf::Keyboard::LAlt:      return L"←Alt";
        case sf::Keyboard::LSystem:   return L"←Sys";
        case sf::Keyboard::RControl:  return L"Ctrl→";
        case sf::Keyboard::RShift:    return L"Shift→";
        case sf::Keyboard::RAlt:      return L"Alt→";
        case sf::Keyboard::RSystem:   return L"Sys→";
        case sf::Keyboard::Menu:      return "Menu";
        case sf::Keyboard::LBracket:  return "[";
        case sf::Keyboard::RBracket:  return "]";
        case sf::Keyboard::SemiColon: return ";";
        case sf::Keyboard::Comma:     return ",";
        case sf::Keyboard::Period:    return ".";
        case sf::Keyboard::Quote:     return "'";
        case sf::Keyboard::Slash:     return "/";
        case sf::Keyboard::BackSlash: return "\\";
        case sf::Keyboard::Tilde:     return "`";
        case sf::Keyboard::Equal:     return "=";
        case sf::Keyboard::Dash:      return "-";
        case sf::Keyboard::Space:     return "Space";
        case sf::Keyboard::Return:    return "Return";
        case sf::Keyboard::BackSpace: return L"←B";
        case sf::Keyboard::Tab:       return "Tab";
        case sf::Keyboard::PageUp:    return L"Pg↑";
        case sf::Keyboard::PageDown:  return L"Pg↓";
        case sf::Keyboard::End:       return "End";
        case sf::Keyboard::Home:      return "Home";
        case sf::Keyboard::Insert:    return "Insert";
        case sf::Keyboard::Delete:    return "Delete";
        case sf::Keyboard::Add:       return "+";
        case sf::Keyboard::Subtract:  return L"–";
        case sf::Keyboard::Multiply:  return L"×";
        case sf::Keyboard::Divide:    return L"÷";
        case sf::Keyboard::Left:      return L"←";
        case sf::Keyboard::Right:     return L"→";
        case sf::Keyboard::Up:        return L"↑";
        case sf::Keyboard::Down:      return L"↓";
        case sf::Keyboard::Numpad0:   return "Np0";
        case sf::Keyboard::Numpad1:   return "Np1";
        case sf::Keyboard::Numpad2:   return "Np2";
        case sf::Keyboard::Numpad3:   return "Np3";
        case sf::Keyboard::Numpad4:   return "Np4";
        case sf::Keyboard::Numpad5:   return "Np5";
        case sf::Keyboard::Numpad6:   return "Np6";
        case sf::Keyboard::Numpad7:   return "Np7";
        case sf::Keyboard::Numpad8:   return "Np8";
        case sf::Keyboard::Numpad9:   return "Np9";
        case sf::Keyboard::F1:        return "F1";
        case sf::Keyboard::F2:        return "F2";
        case sf::Keyboard::F3:        return "F3";
        case sf::Keyboard::F4:        return "F4";
        case sf::Keyboard::F5:        return "F5";
        case sf::Keyboard::F6:        return "F6";
        case sf::Keyboard::F7:        return "F7";
        case sf::Keyboard::F8:        return "F8";
        case sf::Keyboard::F9:        return "F9";
        case sf::Keyboard::F10:       return "F10";
        case sf::Keyboard::F11:       return "F11";
        case sf::Keyboard::F12:       return "F12";
        case sf::Keyboard::Pause:     return "Pause";
        default:                      return "the fuck is this";
        }
    }

/// Returns a key code from a key name
inline sf::Keyboard::Key getKeyCode(sf::String keyName) { // I would use a switch here if C++ allowed me to switch the sf::String objects
        if (keyName == sf::String("A"))         return sf::Keyboard::A;
        if (keyName == sf::String("B"))         return sf::Keyboard::B;
        if (keyName == sf::String("C"))         return sf::Keyboard::C;
        if (keyName == sf::String("D"))         return sf::Keyboard::D;
        if (keyName == sf::String("E"))         return sf::Keyboard::E;
        if (keyName == sf::String("F"))         return sf::Keyboard::F;
        if (keyName == sf::String("G"))         return sf::Keyboard::G;
        if (keyName == sf::String("H"))         return sf::Keyboard::H;
        if (keyName == sf::String("I"))         return sf::Keyboard::I;
        if (keyName == sf::String("J"))         return sf::Keyboard::J;
        if (keyName == sf::String("K"))         return sf::Keyboard::K;
        if (keyName == sf::String("L"))         return sf::Keyboard::L;
        if (keyName == sf::String("M"))         return sf::Keyboard::M;
        if (keyName == sf::String("N"))         return sf::Keyboard::N;
        if (keyName == sf::String("O"))         return sf::Keyboard::O;
        if (keyName == sf::String("P"))         return sf::Keyboard::P;
        if (keyName == sf::String("Q"))         return sf::Keyboard::Q;
        if (keyName == sf::String("R"))         return sf::Keyboard::R;
        if (keyName == sf::String("S"))         return sf::Keyboard::S;
        if (keyName == sf::String("T"))         return sf::Keyboard::T;
        if (keyName == sf::String("U"))         return sf::Keyboard::U;
        if (keyName == sf::String("V"))         return sf::Keyboard::V;
        if (keyName == sf::String("W"))         return sf::Keyboard::W;
        if (keyName == sf::String("X"))         return sf::Keyboard::X;
        if (keyName == sf::String("Y"))         return sf::Keyboard::Y;
        if (keyName == sf::String("Z"))         return sf::Keyboard::Z;
        if (keyName == sf::String("0"))         return sf::Keyboard::Num0;
        if (keyName == sf::String("1"))         return sf::Keyboard::Num1;
        if (keyName == sf::String("2"))         return sf::Keyboard::Num2;
        if (keyName == sf::String("3"))         return sf::Keyboard::Num3;
        if (keyName == sf::String("4"))         return sf::Keyboard::Num4;
        if (keyName == sf::String("5"))         return sf::Keyboard::Num5;
        if (keyName == sf::String("6"))         return sf::Keyboard::Num6;
        if (keyName == sf::String("7"))         return sf::Keyboard::Num7;
        if (keyName == sf::String("8"))         return sf::Keyboard::Num8;
        if (keyName == sf::String("9"))         return sf::Keyboard::Num9;
        if (keyName == sf::String("Escape"))    return sf::Keyboard::Escape;
        if (keyName == sf::String(L"←Ctrl"))    return sf::Keyboard::LControl;
        if (keyName == sf::String(L"←Shift"))   return sf::Keyboard::LShift;
        if (keyName == sf::String(L"←Alt"))     return sf::Keyboard::LAlt;
        if (keyName == sf::String(L"←System"))  return sf::Keyboard::LSystem;
        if (keyName == sf::String(L"Control→")) return sf::Keyboard::RControl;
        if (keyName == sf::String(L"Shift→"))   return sf::Keyboard::RShift;
        if (keyName == sf::String(L"Alt→"))     return sf::Keyboard::RAlt;
        if (keyName == sf::String(L"Sys→"))     return sf::Keyboard::RSystem;
        if (keyName == sf::String("Menu"))      return sf::Keyboard::Menu;
        if (keyName == sf::String("["))         return sf::Keyboard::LBracket;
        if (keyName == sf::String("]"))         return sf::Keyboard::RBracket;
        if (keyName == sf::String(";"))         return sf::Keyboard::SemiColon;
        if (keyName == sf::String(","))         return sf::Keyboard::Comma;
        if (keyName == sf::String("."))         return sf::Keyboard::Period;
        if (keyName == sf::String("'"))         return sf::Keyboard::Quote;
        if (keyName == sf::String("/"))         return sf::Keyboard::Slash;
        if (keyName == sf::String("\\"))        return sf::Keyboard::BackSlash;
        if (keyName == sf::String("`"))         return sf::Keyboard::Tilde;
        if (keyName == sf::String("="))         return sf::Keyboard::Equal;
        if (keyName == sf::String("-"))         return sf::Keyboard::Dash;
        if (keyName == sf::String("Space"))     return sf::Keyboard::Space;
        if (keyName == sf::String("Return"))    return sf::Keyboard::Return;
        if (keyName == sf::String(L"←B"))       return sf::Keyboard::BackSpace;
        if (keyName == sf::String("Tab"))       return sf::Keyboard::Tab;
        if (keyName == sf::String(L"Pg↑"))      return sf::Keyboard::PageUp;
        if (keyName == sf::String(L"Pg↓"))      return sf::Keyboard::PageDown;
        if (keyName == sf::String("End"))       return sf::Keyboard::End;
        if (keyName == sf::String("Home"))      return sf::Keyboard::Home;
        if (keyName == sf::String("Insert"))    return sf::Keyboard::Insert;
        if (keyName == sf::String("Delete"))    return sf::Keyboard::Delete;
        if (keyName == sf::String("+"))         return sf::Keyboard::Add;
        if (keyName == sf::String(L"–"))        return sf::Keyboard::Subtract;
        if (keyName == sf::String(L"×"))        return sf::Keyboard::Multiply;
        if (keyName == sf::String(L"÷"))        return sf::Keyboard::Divide;
        if (keyName == sf::String(L"←"))        return sf::Keyboard::Left;
        if (keyName == sf::String(L"→"))        return sf::Keyboard::Right;
        if (keyName == sf::String(L"↑"))        return sf::Keyboard::Up;
        if (keyName == sf::String(L"↓"))        return sf::Keyboard::Down;
        if (keyName == sf::String("Np0"))       return sf::Keyboard::Numpad0;
        if (keyName == sf::String("Np1"))       return sf::Keyboard::Numpad1;
        if (keyName == sf::String("Np2"))       return sf::Keyboard::Numpad2;
        if (keyName == sf::String("Np3"))       return sf::Keyboard::Numpad3;
        if (keyName == sf::String("Np4"))       return sf::Keyboard::Numpad4;
        if (keyName == sf::String("Np5"))       return sf::Keyboard::Numpad5;
        if (keyName == sf::String("Np6"))       return sf::Keyboard::Numpad6;
        if (keyName == sf::String("Np7"))       return sf::Keyboard::Numpad7;
        if (keyName == sf::String("Np8"))       return sf::Keyboard::Numpad8;
        if (keyName == sf::String("Np9"))       return sf::Keyboard::Numpad9;
        if (keyName == sf::String("F1"))        return sf::Keyboard::F1;
        if (keyName == sf::String("F2"))        return sf::Keyboard::F2;
        if (keyName == sf::String("F3"))        return sf::Keyboard::F3;
        if (keyName == sf::String("F4"))        return sf::Keyboard::F4;
        if (keyName == sf::String("F5"))        return sf::Keyboard::F5;
        if (keyName == sf::String("F6"))        return sf::Keyboard::F6;
        if (keyName == sf::String("F7"))        return sf::Keyboard::F7;
        if (keyName == sf::String("F8"))        return sf::Keyboard::F8;
        if (keyName == sf::String("F9"))        return sf::Keyboard::F9;
        if (keyName == sf::String("F10"))       return sf::Keyboard::F10;
        if (keyName == sf::String("F11"))       return sf::Keyboard::F11;
        if (keyName == sf::String("F12"))       return sf::Keyboard::F12;
        if (keyName == sf::String("Pause"))     return sf::Keyboard::Pause;
                                                return sf::Keyboard::Unknown;
    }

}

#endif // keys_hpp
