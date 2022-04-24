#include <iostream>
#include "gfx/gfx.hpp"

class App : public Gfx::GfxApp {
   public:
    App() {
        setTitle("YASR");
        setSize(320, 200, 3);
    }
};

int main() {
    App app;
    app.init();
    app.run();
    std::cout << "Hello" << std::endl;
    return 0;
}