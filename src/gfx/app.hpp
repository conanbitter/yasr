#include "gfx.hpp"

namespace Gfx {

class GfxApp {
   private:
    bool m_isInitComplete;
    Size m_frameSize;
    Size m_windowSize;
    float m_aspectRatio;
    SDL_Window* m_window;
    SDL_GLContext m_context;
    const Uint8* m_keyboardState;
    std::string m_title;
    std::vector<Uint8> m_keys;

    GfxApp(const GfxApp&) = delete;
    GfxApp& operator=(const GfxApp&) = delete;
    void onResize(int width, int height);

   protected:
    Renderer renderer;

   public:
    GfxApp() : m_isInitComplete{false} {};
    ~GfxApp();

    void init();
    void run();

    void setTitle(std::string title) {
        if (!m_isInitComplete) {
            m_title = title;
        }
    }
    void setSize(int width, int height, int scale);

    virtual void onUpdate() {}
};

}  // namespace Gfx