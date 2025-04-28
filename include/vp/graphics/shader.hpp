#ifndef VP_GRAPHICS_SHADER_HPP
#define VP_GRAPHICS_SHADER_HPP

#include <string>
#include <unordered_map>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp::gl {

enum class ShaderKind : enum32 {
    Fragment = GL_FRAGMENT_SHADER,
    Vertex = GL_VERTEX_SHADER,
    TesselationControl = GL_TESS_CONTROL_SHADER,
    TesselationEvaluation = GL_TESS_EVALUATION_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Compute = GL_COMPUTE_SHADER,
};

class Shader {
public:
private:
};

} // namespace vp::gl

namespace vp {

template <>
inline std::unordered_map<std::string, gl::ShaderKind> utils::StringToEnumMap<gl::ShaderKind>::map = {
    { "vertex", gl::ShaderKind::Vertex },
    { "fragment", gl::ShaderKind::Fragment },
    { "geometry", gl::ShaderKind::Geometry },
    { "compute", gl::ShaderKind::Compute },
    { "tesselation_control", gl::ShaderKind::TesselationControl },
    { "tesselation_evaluation", gl::ShaderKind::TesselationEvaluation },
};

} // namespace vp

#endif // VP_GRAPHICS_SHADER_HPP
