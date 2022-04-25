#include "color.hpp"
#include <algorithm>

namespace Gfx {

uint8_t clampColor(int color) {
    if (color > 255) {
        return 255;
    }
    if (color < 0) {
        return 0;
    }
    return color;
}

Color::Color(int input) {
    uint8_t* p = (uint8_t*)&input;
    std::reverse_copy(p, p + sizeof c, c);
}

Color::Color(int r, int g, int b, int a) {
    c[0] = clampColor(r);
    c[1] = clampColor(g);
    c[2] = clampColor(b);
    c[3] = clampColor(a);
}

Color::operator int() const {
    int result;
    uint8_t* p = (uint8_t*)&result;
    std::reverse_copy(c, c + sizeof c, p);
    return result;
}

}  // namespace Gfx