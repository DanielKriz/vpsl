#ifndef VP_GRAPHICS_OPENGL_OBJECT_HPP
#define VP_GRAPHICS_OPENGL_OBJECT_HPP

#include <vp/types.hpp>

namespace vp::gl::opengl {

class Object {
public:
    virtual ~Object() = default;
    [[nodiscard]] u32 get() const { return m_descriptor; };

protected:
    u32 m_descriptor;
};

} // namespace vp::gl::opengl

#endif // VP_OPENGL_OBJECT_HPP
