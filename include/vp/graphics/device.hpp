#ifndef VP_GRAPHICS_DEVICE_HPP
#define VP_GRAPHICS_DEVICE_HPP

#include <memory>

#include <SDL2/SDL.h>
#include <fmt/core.h>

#include <vp/graphics/window.hpp>
#include <vp/types.hpp>

namespace vp::gl {

/// @brief Representation of GPU.
class GraphicsDevice {
public:
    GraphicsDevice() = default;
    ~GraphicsDevice();

    /// This type can only be constructed.
    GraphicsDevice(const GraphicsDevice &) = delete;
    GraphicsDevice(GraphicsDevice &&) noexcept = delete;
    GraphicsDevice &operator=(const GraphicsDevice &) = delete;
    GraphicsDevice &operator=(GraphicsDevice &&) noexcept = delete;

    void init();
    void createWindow(
        const std::string &title = "VPSL Window",
        u32 width = Window::DEFAULT_WIDTH,
        u32 height = Window::DEFAULT_HEIGHT
    );
    void setupRuntime();
    Window &getWindow();
    [[nodiscard]] f32 getAspectRatio() const;
    [[nodiscard]] static const std::vector<u32> &getTextureUnits() noexcept;
private:
    SDL_GLContext m_context {};
    std::unique_ptr<Window> m_pWindow;
};

} // namespace vp::gl

#endif // VP_GRAPHICS_DEVICE_HPP
