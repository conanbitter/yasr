#include <iostream>
#include "gfx/gfx.hpp"

class App : public Gfx::GfxApp {
   public:
    App() {
        setTitle("YASR");
        setSize(320, 200, 3);
    }
    void load() {
        renderer.putPixel(10, 10, 0xFF00FFFF);
    }
};

int main() {
    App app;
    app.init();
    app.load();
    app.run();
    return 0;
}