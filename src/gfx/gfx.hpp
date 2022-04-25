#ifndef _GFX_H
#define _GFX_H

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include <vector>

namespace Gfx {

class App;
class Renderer;
class Color;

struct Size {
    int width;
    int height;
};

void error_message(const std::string error, const std::string message);

}  // namespace Gfx

#include "color.hpp"
#include "renderer.hpp"
#include "app.hpp"

#endif