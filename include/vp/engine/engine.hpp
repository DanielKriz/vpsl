#ifndef VP_ENGINE_HPP
#define VP_ENGINE_HPP

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <glad/glad.h>
#if 0
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#endif
#include <fmt/core.h>

#include <vp/types.hpp>
#include <vp/description/program_description.hpp>
#include <vp/graphics/opengl/program.hpp>
#include <vp/graphics/device.hpp>
#include <vp/engine/execution_node.hpp>
#include <vp/graphics/opengl/shader.hpp>

#include <iostream>

namespace vp {
struct Position {
    u32 x {0};
    u32 y {0};
};

using EventCallback = std::function<void(SDL_Event const &)>;

class Engine final {
public:
    explicit Engine();
    ~Engine();

    /// This type can only be constructed.
    Engine(const Engine &) = delete;
    Engine(Engine &&) noexcept = delete;
    Engine &operator=(const Engine &) = delete;
    Engine &operator=(Engine &&) noexcept = delete;

    void run();
    void render(f32 deltaTime);

    void handleEvents();
    void handleExecutionSequence(const std::vector<desc::ProgramDescription> &descs);
    void registerCallback(SDL_EventType type, const EventCallback &callback);

private:
    gl::GraphicsDevice m_device;
    std::map<SDL_EventType, std::vector<EventCallback>> m_registeredCallbacks;

    std::vector<ExecutionNode> m_executionSequence;

    gl::opengl::Program *m_program { nullptr };

    bool m_isRunning { true };
    bool m_isFullscreen { false };
};
} // namespace vp

#endif // VP_ENGINE_HPP
