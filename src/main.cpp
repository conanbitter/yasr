#include <iostream>
#include "gfx/gfx.hpp"

class App : public Gfx::GfxApp {
   private:
    int dotx = 10;
    int doty = 10;
    int sx = 1;
    int sy = 1;

   public:
    App() {
        setTitle("YASR");
        setSize(320, 200, 3);
    }
    void onUpdate() override {
        dotx += sx;
        doty += sy;
        if (dotx >= 319 || dotx <= 0) sx = -sx;
        if (doty >= 199 || doty <= 0) sy = -sy;
        renderer.clear(0);
        renderer.putPixel(dotx, doty, 0xFF00FFFF);
    }
};

int main() {
    App app;
    app.init();
    app.run();
    return 0;
}