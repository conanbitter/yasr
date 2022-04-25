#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include "gl/gl_core_3_2.hpp"
#include "color.hpp"

namespace Gfx {

class Renderer {
   private:
    GLuint m_program;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_fbo;
    GLuint m_texture;
    std::vector<Color> m_framebuffer;
    bool m_isInitComplete;
    Size m_frameSize;

   public:
    Renderer() : m_isInitComplete{false} {};
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    ~Renderer();

    void init(int width, int height);
    void reshape(float width, float height);
    void present();
    void putPixel(int x, int y, Color color);
};

GLuint compileShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode);

}  // namespace Gfx

#endif