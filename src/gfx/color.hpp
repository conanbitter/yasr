#ifndef _COLOR_H
#define _COLOR_H

#include <cstdint>
#include <iostream>

namespace Gfx {

class Color {
   private:
    uint8_t c[4];

   public:
    Color() : c{0, 0, 0, 0} {}
    Color(int input);
    Color(int r, int g, int b, int a);

    operator int() const;
};

}  // namespace Gfx

#endif