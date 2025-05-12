#include <vp/graphics/device.hpp>

namespace vp::gl {

Window::Window(const std::string &title, u32 width, u32 height)
    : m_width(width), m_height(height) {
    m_pWindow = std::unique_ptr<SDL_Window, WindowDeleter>(
        SDL_CreateWindow(
            title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            static_cast<i32>(m_width), static_cast<int>(m_height),
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        ),
        [](SDL_Window *pWin) { SDL_DestroyWindow(pWin); }
    );
}

void Window::setFullscreen(bool enable) noexcept {
    SDL_SetWindowFullscreen(m_pWindow.get(), static_cast<u32>(enable));
}

void Window::setMaximize(bool enable) noexcept {
    if (enable) {
        SDL_MaximizeWindow(m_pWindow.get());
    } else {
        SDL_RestoreWindow(m_pWindow.get());
    }
}

f32 Window::getAspectRation() const noexcept {
    return static_cast<f32>(m_width) / static_cast<f32>(m_height);
}

SDL_GLContext Window::createGLContext() const noexcept {
    return SDL_GL_CreateContext(m_pWindow.get());
}

u32 Window::getWidth() const noexcept {
    return m_width;
}

u32 Window::getHeight() const noexcept {
    return m_height;
}

void Window::swapWindow() const noexcept {
    SDL_GL_SwapWindow(m_pWindow.get());
}

} // namespace vp::gl
