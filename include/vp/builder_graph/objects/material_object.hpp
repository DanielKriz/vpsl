#pragma once

#include <vp/types.hpp>
#include <glm/glm.hpp>

namespace vp {
struct MaterialObject {};
} // namespace vp

class Material {
public:
private:
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    vp::f32 roughness;
};
