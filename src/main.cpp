#include <iostream>
#include "gfx/gfx.hpp"
#include <random>
#include <cmath>

struct Particle {
    float x;
    float y;
    float dx;
    float dy;
    Gfx::Color color;
};

inline int max(const float d1, const float d2, const float d3, const int border) {
    float t = d1 > d2 ? d1 : d2;
    int r = t > d3 ? t : d3 + 1;
    return r > border ? border : r;
}

inline int min(const float d1, const float d2, const float d3) {
    float t = d1 < d2 ? d1 : d2;
    int r = t < d3 ? t : d3 - 1;
    return r < 0 ? 0 : r;
}

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
        std::uniform_real_distribution<float> speed(-0.5, 0.5);
        std::uniform_real_distribution<float> width(1.0, 319.0);
        std::uniform_real_distribution<float> height(1.0, 199.0);
        std::uniform_int_distribution<int> color(50, 255);
        std::mt19937 gen;

        for (int i = 0; i < 4; i++) {
            particles.push_back(Particle{
                width(gen),
                height(gen),
                speed(gen),
                speed(gen),
                Gfx::Color(color(gen), color(gen), color(gen), 255)});
        }
    }

    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Gfx::Color color) {
        Gfx::Color c;
        int xmin = min(x1, x2, x3);
        int xmax = max(x1, x2, x3, 320);
        int ymin = min(y1, y2, y3);
        int ymax = max(y1, y2, y3, 200);

        for (int y = ymin; y <= ymax; y++) {
            for (int x = xmin; x <= xmax; x++) {
                if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
                    (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
                    (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0) {
                    renderer.putPixel(x, y, color);
                }
            }
        }
        renderer.putPixel(x1, y1, 0xFF0000FF);
        renderer.putPixel(x2, y2, 0x00FF00FF);
        renderer.putPixel(x3, y3, 0x0000FFFF);
    }

    void onUpdate() override {
        renderer.clear(0);
        drawTriangle(
            particles[0].x,
            particles[0].y,
            particles[1].x,
            particles[1].y,
            particles[2].x,
            particles[2].y,
            0xF000FF);
        drawTriangle(
            particles[2].x,
            particles[2].y,
            particles[1].x,
            particles[1].y,
            particles[3].x,
            particles[3].y,
            0xF0FF);
        for (Particle& p : particles) {
            if ((p.x + p.dx) > 320.0 || (p.x + p.dx) < 0.0) {
                p.dx = -p.dx;
            }
            if ((p.y + p.dy) > 200.0 || (p.y + p.dy) < 0.0) {
                p.dy = -p.dy;
            }
            renderer.putPixel(p.x, p.y, 0xFF0000FF);
            p.x += p.dx;
            p.y += p.dy;
        }
    }
};

int main() {
    App app;
    app.init();
    app.run();
    return 0;
}