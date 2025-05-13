#include <vp/engine/engine.hpp>

#include <spdlog/spdlog.h>

namespace vp {
Engine::Engine() {
    m_device.init();
    m_device.createWindow();
    m_device.setupRuntime();

    // Setting up Event handler
    registerCallback(SDL_KEYDOWN, [this](SDL_Event const &event) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            m_isRunning = false;
        }
    });

    registerCallback(SDL_QUIT, [this]([[maybe_unused]] SDL_Event const &event) {
        m_isRunning = false;
    });

    registerCallback(SDL_KEYDOWN, [this](SDL_Event const &event) {
        static bool isMaximized = false;
        if (event.key.keysym.sym == SDLK_F10) {
            isMaximized = not isMaximized;
            if (isMaximized) {
                m_device.getWindow().setMaximize(true);
            } else {
                m_device.getWindow().setMaximize(false);
            }
        }
    });

    registerCallback(SDL_KEYDOWN, [this](SDL_Event const &event) {
        static bool isFullscreen = false;
        if (event.key.keysym.sym == SDLK_F11) {
            isFullscreen = not isFullscreen;
            if (isFullscreen) {
                m_device.getWindow().setMaximize(true);
            } else {
                m_device.getWindow().setMaximize(false);
            }
            m_device.getWindow().setFullscreen(isFullscreen);
        }
    });
    spdlog::debug("engine initialized");
}

Engine::~Engine() {
    delete m_program;
}

void Engine::registerCallback(SDL_EventType type, const EventCallback &callback) {
    m_registeredCallbacks[type].push_back(callback);
}

void Engine::handleExecutionSequence(const std::vector<desc::ProgramDescription> &descs) {
    using vp::gl::opengl::Shader;

    for (const auto &desc : descs) {
        auto &currentNode = m_executionSequence.emplace_back();
        auto &currentProgram = currentNode.getProgram();
        std::vector<Shader> attachedShaders;
        for (auto *shaderCode : desc.getShaderCodes()) {
            attachedShaders.emplace_back(Shader::initFromShaderCode(*shaderCode));
            currentProgram.attachShader(attachedShaders.back());
        }

        currentProgram.link();

        for (auto &shader : attachedShaders) {
            currentProgram.detachShader(shader);
        }
    }
}

void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        for (auto &callback :
            m_registeredCallbacks[static_cast<SDL_EventType>(event.type)]) {
            callback(event);
        }
    }
}

void Engine::render(f32 deltaTime) {
    const auto &window = m_device.getWindow();
    glViewport(0, 0, static_cast<i32>(window.getWidth()), static_cast<i32>(window.getHeight()));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto &node : m_executionSequence) {
        node.getProgram().use();
        node.getProgram().draw();
    }
}

void Engine::run() {
    spdlog::info("starting engine runtime");

    u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    f32 elapsedTime = 0.0f;
    do {
        handleEvents();

        f32 currentElapsedTime = static_cast<f32>(SDL_GetTicks()) / 1000.0f;
        render(currentElapsedTime - elapsedTime);
        elapsedTime = currentElapsedTime;

        m_device.getWindow().swapWindow();
    } while (m_isRunning);

    glDeleteVertexArrays(1, &vao);
}

} // namespace vp
