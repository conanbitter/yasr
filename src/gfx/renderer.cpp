#include "gfx.hpp"

namespace Gfx {

static float quad[6][4] = {
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {-1.0f, 1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, -1.0f, 1.0f, 1.0f},
};

static const std::string vertexShaderCode = R"(
    #version 150

    in vec2 vert;
    in vec2 vertUV;
    out vec2 fragUV;

    void main() {
        gl_Position = vec4(vert.x, vert.y, 0.0, 1.0);
        fragUV = vertUV;
    }
)";

static const std::string fragmentShaderCode = R"(
    #version 150

    uniform sampler2D tex;
    in vec2 fragUV;
    out vec4 outputColor;

    void main() {
        outputColor = texture(tex, fragUV);
    }
)";

void Renderer::init(int width, int height) {
    gl::exts::LoadTest glLoadResult = gl::sys::LoadFunctions();
    if (!glLoadResult) {
        error_message("Error", "Error loading OpenGL");
    }

    gl::ClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    // Init shader
    m_program = compileShaderProgram(vertexShaderCode, fragmentShaderCode);
    gl::UseProgram(m_program);
    GLint tex_loc = gl::GetUniformLocation(m_program, "tex");
    GLint vert_loc = gl::GetAttribLocation(m_program, "vert");
    GLint vertUV_loc = gl::GetAttribLocation(m_program, "vertUV");

    // Init buffers
    gl::Disable(gl::BLEND);
    gl::Disable(gl::DEPTH_TEST);
    gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);
    gl::GenVertexArrays(1, &m_vao);
    gl::BindVertexArray(m_vao);
    gl::GenBuffers(1, &m_vbo);
    gl::BindBuffer(gl::ARRAY_BUFFER, m_vbo);
    gl::EnableVertexAttribArray(vert_loc);
    gl::VertexAttribPointer(vert_loc, 2, gl::FLOAT, false, 4 * 4, nullptr);
    gl::EnableVertexAttribArray(vertUV_loc);
    gl::VertexAttribPointer(vertUV_loc, 2, gl::FLOAT, false, 4 * 4, (const void*)(2 * 4));
    gl::BufferData(gl::ARRAY_BUFFER, 6 * 4 * 4, &quad, gl::STATIC_DRAW);

    // Init textures
    gl::GenTextures(1, &m_texture);
    gl::ActiveTexture(gl::TEXTURE0);
    gl::BindTexture(gl::TEXTURE_2D, m_texture);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RED, width, height, 0, gl::RED, gl::UNSIGNED_BYTE, nullptr);
    gl::Uniform1i(tex_loc, 0);

    m_frameSize.width = width;
    m_frameSize.height = height;
    m_isInitComplete = true;
}

Renderer::~Renderer() {
    gl::DeleteTextures(1, &m_texture);
    gl::DeleteFramebuffers(1, &m_fbo);
    if (gl::IsBuffer(m_vbo)) {
        gl::DeleteBuffers(1, &m_vbo);
    }
    if (gl::IsVertexArray(m_vao)) {
        gl::DeleteVertexArrays(1, &m_vao);
    }
    if (gl::IsProgram(m_program)) {
        gl::DeleteProgram(m_program);
    }
}

void Renderer::reshape(float width, float height) {
    quad[0][0] = quad[1][0] = quad[3][0] = -width;
    quad[2][0] = quad[4][0] = quad[5][0] = width;
    quad[0][1] = quad[3][1] = quad[5][1] = -height;
    quad[1][1] = quad[2][1] = quad[4][1] = height;
    gl::BindVertexArray(m_vao);
    gl::BindBuffer(gl::ARRAY_BUFFER, m_vbo);
    gl::BufferData(gl::ARRAY_BUFFER, 6 * 4 * 4, &quad, gl::STATIC_DRAW);
}

void Renderer::present() {
    gl::BindTexture(gl::TEXTURE_2D, m_texture);
    gl::TexSubImage2D(gl::TEXTURE_2D, 0, 0, 0, m_frameSize.width, m_frameSize.height, gl::RGBA, gl::UNSIGNED_BYTE, m_framebuffer.data());
    gl::UseProgram(m_program);
    gl::BindVertexArray(m_vao);
    gl::DrawArrays(gl::TRIANGLES, 0, 6);
}

void Renderer::putPixel(int x, int y, Color color) {
    int pos = x + y * m_frameSize.width;
    if (pos >= 0 && pos < m_framebuffer.size()) {
        m_framebuffer[pos] = color;
    }
}

}  // namespace Gfx