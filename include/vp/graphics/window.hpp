#ifndef VP_GRAPHICS_WINDOW_HPP
#define VP_GRAPHICS_WINDOW_HPP

#include <functional>
#include <memory>

#include <SDL2/SDL.h>

#include <vp/types.hpp>

namespace vp::gl {

/// @brief Wrapper around SDL window.
class Window final {
public:
    static constexpr u32 DEFAULT_WIDTH = 600;
    static constexpr u32 DEFAULT_HEIGHT = 600;

    explicit Window(
        const std::string &title = "",
        u32 width = DEFAULT_WIDTH,
        u32 height = DEFAULT_HEIGHT
    );

    void setFullscreen(bool enable) noexcept;
    void setMaximize(bool enable) noexcept;

    [[nodiscard]] f32 getAspectRation() const noexcept;
    [[nodiscard]] SDL_GLContext createGLContext() const noexcept;

    [[nodiscard]] u32 getWidth() const noexcept;
    [[nodiscard]] u32 getHeight() const noexcept;

    void swapWindow() const noexcept;

private:
    using WindowDeleter = std::function<void(SDL_Window *)>;
    std::unique_ptr<SDL_Window, WindowDeleter> m_pWindow;
    u32 m_width;
    u32 m_height;
};

} // namespace vp::gl

#endif // VP_GRAPHICS_WINDOW_HPP
