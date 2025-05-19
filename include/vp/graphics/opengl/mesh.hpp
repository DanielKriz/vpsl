#ifndef VP_GRAPHICS_OPENGL_MESH_HPP
#define VP_GRAPHICS_OPENGL_MESH_HPP

#include <memory>
#include <vector>

#include <vp/types.hpp>
#include <vp/description/attribute_description.hpp>
#include <vp/graphics/vertex.hpp>

namespace vp::gl::opengl {

class Mesh {
public:
    Mesh(const std::vector<Vertex> &vertices, const desc::AttributeDescription &desc);
    void draw() const;
private:
    std::shared_ptr<u32> m_pVBO;
    std::shared_ptr<u32> m_pVAO;
    const std::vector<Vertex> *m_pVertices;
    desc::AttributeDescription m_attrDesc;
    u32 m_VBO { 0 };
    u32 m_VAO { 0 };
};


} // namespace vp::gl::opengl

#endif // VP_GRAPHICS_OPENGL_MESH_HPP
