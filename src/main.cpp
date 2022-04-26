#include <iostream>
#include "gfx/gfx.hpp"
#include <random>

struct Particle {
    double x;
    double y;
    double dx;
    double dy;
    Gfx::Color color;
};

class App : public Gfx::GfxApp {
   private:
    int dotx = 10;
    int doty = 10;
    int sx = 1;
    int sy = 1;
    std::vector<Particle> particles;

   public:
    App() {
        setTitle("YASR");
        setSize(320, 200, 3);
        std::uniform_real_distribution<double> speed(-1.5, 1.5);
        std::uniform_real_distribution<double> width(1.0, 319.0);
        std::uniform_real_distribution<double> height(1.0, 199.0);
        std::uniform_int_distribution<int> color(50, 255);
        std::mt19937 gen;

        for (int i = 0; i < 5000; i++) {
            particles.push_back(Particle{
                width(gen),
                height(gen),
                speed(gen),
                speed(gen),
                Gfx::Color(color(gen), color(gen), color(gen), 255)});
        }
    }
    void onUpdate() override {
        /*dotx += sx;
        doty += sy;
        if (dotx >= 319 || dotx <= 0) sx = -sx;
        if (doty >= 199 || doty <= 0) sy = -sy;*/
        renderer.clear(0);
        for (Particle& p : particles) {
            if ((p.x + p.dx) > 320.0 || (p.x + p.dx) < 0.0) {
                p.dx = -p.dx;
            }
            if ((p.y + p.dy) > 200.0 || (p.y + p.dy) < 0.0) {
                p.dy = -p.dy;
            }
            p.x += p.dx;
            p.y += p.dy;
            renderer.putPixel(p.x, p.y, p.color);
        }
    }
};

int main() {
    App app;
    app.init();
    app.run();
    return 0;
}