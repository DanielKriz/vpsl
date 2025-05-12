#ifndef VP_GRAPHICS_OPENGL_UTIL_HPP
#define VP_GRAPHICS_OPENGL_UTIL_HPP

#include <stdexcept>

#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vp/types.hpp>

namespace vp::gl::utils {

std::string getShaderErrorMessage(u32 desc);

template <typename T1 = glm::vec3, typename T2 = aiVector3D>
inline T1 toVector(const T2 *vec) {
    throw std::runtime_error("Not implemented conversion");
}

template <>
inline glm::vec3 toVector(const aiVector3D *vec) {
    return { vec->x, vec->y, vec->z };
}

template <>
inline glm::vec2 toVector(const aiVector3D *vec) {
    return { vec->x, vec->y };
}

} // namespace vp::gl::utils

#endif // VP_GRAPHICS_OPENGL_UTILS_HPP
