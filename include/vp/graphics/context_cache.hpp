#ifndef VP_GRAPHICS_CONTEXT_CACHE_HPP
#define VP_GRAPHICS_CONTEXT_CACHE_HPP

#include <memory>

#include <vp/description/options.hpp>
#include <vp/graphics/context_options.hpp>
#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp::gl {

/// @brief Cache of current runtime options of GPUs context.
/// Switching between various modes and options is expensive and it is not
/// checked. Thus, if the function would be just called then it would be a waste
/// of resource.
///
/// This cache calls the function setting the context iff the value really does change.
/// Otherwise, it simply does nothing.
///
/// The default values of options come from OpenGL documentation.
class ContextCache {
public:
    /// @brief Enables blend test
    void enableDepthTest(bool enable) noexcept;
    /// @brief Enables blend test
    void enableBlending(bool enable) noexcept;
    /// @brief Enables blend test
    void enableFaceCulling(bool enable) noexcept;

    /// @brief Enables blend test
    void setPolygonMode(PolygonMode mode) noexcept;
    /// @brief Enables blend test
    void setPolygonMode(FrontFaceMode face, PolygonMode mode) noexcept;

    /// @brief Enables blend test
    void setCullingMode(CullingMode mode) noexcept;
    /// @brief Enables blend test
    void setFrontFaceMode(FrontFaceMode mode) noexcept;
    /// @brief Enables blend test
    void setDepthFunction(DepthFunction func) noexcept;
    /// @brief Enables blend test
    void setSrcBlendFactor(BlendingFactor factor) noexcept;
    /// @brief Enables blend test
    void setDstBlendFactor(BlendingFactor factor) noexcept;

private:
    std::unique_ptr<Options> m_pCurrentOptions;
};

} // namespace vp::gl

#endif // VP_GRAPHICS_CONTEXT_CACHE_HPP
