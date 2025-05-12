#include <vp/graphics/device.hpp>

namespace vp::gl {

GraphicsDevice::~GraphicsDevice() {
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

Window &GraphicsDevice::getWindow() {
    return *m_pWindow;
}

void GraphicsDevice::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Could not initialize SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

void GraphicsDevice::createWindow(const std::string &title, u32 width, u32 height) {
    m_pWindow = std::make_unique<Window>(title, width, height);
}

void GraphicsDevice::setupRuntime() {
    if (m_pWindow == nullptr) {
        throw std::runtime_error("Window has to be initialized");
    }

    m_context = m_pWindow->createGLContext();

    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
        throw std::runtime_error("Could not initialize Glad");
    }

    fmt::println("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    fmt::println("Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    fmt::println("Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    SDL_GL_SetSwapInterval(1);
}
} // namespace vp::gl
