#include "gfx.hpp"

namespace Gfx {

void GfxApp::init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_windowSize.width,
                                m_windowSize.height,
                                SDL_WINDOW_OPENGL);

    m_context = SDL_GL_CreateContext(m_window);
    m_keyboardState = SDL_GetKeyboardState(nullptr);
}

void GfxApp::run() {
    SDL_Event event;
    bool working = true;
    while (working) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    working = false;
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_KEYDOWN:
                    if (!event.key.repeat) {
                    }
                    break;
                case SDL_KEYUP:
                    if (!event.key.repeat) {
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
            }
        }
        SDL_GL_SwapWindow(m_window);
        SDL_Delay(5);
    }
}

void GfxApp::setSize(int width, int height, int scale) {
    if (!m_isInitComplete) {
        m_frameSize.width = width;
        m_frameSize.height = height;
        m_windowSize.width = m_frameSize.width * scale;
        m_windowSize.height = m_frameSize.height * scale;
        m_aspectRatio = static_cast<float>(m_windowSize.width) / static_cast<float>(m_windowSize.height);
    }
}

GfxApp::~GfxApp() {
    if (m_isInitComplete) {
        if (m_context) {
            SDL_GL_DeleteContext(m_context);
        }
        if (m_window) {
            SDL_DestroyWindow(m_window);
        }
        SDL_Quit();
    }
}

}  // namespace Gfx