#ifndef COLOR_H
#define COLOR_H

#include <ostream>
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        FG_TASBEYAZ = 97,
        FG_BEYAZ = 97,
        FG_TASSIYAH = 30,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49,
        BG_LIGHTBLUE = 104,
        BG_COLOR1 = 46,
        BG_COLOR2 = 106,
        BG_CERCEVE = 44
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

#endif
