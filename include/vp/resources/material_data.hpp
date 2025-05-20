#ifndef VP_RESOURCES_MATERIAL_DATA_HPP
#define VP_RESOURCES_MATERIAL_DATA_HPP

#include <iosfwd>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <vp/types.hpp>

namespace vp {

class MaterialData {
public:
    MaterialData() = default;
    MaterialData(
        glm::vec3 ambient,
        glm::vec3 specular,
        glm::vec3 diffuse,
        glm::vec3 emissive,
        f32 shininess
    );

    void setAmbient(glm::vec3 value) noexcept;
    void setSpecular(glm::vec3 value) noexcept;
    void setEmissive(glm::vec3 value) noexcept;
    void setDiffuse(glm::vec3 value) noexcept;
    void setShininess(f32 value) noexcept;

    [[nodiscard]] const glm::vec3 &getAmbient() const noexcept;
    [[nodiscard]] const glm::vec3 &getSpecular() const noexcept;
    [[nodiscard]] const glm::vec3 &getEmissive() const noexcept;
    [[nodiscard]] const glm::vec3 &getDiffuse() const noexcept;
    [[nodiscard]] f32 getShininess() const noexcept;

private:
    glm::vec3 m_ambient { glm::zero<glm::vec3>() };
    glm::vec3 m_specular { glm::zero<glm::vec3>() };
    glm::vec3 m_diffuse { glm::zero<glm::vec3>() };
    glm::vec3 m_emmisive { glm::zero<glm::vec3>() };
    f32 m_shininess { 0.0f };
};

std::ostream &operator<<(std::ostream &os, const MaterialData &data);

} // namespace vp

#endif // VP_RESOURCES_MATERIAL_DATA_HPP
