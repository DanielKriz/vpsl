#ifndef VP_DESCRIPTION_OPTIONS_HPP
#define VP_DESCRIPTION_OPTIONS_HPP

#include <vp/graphics/context_options.hpp>

namespace vp {

struct Options final {
    /// @brief Enables blend test
    bool isDepthTestEnabled { false };
    /// @brief Enables blend test
    bool isBlendingEnabled { false };
    /// @brief Enables blend test
    bool isFaceCullingEnabled { false };
    /// @brief Enables blend test
    gl::PolygonMode frontFacePolygonMode { gl::PolygonMode::Fill };
    /// @brief Enables blend test
    gl::PolygonMode backFacePolygonMode { gl::PolygonMode::Fill };
    /// @brief Enables blend test
    gl::CullingMode cullingMode { gl::CullingMode::Back };
    /// @brief Enables blend test
    gl::FrontFaceMode frontFaceMode { gl::FrontFaceMode::CCW };
    /// @brief Enables blend test
    gl::DepthFunction depthFunction { gl::DepthFunction::Less };
    /// @brief Enables blend test
    gl::BlendingFactor srcBlendFactor { gl::BlendingFactor::One };
    /// @brief Enables blend test
    gl::BlendingFactor dstBlendFactor { gl::BlendingFactor::Zero };
};

bool operator==(const Options &lhs, const Options &rhs);
std::ostream &operator<<(std::ostream &os, const Options &opts);

} // namespace vp

#endif // VP_DESCRIPTION_OPTIONS_HPP
