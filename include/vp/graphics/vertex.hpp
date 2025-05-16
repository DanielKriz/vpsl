#ifndef VP_GRAPHICS_VERTEX_HPP
#define VP_GRAPHICS_VERTEX_HPP

#include <glm/glm.hpp>

namespace vp::gl {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

} // namespace vp::gl

#endif // VP_GRAPHICS_VERTEX_HPP
